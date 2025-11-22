#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <functional>

/**
 * @brief Ролі користувачів системи
 */
enum class UserRole {
    ADMIN,      ///< Адміністратор
    STUDENT     ///< Студент
};

/**
 * @brief Клас для управління адміністративними функціями
 *
 * Надає функціонал для керування користувачами, автентифікації
 * та роботи з файлами користувачів
 */
class Admin
{
private:
    std::string m_username;     ///< Ім'я користувача
    std::string m_password;     ///< Хеш пароля

    // Структура для зберігання даних користувача
    struct UserData {
        std::string password;
        UserRole role;

        UserData(const std::string& pwd = "", UserRole r = UserRole::STUDENT)
            : password(pwd), role(r) {}
    };

    std::unordered_map<std::string, UserData> m_users;  ///< База користувачів

    /// @brief Ініціалізує адміністратора за замовчуванням
    void InitializeDefaultAdmin();

    /// @brief Хешує пароль
    /// @param password Пароль для хешування
    /// @return Хеш пароля
    std::string HashPassword(const std::string& password) const;

    /// @brief Перевіряє відповідність пароля
    /// @param inputPassword Введений пароль
    /// @param storedPassword Збережений хеш
    /// @return true якщо паролі співпадають
    bool VerifyPassword(const std::string& inputPassword,
                       const std::string& storedPassword) const;

    /// @brief Конвертує роль у рядок
    std::string RoleToString(UserRole role) const;

    /// @brief Конвертує рядок у роль
    UserRole StringToRole(const std::string& roleStr) const;

public:
    // Конструктори та деструктор
    Admin();
    Admin(const std::string& username, const std::string& password);
    Admin(const Admin& other);
    Admin(Admin&& other) noexcept;
    ~Admin();

    // Властивості
    std::string GetUsername() const { return m_username; }
    std::string GetPassword() const { return m_password; }

    void SetUsername(const std::string& newUsername);
    void SetPassword(const std::string& newPassword);

    // Методи керування користувачами
    bool AddUser(const std::string& username, const std::string& password, UserRole role = UserRole::STUDENT);
    bool RemoveUser(const std::string& username);
    bool ChangePassword(const std::string& username, const std::string& newPassword);
    bool ChangeUserRole(const std::string& username, UserRole newRole);
    bool Authenticate(const std::string& username, const std::string& password) const;
    UserRole GetUserRole(const std::string& username) const;
    void ListUsers() const;
    void ResetPassword(const std::string& username);
    void ExportUsers(const std::string& filename) const;
    bool LoadUsersFromFile(const std::string& filename);
    bool SaveUsersToFile(const std::string& filename) const;
    static bool ValidatePassword(const std::string& password);
    bool UserExists(const std::string& username) const;
    int GetUserCount() const;
    void DisplayUserInfo(const std::string& username) const;
    bool IsAdminUser(const std::string& username) const;
    void ChangeOwnPassword(const std::string& newPassword);
    std::vector<std::string> GetAllUsernames() const;

    // Оператори
    Admin& operator=(const Admin& other);
    Admin& operator=(Admin&& other) noexcept;
    bool operator==(const Admin& other) const;
};