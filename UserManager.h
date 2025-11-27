/// @file     UserManager.h
/// @brief    Заголовний файл для класу керування користувачами
/// @author   Vanessa Hudan
/// @date     2025
/// @namespace University

#pragma once
#include "FileConstants.h"
#include <string>
#include <unordered_map>

namespace University {

/// @enum    UserRole
/// @brief   Ролі користувачів в системі
enum class UserRole {
    Student,  ///< Студент
    Teacher,  ///< Викладач
    Admin     ///< Адміністратор
};

/// @struct  UserData
/// @brief   Структура для зберігання даних користувача
struct UserData {
    std::string password;  ///< Пароль користувача
    UserRole role;         ///< Роль користувача

    /// @brief Конструктор за замовчуванням
    UserData();

    /// @brief Параметризований конструктор
    /// @param pwd Пароль користувача
    /// @param r   Роль користувача
    UserData(const std::string& pwd, UserRole r);
};

/// @class   UserManager
/// @brief   Клас для управління користувачами системи
class UserManager {
private:
    std::unordered_map<std::string, UserData> m_users;  ///< Колекція користувачів

    // Константи повідомлень
    static const std::string ERROR_EMPTY_USERNAME;     ///< Помилка: пусте ім'я користувача
    static const std::string ERROR_USER_EXISTS;        ///< Помилка: користувач вже існує
    static const std::string ERROR_USER_NOT_FOUND;     ///< Помилка: користувач не знайдений
    static const std::string ERROR_DELETE_ADMIN;       ///< Помилка: спроба видалити адміністратора
    static const std::string ERROR_PASSWORD_LENGTH;    ///< Помилка: невірна довжина пароля
    static const std::string ERROR_PASSWORD_CHARS;     ///< Помилка: невірні символи пароля
    static const std::string SUCCESS_ADD_USER;         ///< Успіх: користувача додано
    static const std::string SUCCESS_REMOVE_USER;      ///< Успіх: користувача видалено

public:
    /// @brief Конструктор за замовчуванням
    UserManager();

    /// @brief Конструктор копіювання
    /// @param other Об'єкт для копіювання
    UserManager(const UserManager& other);

    /// @brief Конструктор переміщення
    /// @param other Об'єкт для переміщення
    UserManager(UserManager&& other) noexcept;

    /// @brief Деструктор
    ~UserManager();

    /// @brief Ініціалізація стандартного адміністратора
    void InitializeDefaultAdmin();

    /// @brief Перетворення ролі в рядок
    /// @param role Роль для перетворення
    /// @return Рядкове представлення ролі
    std::string RoleToString(UserRole role) const;

    /// @brief Перетворення рядка в роль
    /// @param roleStr Рядок для перетворення
    /// @return Відповідна роль
    UserRole StringToRole(const std::string& roleStr) const;

    /// @brief Додавання нового користувача
    /// @param username Ім'я користувача
    /// @param password Пароль користувача
    /// @param role     Роль користувача
    /// @return Результат операції
    std::string AddUser(const std::string& username, const std::string& password,
                        UserRole role);

    /// @brief Видалення користувача
    /// @param username Ім'я користувача для видалення
    /// @return Результат операції
    std::string RemoveUser(const std::string& username);

    /// @brief Редагування даних користувача
    /// @param username    Ім'я користувача
    /// @param newPassword Новий пароль
    /// @param newRole     Нова роль
    /// @return Результат операції
    std::string EditUser(const std::string& username, const std::string& newPassword,
                         int newRole);

    /// @brief Аутентифікація користувача
    /// @param username Ім'я користувача
    /// @param password Пароль користувача
    /// @return Результат аутентифікації
    std::string Authenticate(const std::string& username, const std::string& password) const;

    /// @brief Отримання ролі користувача
    /// @param username Ім'я користувача
    /// @return Роль користувача
    UserRole GetUserRole(const std::string& username) const;

    /// @brief Отримання списку користувачів
    /// @return Форматований список користувачів
    std::string ListUsers() const;

    /// @brief Експорт користувачів у файл
    /// @param filename Ім'я файлу
    /// @return Результат операції
    std::string ExportUsers(const std::string& filename) const;

    /// @brief Збереження користувачів у файл
    /// @param filename Ім'я файлу
    /// @return Результат операції
    std::string SaveUsersToFile(const std::string& filename) const;

    /// @brief Валідація пароля
    /// @param password Пароль для перевірки
    /// @return Результат валідації
    std::string ValidatePassword(const std::string& password) const;

    /// @brief Отримання кількості користувачів
    /// @return Рядок з кількістю користувачів
    std::string GetUserCount() const;

    /// @brief Відображення інформації про користувача
    /// @param username Ім'я користувача
    /// @return Інформація про користувача
    std::string DisplayUserInfo(const std::string& username) const;

    /// @brief Завантаження користувачів з файлу
    /// @param filename Ім'я файлу
    /// @return Результат операції
    std::string LoadUsersFromFile(const std::string& filename);

    /// @brief Показ меню управління користувачами
    void ShowUserManagementMenu();

    /// @brief Обробка додавання користувача
    void HandleAddUser();

    /// @brief Обробка редагування користувача
    void HandleEditUser();

    /// @brief Обробка видалення користувача
    void HandleDeleteUser();

    /// @brief Обробка пошуку користувача
    void HandleSearchUser();

    /// @brief Очікування натискання Enter
    void WaitForEnter() const;
};

} // namespace University