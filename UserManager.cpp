#include "UserManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>

#include "MenuManager.h"

using namespace std;

namespace University {

const string UserManager::ERROR_EMPTY_USERNAME = "ПОМИЛКА: Ім'я користувача не може бути порожнім";
const string UserManager::ERROR_USER_EXISTS = "ПОМИЛКА: Користувач вже існує";
const string UserManager::ERROR_USER_NOT_FOUND = "ПОМИЛКА: Користувача не знайдено";
const string UserManager::ERROR_DELETE_ADMIN = "ПОМИЛКА: Не можна видалити головного адміністратора";
const string UserManager::ERROR_PASSWORD_LENGTH = "ПОМИЛКА: Пароль має бути не менше 6 символів";
const string UserManager::ERROR_PASSWORD_CHARS = "ПОМИЛКА: Пароль має містити літери та цифри";
const string UserManager::SUCCESS_ADD_USER = "УСПІХ: Користувача додано";
const string UserManager::SUCCESS_REMOVE_USER = "УСПІХ: Користувача видалено";

UserData::UserData() : password(""), role(UserRole::Student)
{
}

UserData::UserData(const string& pwd, UserRole r) : password(pwd), role(r)
{
}

UserManager::UserManager()
{
    InitializeDefaultAdmin();
}

UserManager::UserManager(const UserManager& other) : m_users(other.m_users)
{
}

UserManager::UserManager(UserManager&& other) noexcept : m_users(std::move(other.m_users))
{
}

UserManager::~UserManager()
{
}

void UserManager::InitializeDefaultAdmin()
{
    m_users["admin"] = UserData("admin123", UserRole::Admin);
}

string UserManager::RoleToString(UserRole role) const
{
    switch (role)
    {
        case UserRole::Student:
            return "Студент";
        case UserRole::Teacher:
            return "Викладач";
        case UserRole::Admin:
            return "Адміністратор";
        default:
            return "Студент";
    }
}

UserRole UserManager::StringToRole(const string& roleStr) const
{
    if (roleStr == "Адміністратор" || roleStr == "Admin" || roleStr == "administrator")
    {
        return UserRole::Admin;
    }

    if (roleStr == "Викладач" || roleStr == "Teacher" || roleStr == "teacher")
    {
        return UserRole::Teacher;
    }

    if (roleStr == "Студент" || roleStr == "Student" || roleStr == "student")
    {
        return UserRole::Student;
    }

    return UserRole::Student;
}

string UserManager::AddUser(const string& username, const string& password, UserRole role)
{
    if (username.empty())
    {
        return ERROR_EMPTY_USERNAME;
    }

    string validation = ValidatePassword(password);
    if (!validation.empty())
    {
        return validation;
    }

    if (m_users.find(username) != m_users.end())
    {
        return ERROR_USER_EXISTS + ": " + username;
    }

    m_users[username] = UserData(password, role);
    string saveResult = SaveUsersToFile(FileConstants::USERS_FILE);

    if (saveResult.find("ПОМИЛКА") != string::npos)
    {
        m_users.erase(username);
        return saveResult;
    }

    return SUCCESS_ADD_USER + ": " + username;
}

string UserManager::EditUser(const string& username, const string& newPassword, int newRole)
{
    if (username.empty())
    {
        return ERROR_EMPTY_USERNAME;
    }

    auto it = m_users.find(username);
    if (it == m_users.end())
    {
        return ERROR_USER_NOT_FOUND + ": " + username;
    }

    string validation = ValidatePassword(newPassword);
    if (!validation.empty())
    {
        return validation;
    }

    UserRole role;
    switch (newRole)
    {
        case 1:
            role = UserRole::Student;
            break;
        case 2:
            role = UserRole::Teacher;
            break;
        case 3:
            role = UserRole::Admin;
            break;
        default:
            return "ПОМИЛКА: Невірна роль. Дозволені значення: 1-Студент, 2-Викладач, 3-Адміністратор";
    }

    it->second.password = newPassword;
    it->second.role = role;

    string saveResult = SaveUsersToFile(FileConstants::USERS_FILE);
    if (saveResult.find("ПОМИЛКА") != string::npos)
    {
        return saveResult;
    }

    return "УСПІХ: Користувача оновлено: " + username;
}

string UserManager::RemoveUser(const string& username)
{
    if (username.empty())
    {
        return ERROR_EMPTY_USERNAME;
    }

    if (m_users.find(username) == m_users.end())
    {
        return ERROR_USER_NOT_FOUND + ": " + username;
    }

    if (username == "admin")
    {
        return ERROR_DELETE_ADMIN;
    }

    m_users.erase(username);
    string saveResult = SaveUsersToFile(FileConstants::USERS_FILE);

    if (saveResult.find("ПОМИЛКА") != string::npos)
    {
        return saveResult;
    }

    return SUCCESS_REMOVE_USER + ": " + username;
}

string UserManager::Authenticate(const string& username, const string& password) const
{
    if (username.empty() || password.empty())
    {
        return "ПОМИЛКА: Логін або пароль не можуть бути порожніми";
    }

    auto it = m_users.find(username);
    if (it == m_users.end())
    {
        return "ПОМИЛКА: Користувача не знайдено: " + username;
    }

    if (it->second.password != password)
    {
        return "ПОМИЛКА: Невірний пароль для користувача: " + username;
    }

    return "УСПІХ: Авторизація пройшла успішно для: " + username;
}

UserRole UserManager::GetUserRole(const string& username) const
{
    auto it = m_users.find(username);
    if (it != m_users.end())
    {
        return it->second.role;
    }

    return UserRole::Student;
}

string UserManager::ListUsers() const
{
    stringstream ss;
    ss << "=== СПИСОК КОРИСТУВАЧІВ ===\n";
    ss << "Загальна кількість: " << m_users.size() << "\n\n";

    for (const auto& user : m_users)
    {
        ss << " " << user.first << "\n";
        ss << "   Роль: " << RoleToString(user.second.role) << "\n";
        ss << "   Пароль: " << user.second.password << "\n";

        if (user.first == "admin")
        {
            ss << "    Головний адміністратор\n";
        }

        ss << "------------------------\n";
    }

    return ss.str();
}

string UserManager::ExportUsers(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return "ПОМИЛКА: Не вдалося відкрити файл для експорту: " + filename;
    }

    for (const auto& user : m_users)
    {
        file << user.first << ":" << user.second.password << ":"
             << RoleToString(user.second.role) << "\n";
    }

    file.close();
    return "УСПІХ: Користувачів експортовано у файл: " + filename;
}

string UserManager::SaveUsersToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return "ПОМИЛКА: Не вдалося відкрити файл для запису: " + filename;
    }

    for (const auto& user : m_users)
    {
        file << user.first << ":" << user.second.password << ":"
             << RoleToString(user.second.role) << "\n";
    }

    file.close();
    return "УСПІХ: Користувачів збережено у файл: " + filename;
}

string UserManager::ValidatePassword(const string& password) const
{
    if (password.length() < 6)
    {
        return ERROR_PASSWORD_LENGTH;
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (char c : password)
    {
        if (isalpha(c))
        {
            hasLetter = true;
        }

        if (isdigit(c))
        {
            hasDigit = true;
        }
    }

    if (!hasLetter || !hasDigit)
    {
        return ERROR_PASSWORD_CHARS;
    }

    return "";
}

string UserManager::GetUserCount() const
{
    return "Кількість користувачів у системі: " + to_string(m_users.size());
}

string UserManager::DisplayUserInfo(const string& username) const
{
    if (m_users.find(username) == m_users.end())
    {
        return ERROR_USER_NOT_FOUND + ": " + username;
    }

    const UserData& userData = m_users.at(username);
    stringstream ss;
    ss << "=== ІНФОРМАЦІЯ ПРО КОРИСТУВАЧА ===\n";
    ss << " Ім'я: " << username << "\n";
    ss << " Роль: " << RoleToString(userData.role) << "\n";
    ss << " Пароль: " << userData.password << "\n";

    if (username == "admin")
    {
        ss << " Статус: Головний адміністратор системи\n";
    }

    return ss.str();
}

string UserManager::LoadUsersFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        SaveUsersToFile(filename);
        return "ІНФО: Файл не знайдено. Створено новий файл з адміністратором.";
    }

    std::unordered_map<std::string, UserData> tempUsers;
    string line;
    int loadedCount = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string username;
        string password;
        string roleStr;

        if (getline(ss, username, ':') && getline(ss, password, ':') && getline(ss, roleStr))
        {
            if (!username.empty() && !password.empty())
            {
                UserRole role = StringToRole(roleStr);
                tempUsers[username] = UserData(password, role);
                loadedCount++;
            }
        }
    }

    file.close();
    m_users = tempUsers;
    InitializeDefaultAdmin();

    return "УСПІХ: Завантажено " + to_string(loadedCount) + " користувачів з файлу: " + filename;
}

void UserManager::ShowUserManagementMenu()
{
}

void UserManager::HandleAddUser()
{
}

void UserManager::HandleEditUser()
{
}

void UserManager::HandleDeleteUser()
{
}

void UserManager::HandleSearchUser()
{
}

void UserManager::WaitForEnter() const
{
}

} // namespace University