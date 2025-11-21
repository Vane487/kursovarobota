#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

// Конструктори та деструктор
Admin::Admin() : username("admin"), password("admin123") {
    cout << "Admin конструктор за замовчуванням викликаний" << endl;
    initializeDefaultAdmin();
}

Admin::Admin(const string& username, const string& password)
    : username(username), password(password) {
    cout << "Admin конструктор з параметрами викликаний для: " << username << endl;
    initializeDefaultAdmin();
}

Admin::Admin(const Admin& other)
    : username(other.username), password(other.password), users(other.users) {
    cout << "Admin копіювальний конструктор викликаний" << endl;
}

Admin::Admin(Admin&& other) noexcept
    : username(move(other.username)), password(move(other.password)), users(move(other.users)) {
    cout << "Admin переміщувальний конструктор викликаний" << endl;
}

Admin::~Admin() {
    cout << "Admin деструктор викликаний для: " << username << endl;
    cout << "Знищено: " << users.size() << " користувачів" << endl;
}

// Setter методи
void Admin::setUsername(const string& newUsername) {
    if (newUsername.empty()) {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    this->username = newUsername;
}

void Admin::setPassword(const string& newPassword) {
    if (!validatePassword(newPassword)) {
        throw invalid_argument("Новий пароль не відповідає вимогам безпеки");
    }
    this->password = newPassword;
}

void Admin::setUsers(const unordered_map<string, string>& newUsers) {
    this->users = newUsers;
}

// Оператори
Admin& Admin::operator=(const Admin& other) {
    if (this != &other) {
        username = other.username;
        password = other.password;
        users = other.users;
    }
    return *this;
}

Admin& Admin::operator=(Admin&& other) noexcept {
    if (this != &other) {
        username = move(other.username);
        password = move(other.password);
        users = move(other.users);
    }
    return *this;
}

bool Admin::operator==(const Admin& other) const {
    return username == other.username && password == other.password;
}

// Решта методів залишаються без змін...
void Admin::initializeDefaultAdmin() {
    if (users.empty()) {
        users["admin"] = "admin123";
    }
}

string Admin::hashPassword(const string& password) const {
    hash<string> hasher;
    return to_string(hasher(password));
}

bool Admin::verifyPassword(const string& inputPassword, const string& storedPassword) const {
    return inputPassword == storedPassword;
}

bool Admin::addUser(const string& username, const string& password) {
    if (username.empty()) {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!validatePassword(password)) {
        throw invalid_argument("Пароль не відповідає вимогам безпеки");
    }
    if (userExists(username)) {
        throw invalid_argument("Користувач з таким іменем вже існує: " + username);
    }

    users[username] = password;

    if (!saveUsersToFile("users.txt")) {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    return true;
}

bool Admin::removeUser(const string& username) {
    if (username.empty()) {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!userExists(username)) {
        throw invalid_argument("Користувач не існує: " + username);
    }
    if (username == "admin") {
        throw invalid_argument("Не можна видалити адміністратора");
    }

    users.erase(username);

    if (!saveUsersToFile("users.txt")) {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    return true;
}

bool Admin::changePassword(const string& username, const string& newPassword) {
    if (username.empty()) {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!validatePassword(newPassword)) {
        throw invalid_argument("Новий пароль не відповідає вимогам безпеки");
    }
    if (!userExists(username)) {
        throw invalid_argument("Користувач не існує: " + username);
    }

    users[username] = newPassword;

    if (!saveUsersToFile("users.txt")) {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    return true;
}

bool Admin::authenticate(const string& username, const string& password) const {
    if (username.empty() || password.empty()) {
        return false;
    }

    auto it = users.find(username);
    if (it == users.end()) {
        return false;
    }

    return verifyPassword(password, it->second);
}

void Admin::listUsers() const {
    cout << "Список користувачів (" << users.size() << "):" << endl;
    for (const auto& user : users) {
        cout << "  " << user.first;
        if (user.first == "admin") {
            cout << " (адміністратор)";
        }
        cout << endl;
    }
}

void Admin::resetPassword(const string& username) {
    if (username.empty()) {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!userExists(username)) {
        throw invalid_argument("Користувач не існує: " + username);
    }

    string defaultPassword = "password123";
    users[username] = defaultPassword;

    if (!saveUsersToFile("users.txt")) {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "Пароль для користувача " << username << " скинуто на: " << defaultPassword << endl;
}

void Admin::exportUsers(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не вдалося відкрити файл для експорту: " + filename);
    }

    for (const auto& user : users) {
        file << user.first << ":" << user.second << endl;
    }

    file.close();
}

bool Admin::loadUsersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл " << filename << " не знайдено. Буде створено новий при першому збереженні." << endl;
        return false;
    }

    unordered_map<string, string> oldUsers = users;
    users.clear();

    string line;
    bool hasErrors = false;
    int loadedCount = 0;

    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string username = line.substr(0, pos);
            string password = line.substr(pos + 1);

            if (!username.empty() && !password.empty()) {
                users[username] = password;
                loadedCount++;
            } else {
                hasErrors = true;
                cout << "Попередження: Знайдено неправильний запис у файлі: " << line << endl;
            }
        } else {
            hasErrors = true;
            cout << "Попередження: Неправильний формат рядка у файлі: " << line << endl;
        }
    }

    file.close();

    if (users.empty() && !oldUsers.empty()) {
        users = oldUsers;
        cout << "Відновлено попередніх користувачів." << endl;
    }

    if (users.find("admin") == users.end()) {
        users["admin"] = "admin123";
        cout << "Додано адміністратора за замовчуванням." << endl;
    }

    cout << "Завантажено " << loadedCount << " користувачів з файлу." << endl;
    return !hasErrors;
}

bool Admin::saveUsersToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка: Не вдалося відкрити файл для запису: " << filename << endl;
        return false;
    }

    for (const auto& user : users) {
        file << user.first << ":" << user.second << endl;
    }

    file.close();
    cout << "Збережено " << users.size() << " користувачів у файл: " << filename << endl;
    return true;
}

bool Admin::validatePassword(const string& password) {
    if (password.length() < 6) {
        throw invalid_argument("Пароль повинен містити щонайменше 6 символів");
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (char c : password) {
        if (isalpha(c)) hasLetter = true;
        if (isdigit(c)) hasDigit = true;
    }

    if (!hasLetter || !hasDigit) {
        throw invalid_argument("Пароль повинен містити як літери, так і цифри");
    }

    return true;
}

bool Admin::userExists(const string& username) const {
    return users.find(username) != users.end();
}

int Admin::getUserCount() const {
    return users.size();
}

void Admin::displayUserInfo(const string& username) const {
    if (!userExists(username)) {
        throw invalid_argument("Користувач не існує: " + username);
    }

    cout << "Інформація про користувача:" << endl;
    cout << "  Ім'я: " << username << endl;
    cout << "  Тип: " << (username == "admin" ? "Адміністратор" : "Звичайний користувач") << endl;
    cout << "  Пароль: " << users.at(username) << endl;
}

bool Admin::isAdminUser(const string& username) const {
    return username == "admin";
}

void Admin::changeOwnPassword(const string& newPassword) {
    if (!validatePassword(newPassword)) {
        throw invalid_argument("Новий пароль не відповідає вимогам безпеки");
    }

    users[username] = newPassword;

    if (!saveUsersToFile("users.txt")) {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "Ваш пароль успішно змінено!" << endl;
}

vector<string> Admin::getAllUsernames() const {
    vector<string> usernames;
    for (const auto& user : users) {
        usernames.push_back(user.first);
    }
    return usernames;
}