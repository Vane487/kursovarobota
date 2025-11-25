#pragma once
#include <string>
#include <unordered_map>
#include "FileConstants.h"

namespace University {

    enum class UserRole {
        Student,
        Teacher,
        Admin
    };

    struct UserData {
        std::string password;
        UserRole role;

        UserData();
        UserData(const std::string& pwd, UserRole r);
    };

    class UserManager {
    private:
        std::unordered_map<std::string, UserData> m_users;

        // Константи повідомлень
        static const std::string ERROR_EMPTY_USERNAME;
        static const std::string ERROR_USER_EXISTS;
        static const std::string ERROR_USER_NOT_FOUND;
        static const std::string ERROR_DELETE_ADMIN;
        static const std::string ERROR_PASSWORD_LENGTH;
        static const std::string ERROR_PASSWORD_CHARS;
        static const std::string SUCCESS_ADD_USER;
        static const std::string SUCCESS_REMOVE_USER;

    public:
        UserManager();
        UserManager(const UserManager& other);
        UserManager(UserManager&& other) noexcept;
        ~UserManager();

        void InitializeDefaultAdmin();
        std::string RoleToString(UserRole role) const;
        UserRole StringToRole(const std::string& roleStr) const;

        std::string AddUser(const std::string& username, const std::string& password, UserRole role);
        std::string RemoveUser(const std::string& username);
        std::string EditUser(const std::string& username, const std::string& newPassword, int newRole);
        std::string Authenticate(const std::string& username, const std::string& password) const;
        UserRole GetUserRole(const std::string& username) const;

        std::string ListUsers() const;
        std::string ExportUsers(const std::string& filename) const;
        std::string SaveUsersToFile(const std::string& filename) const;
        std::string ValidatePassword(const std::string& password) const;
        std::string GetUserCount() const;
        std::string DisplayUserInfo(const std::string& username) const;
        std::string LoadUsersFromFile(const std::string& filename);
        void ShowUserManagementMenu();
        void HandleAddUser();
        void HandleEditUser();
        void HandleDeleteUser();
        void HandleSearchUser();
        void WaitForEnter() const;

    };

} // namespace University