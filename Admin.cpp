#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

Admin::Admin() : m_username("admin"), m_password("admin123")
{
    cout << "Admin конструктор за замовчуванням викликаний" << endl;
    InitializeDefaultAdmin();
}

Admin::Admin(const string& username, const string& password)
    : m_username(username), m_password(password)
{
    cout << "Admin конструктор з параметрами викликаний для: "
         << username << endl;
    InitializeDefaultAdmin();
}

Admin::Admin(const Admin& other)
    : m_username(other.m_username), m_password(other.m_password),
      m_users(other.m_users)
{
    cout << "Admin копіювальний конструктор викликаний" << endl;
}

Admin::Admin(Admin&& other) noexcept
    : m_username(move(other.m_username)), m_password(move(other.m_password)),
      m_users(move(other.m_users))
{
    cout << "Admin переміщувальний конструктор викликаний" << endl;
}

Admin::~Admin()
{
    cout << "Admin деструктор викликаний для: " << m_username << endl;
    cout << "Знищено: " << m_users.size() << " користувачів" << endl;
}

void Admin::InitializeDefaultAdmin()
{
    if (m_users.empty())
    {
        // Додаємо адміністратора за замовчуванням
        m_users["admin"] = UserData("admin123", UserRole::ADMIN);
    }
}

string Admin::RoleToString(UserRole role) const
{
    switch (role) {
        case UserRole::ADMIN: return "ADMIN";
        case UserRole::STUDENT: return "STUDENT";
        default: return "STUDENT";
    }
}

UserRole Admin::StringToRole(const string& roleStr) const
{
    if (roleStr == "ADMIN") return UserRole::ADMIN;
    if (roleStr == "STUDENT") return UserRole::STUDENT;
    return UserRole::STUDENT; // за замовчуванням
}

void Admin::SetUsername(const string& newUsername)
{
    if (newUsername.empty())
    {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    m_username = newUsername;
}

void Admin::SetPassword(const string& newPassword)
{
    if (!ValidatePassword(newPassword))
    {
        throw invalid_argument("Новий пароль не відповідає вимогам безпеки");
    }
    m_password = newPassword;
}

Admin& Admin::operator=(const Admin& other)
{
    if (this != &other)
    {
        m_username = other.m_username;
        m_password = other.m_password;
        m_users = other.m_users;
    }
    return *this;
}

Admin& Admin::operator=(Admin&& other) noexcept
{
    if (this != &other)
    {
        m_username = move(other.m_username);
        m_password = move(other.m_password);
        m_users = move(other.m_users);
    }
    return *this;
}

bool Admin::operator==(const Admin& other) const
{
    return m_username == other.m_username && m_password == other.m_password;
}

string Admin::HashPassword(const string& password) const
{
    hash<string> hasher;
    return to_string(hasher(password));
}

bool Admin::VerifyPassword(const string& inputPassword,
                          const string& storedPassword) const
{
    return inputPassword == storedPassword;
}

bool Admin::AddUser(const string& username, const string& password, UserRole role)
{
    if (username.empty())
    {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!ValidatePassword(password))
    {
        throw invalid_argument("Пароль не відповідає вимогам безпеки");
    }
    if (UserExists(username))
    {
        throw invalid_argument("Користувач з таким іменем вже існує: " + username);
    }

    m_users[username] = UserData(password, role);

    if (!SaveUsersToFile("users.txt"))
    {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "✅ Користувача '" << username << "' успішно додано!" << endl;
    return true;
}

bool Admin::RemoveUser(const string& username)
{
    if (username.empty())
    {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!UserExists(username))
    {
        throw invalid_argument("Користувач не існує: " + username);
    }
    if (username == "admin")
    {
        throw invalid_argument("Не можна видалити адміністратора");
    }

    m_users.erase(username);

    if (!SaveUsersToFile("users.txt"))
    {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "✅ Користувача '" << username << "' успішно видалено!" << endl;
    return true;
}

bool Admin::ChangePassword(const string& username, const string& newPassword)
{
    if (username.empty())
    {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!ValidatePassword(newPassword))
    {
        throw invalid_argument("Новий пароль не відповідає вимогам безпеки");
    }
    if (!UserExists(username))
    {
        throw invalid_argument("Користувач не існує: " + username);
    }

    m_users[username].password = newPassword;

    if (!SaveUsersToFile("users.txt"))
    {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "✅ Пароль для користувача '" << username << "' успішно змінено!" << endl;
    return true;
}

bool Admin::ChangeUserRole(const string& username, UserRole newRole)
{
    if (username.empty())
    {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!UserExists(username))
    {
        throw invalid_argument("Користувач не існує: " + username);
    }
    if (username == "admin" && newRole != UserRole::ADMIN)
    {
        throw invalid_argument("Не можна змінити роль головного адміністратора");
    }

    m_users[username].role = newRole;

    if (!SaveUsersToFile("users.txt"))
    {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "✅ Роль користувача '" << username << "' успішно змінено на "
         << RoleToString(newRole) << "!" << endl;
    return true;
}

bool Admin::Authenticate(const string& username, const string& password) const
{
    if (username.empty() || password.empty())
    {
        return false;
    }

    auto it = m_users.find(username);
    if (it == m_users.end())
    {
        return false;
    }

    return VerifyPassword(password, it->second.password);
}

UserRole Admin::GetUserRole(const string& username) const
{
    auto it = m_users.find(username);
    if (it == m_users.end())
    {
        throw invalid_argument("Користувач не існує: " + username);
    }
    return it->second.role;
}

void Admin::ListUsers() const
{
    cout << "Список користувачів (" << m_users.size() << "):" << endl;
    for (const auto& user : m_users)
    {
        cout << "  " << user.first << " (" << RoleToString(user.second.role) << ")";
        if (user.first == "admin")
        {
            cout << " - головний адміністратор";
        }
        cout << endl;
    }
}

void Admin::ResetPassword(const string& username)
{
    if (username.empty())
    {
        throw invalid_argument("Ім'я користувача не може бути порожнім");
    }
    if (!UserExists(username))
    {
        throw invalid_argument("Користувач не існує: " + username);
    }

    string defaultPassword = "password123";
    m_users[username].password = defaultPassword;

    if (!SaveUsersToFile("users.txt"))
    {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "Пароль для користувача " << username << " скинуто на: "
         << defaultPassword << endl;
}

void Admin::ExportUsers(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Не вдалося відкрити файл для експорту: " + filename);
    }

    for (const auto& user : m_users)
    {
        file << user.first << ":" << user.second.password << ":"
             << RoleToString(user.second.role) << endl;
    }

    file.close();
}

bool Admin::LoadUsersFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Файл " << filename << " не знайдено. Буде створено новий "
             << "при першому збереженні." << endl;
        return false;
    }

    unordered_map<string, UserData> oldUsers = m_users;
    m_users.clear();

    string line;
    bool hasErrors = false;
    int loadedCount = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string username, password, roleStr;

        if (getline(ss, username, ':') &&
            getline(ss, password, ':') &&
            getline(ss, roleStr))
        {
            if (!username.empty() && !password.empty())
            {
                UserRole role = StringToRole(roleStr);
                m_users[username] = UserData(password, role);
                loadedCount++;
            }
            else
            {
                hasErrors = true;
                cout << "Попередження: Знайдено неправильний запис у файлі: "
                     << line << endl;
            }
        }
        else
        {
            hasErrors = true;
            cout << "Попередження: Неправильний формат рядка у файлі: "
                 << line << endl;
        }
    }

    file.close();

    if (m_users.empty() && !oldUsers.empty())
    {
        m_users = oldUsers;
        cout << "Відновлено попередніх користувачів." << endl;
    }

    if (m_users.find("admin") == m_users.end())
    {
        m_users["admin"] = UserData("admin123", UserRole::ADMIN);
        cout << "Додано адміністратора за замовчуванням." << endl;
    }

    cout << "Завантажено " << loadedCount << " користувачів з файлу." << endl;
    return !hasErrors;
}

bool Admin::SaveUsersToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Помилка: Не вдалося відкрити файл для запису: " << filename << endl;
        return false;
    }

    for (const auto& user : m_users)
    {
        file << user.first << ":" << user.second.password << ":"
             << RoleToString(user.second.role) << endl;
    }

    file.close();
    cout << "Збережено " << m_users.size() << " користувачів у файл: "
         << filename << endl;
    return true;
}

bool Admin::ValidatePassword(const string& password)
{
    if (password.length() < 6)
    {
        throw invalid_argument("Пароль повинен містити щонайменше 6 символів");
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (char c : password)
    {
        if (isalpha(c)) hasLetter = true;
        if (isdigit(c)) hasDigit = true;
    }

    if (!hasLetter || !hasDigit)
    {
        throw invalid_argument("Пароль повинен містити як літери, так і цифри");
    }

    return true;
}

bool Admin::UserExists(const string& username) const
{
    return m_users.find(username) != m_users.end();
}

int Admin::GetUserCount() const
{
    return m_users.size();
}

void Admin::DisplayUserInfo(const string& username) const
{
    if (!UserExists(username))
    {
        throw invalid_argument("Користувач не існує: " + username);
    }

    const UserData& userData = m_users.at(username);
    cout << "Інформація про користувача:" << endl;
    cout << "  Ім'я: " << username << endl;
    cout << "  Роль: " << RoleToString(userData.role) << endl;
    cout << "  Пароль: " << userData.password << endl;
}

bool Admin::IsAdminUser(const string& username) const
{
    auto it = m_users.find(username);
    if (it == m_users.end()) return false;
    return it->second.role == UserRole::ADMIN;
}

void Admin::ChangeOwnPassword(const string& newPassword)
{
    if (!ValidatePassword(newPassword))
    {
        throw invalid_argument("Новий пароль не відповідає вимогам безпеки");
    }

    m_users[m_username].password = newPassword;

    if (!SaveUsersToFile("users.txt"))
    {
        throw runtime_error("Не вдалося зберегти користувачів у файл");
    }

    cout << "Ваш пароль успішно змінено!" << endl;
}

vector<string> Admin::GetAllUsernames() const
{
    vector<string> usernames;
    for (const auto& user : m_users)
    {
        usernames.push_back(user.first);
    }
    return usernames;
}