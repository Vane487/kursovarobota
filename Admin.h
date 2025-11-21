#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <functional>

class Admin {
private:
    std::string username;
    std::string password;
    std::unordered_map<std::string, std::string> users;

    void initializeDefaultAdmin();
    std::string hashPassword(const std::string& password) const;
    bool verifyPassword(const std::string& inputPassword, const std::string& storedPassword) const;

public:
    // Конструктори та деструктор
    Admin();
    Admin(const std::string& username, const std::string& password);
    Admin(const Admin& other);
    Admin(Admin&& other) noexcept;
    ~Admin();

    // Getter методи
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::unordered_map<std::string, std::string> getUsers() const { return users; }

    // Setter методи
    void setUsername(const std::string& newUsername);
    void setPassword(const std::string& newPassword);
    void setUsers(const std::unordered_map<std::string, std::string>& newUsers);

    // ВЛАСНІ МЕТОДИ (12+ методів):
    bool addUser(const std::string& username, const std::string& password);
    bool removeUser(const std::string& username);
    bool changePassword(const std::string& username, const std::string& newPassword);
    bool authenticate(const std::string& username, const std::string& password) const;
    void listUsers() const;
    void resetPassword(const std::string& username);
    void exportUsers(const std::string& filename) const;
    bool loadUsersFromFile(const std::string& filename);
    bool saveUsersToFile(const std::string& filename) const;
    static bool validatePassword(const std::string& password);
    bool userExists(const std::string& username) const;
    int getUserCount() const;
    void displayUserInfo(const std::string& username) const;
    bool isAdminUser(const std::string& username) const;
    void changeOwnPassword(const std::string& newPassword);
    std::vector<std::string> getAllUsernames() const;

    // Оператори
    Admin& operator=(const Admin& other);
    Admin& operator=(Admin&& other) noexcept;
    bool operator==(const Admin& other) const;
};