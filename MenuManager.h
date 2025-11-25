#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "UserManager.h"
#include "DatabaseManager.h"
#include "AssignmentManager.h"
#include "FileConstants.h"
#include <string>
#include <vector>

namespace University {


class MenuManager {
private:
    UserManager* m_userManager;
    DatabaseManager* m_dbManager;
    AssignmentManager* m_assignmentManager;
    std::string m_currentUser;
    UserRole m_currentRole;

public:
    // Конструктори та оператори
    MenuManager(UserManager* userManager, DatabaseManager* dbManager,
                AssignmentManager* assignmentManager, const std::string& username, UserRole role);
    MenuManager();
    MenuManager(const MenuManager& other);
    MenuManager(MenuManager&& other) noexcept;
    ~MenuManager();

    MenuManager& operator=(const MenuManager& other);
    MenuManager& operator=(MenuManager&& other) noexcept;

    // Гетери/Сетери
    UserManager* getUserManager() const;
    void setUserManager(UserManager* userManager);
    DatabaseManager* getDatabaseManager() const;
    void setDatabaseManager(DatabaseManager* dbManager);
    AssignmentManager* getAssignmentManager() const;
    void setAssignmentManager(AssignmentManager* assignmentManager);
    std::string getCurrentUser() const;
    void setCurrentUser(const std::string& user);
    UserRole getCurrentRole() const;
    void setCurrentRole(UserRole role);

    // Основні методи
    void DisplayWelcome() const;
    void Logout();
    bool ValidateAccess(UserRole requiredRole) const;
    bool IsAdmin() const;

    // Допоміжні методи
    void Denied();
    std::string GetInput(const std::string& text);
    int GetIntInput(const std::string& text);
    void ClearInputBuffer();
    void ClearScreen() const;
    void PressAnyKey() const;
    std::string RoleToString(UserRole role) const;

    // Методи для виводу списків
    void PrintStudentList(const std::vector<Student>& list, const std::string& title) const;
    void PrintTeacherList(const std::vector<Teacher>& list, const std::string& title) const;
    void PrintSubjectList(const std::vector<Subject>& list, const std::string& title) const;

    // Завантаження даних
    void LoadAllData();

    // Методи меню
    void ShowWelcomeMenu();
    void ShowMainMenu();
    void ShowUserManagement();
    void ShowStudentManagement();
    void ShowTeacherManagement();
    void ShowSubjectManagement();
    void ShowGenericManagementMenu(const std::string& title, int type);
    void ShowAssignmentManagement();
    void ShowSearchMenu();
    void ShowHelp();

    // Константи
    static const std::string WELCOME_MENU_TITLE;
    static const std::string WELCOME_MENU_OPTION_1;
    static const std::string WELCOME_MENU_OPTION_2;
    static const std::string WELCOME_MENU_OPTION_3;
    static const std::string WELCOME_MENU_PROMPT;

    static const std::string MAIN_MENU_TITLE;
    static const std::string MAIN_MENU_CURRENT_USER;
    static const std::string MAIN_MENU_OPTION_1;
    static const std::string MAIN_MENU_OPTION_2;
    static const std::string MAIN_MENU_OPTION_3;
    static const std::string MAIN_MENU_OPTION_4;
    static const std::string MAIN_MENU_OPTION_5;
    static const std::string MAIN_MENU_OPTION_6;
    static const std::string MAIN_MENU_OPTION_7;
    static const std::string MAIN_MENU_OPTION_8;
    static const std::string MAIN_MENU_PROMPT;
    static const std::string MAIN_MENU_LOCKED;

    static const std::string SUBMENU_TITLE;
    static const std::string SUBMENU_OPTION_1;
    static const std::string SUBMENU_OPTION_2;
    static const std::string SUBMENU_OPTION_3;
    static const std::string SUBMENU_OPTION_4;
    static const std::string SUBMENU_OPTION_5;
    static const std::string SUBMENU_PROMPT;

    static const std::string SEARCH_MENU_TITLE;
    static const std::string SEARCH_STUDENT_OPTIONS;
    static const std::string SEARCH_TEACHER_OPTIONS;
    static const std::string SEARCH_SUBJECT_OPTIONS;
    static const std::string SEARCH_PROMPT;

    static const std::string ACCESS_DENIED;
    static const std::string ADMIN_ONLY;
    static const std::string INVALID_CHOICE_MSG;
    static const std::string EXIT_SYSTEM_MSG;
    static const std::string OPERATION_SUCCESS;
    static const std::string NOT_FOUND;
    static const std::string UPDATED_SUCCESS;
    static const std::string DELETED_SUCCESS;
    static const std::string ADDED_SUCCESS;
    static const std::string SORTED_SUCCESS;
    static const std::string PRESS_ENTER;

    static const std::string SEARCH_RESULTS;
    static const std::string FILTER_RESULTS;
    static const std::string LIST_TITLE;

    static const std::string INPUT_NAME;
    static const std::string INPUT_LASTNAME;
    static const std::string INPUT_EMAIL;
    static const std::string INPUT_ID;
    static const std::string INPUT_PROGRAM;
    static const std::string INPUT_DEPARTMENT;
    static const std::string INPUT_DEGREE;
    static const std::string INPUT_CREDITS;
    static const std::string INPUT_SEMESTER;
    static const std::string INPUT_TEACHER_ID;
    static const std::string INPUT_SEARCH_NAME;
    static const std::string INPUT_SORT_ORDER;
};

} // namespace University

#endif // MENUMANAGER_H