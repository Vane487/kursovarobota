/**
 * @file MenuManager.h
 * @brief Заголовний файл для менеджеру меню системи управління університетом
 */

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "UserManager.h"
#include "DatabaseManager.h"
#include "FileConstants.h"
#include "AssignmentManager.h"
#include <string>
#include <vector>

namespace University {

/**
 * @class MenuManager
 * @brief Керує користувацькими меню та взаємодією з системою
 *
 * Відповідає за відображення меню, обробку вводу користувача,
 * управління доступом та координацію між різними менеджерами системи.
 */
class MenuManager {
private:
    UserManager* m_userManager;           ///< Вказівник на менеджер користувачів
    DatabaseManager* m_dbManager;         ///< Вказівник на менеджер бази даних
    AssignmentManager* m_assignmentManager; ///< Вказівник на менеджер призначень
    std::string m_currentUser;            ///< Поточний користувач системи
    UserRole m_currentRole;               ///< Роль поточного користувача

public:
    // === КОНСТРУКТОРИ ТА ОПЕРАТОРИ ===

    /**
     * @brief Конструктор з параметрами
     * @param userManager Менеджер користувачів
     * @param dbManager Менеджер бази даних
     * @param assignmentManager Менеджер призначень
     * @param username Ім'я користувача
     * @param role Роль користувача
     */
    MenuManager(UserManager* userManager, DatabaseManager* dbManager,
                AssignmentManager* assignmentManager, const std::string& username, UserRole role);

    /**
     * @brief Конструктор за замовчуванням
     */
    MenuManager();

    /**
     * @brief Конструктор копіювання
     * @param other Об'єкт для копіювання
     */
    MenuManager(const MenuManager& other);

    /**
     * @brief Конструктор переміщення
     * @param other Об'єкт для переміщення
     */
    MenuManager(MenuManager&& other) noexcept;

    /**
     * @brief Деструктор
     */
    ~MenuManager();

    /**
     * @brief Оператор присвоювання копіюванням
     * @param other Об'єкт для копіювання
     * @return Посилання на поточний об'єкт
     */
    MenuManager& operator=(const MenuManager& other);

    /**
     * @brief Оператор присвоювання переміщенням
     * @param other Об'єкт для переміщення
     * @return Посилання на поточний об'єкт
     */
    MenuManager& operator=(MenuManager&& other) noexcept;

    // === ГЕТЕРИ/СЕТЕРИ ===

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

    // === ОСНОВНІ МЕТОДИ ===

    /**
     * @brief Відображає вітальне повідомлення
     */
    void DisplayWelcome() const;

    /**
     * @brief Виконує вихід з системи
     */
    void Logout();

    /**
     * @brief Перевіряє доступ користувача
     * @param requiredRole Необхідна роль для доступу
     * @return true якщо доступ дозволено, false в іншому випадку
     */
    bool ValidateAccess(UserRole requiredRole) const;

    /**
     * @brief Перевіряє, чи є користувач адміністратором
     * @return true якщо користувач адміністратор, false в іншому випадку
     */
    bool IsAdmin() const;

    // === ДОПОМІЖНІ МЕТОДИ ===

    /**
     * @brief Відображає повідомлення про відмову в доступі
     */
    void Denied();

    /**
     * @brief Отримує текстове введення від користувача
     * @param text Запит для користувача
     * @return Введений рядок
     */
    std::string GetInput(const std::string& text);

    /**
     * @brief Отримує цілочисельне введення від користувача
     * @param text Запит для користувача
     * @return Введене число
     */
    int GetIntInput(const std::string& text);

    /**
     * @brief Очищує буфер вводу
     */
    void ClearInputBuffer();

    /**
     * @brief Очищує екран консолі
     */
    void ClearScreen() const;

    /**
     * @brief Чекає натискання клавіші Enter
     */
    void PressAnyKey() const;

    /**
     * @brief Перетворює роль у рядок
     * @param role Роль для перетворення
     * @return Рядкове представлення ролі
     */
    std::string RoleToString(UserRole role) const;

    // === МЕТОДИ ДЛЯ ВИВОДУ СПИСКІВ ===

    /**
     * @brief Виводить список студентів
     * @param list Список студентів
     * @param title Заголовок списку
     */
    void PrintStudentList(const std::vector<Student>& list, const std::string& title) const;

    /**
     * @brief Виводить список викладачів
     * @param list Список викладачів
     * @param title Заголовок списку
     */
    void PrintTeacherList(const std::vector<Teacher>& list, const std::string& title) const;

    /**
     * @brief Виводить список предметів
     * @param list Список предметів
     * @param title Заголовок списку
     */
    void PrintSubjectList(const std::vector<Subject>& list, const std::string& title) const;

    // === ЗАВАНТАЖЕННЯ ДАНИХ ===

    /**
     * @brief Завантажує всі дані з файлів
     */
    void LoadAllData();

    // === МЕТОДИ МЕНЮ ===

    /**
     * @brief Відображає головне меню
     */
    void ShowWelcomeMenu();

    /**
     * @brief Відображає основне меню системи
     */
    void ShowMainMenu();

    /**
     * @brief Відображає меню управління користувачами
     */
    void ShowUserManagement();

    /**
     * @brief Відображає меню управління студентами
     */
    void ShowStudentManagement();

    /**
     * @brief Відображає меню управління викладачами
     */
    void ShowTeacherManagement();

    /**
     * @brief Відображає меню управління предметами
     */
    void ShowSubjectManagement();

    /**
     * @brief Відображає універсальне меню управління
     * @param title Заголовок меню
     * @param type Тип меню (1-студенти, 2-викладачі, 3-предмети)
     */
    void ShowGenericManagementMenu(const std::string& title, int type);

    /**
     * @brief Відображає меню управління призначеннями
     */
    void ShowAssignmentManagement();

    /**
     * @brief Відображає меню пошуку та сортування
     */
    void ShowSearchMenu();

    /**
     * @brief Відображає довідку по системі
     */
    void ShowHelp();

    // === КОНСТАНТИ МЕНЮ ===

    // Файли
    static const std::string STUDENTS_FILE;       ///< Файл студентів
    static const std::string TEACHERS_FILE;       ///< Файл викладачів
    static const std::string SUBJECTS_FILE;       ///< Файл предметів
    static const std::string USERS_FILE;          ///< Файл користувачів
    static const std::string ASSIGNMENTS_FILE;    ///< Файл призначень

    // Головне меню
    static const std::string WELCOME_MENU_TITLE;          ///< Заголовок вітального меню
    static const std::string WELCOME_MENU_OPTION_1;       ///< Опція 1 вітального меню
    static const std::string WELCOME_MENU_OPTION_2;       ///< Опція 2 вітального меню
    static const std::string WELCOME_MENU_OPTION_3;       ///< Опція 3 вітального меню
    static const std::string WELCOME_MENU_PROMPT;         ///< Запит вітального меню

    // Основне меню
    static const std::string MAIN_MENU_TITLE;             ///< Заголовок основного меню
    static const std::string MAIN_MENU_CURRENT_USER;      ///< Інформація про поточного користувача
    static const std::string MAIN_MENU_OPTION_1;          ///< Опція 1 основного меню
    static const std::string MAIN_MENU_OPTION_2;          ///< Опція 2 основного меню
    static const std::string MAIN_MENU_OPTION_3;          ///< Опція 3 основного меню
    static const std::string MAIN_MENU_OPTION_4;          ///< Опція 4 основного меню
    static const std::string MAIN_MENU_OPTION_5;          ///< Опція 5 основного меню
    static const std::string MAIN_MENU_OPTION_6;          ///< Опція 6 основного меню
    static const std::string MAIN_MENU_OPTION_7;          ///< Опція 7 основного меню
    static const std::string MAIN_MENU_OPTION_8;          ///< Опція 8 основного меню
    static const std::string MAIN_MENU_PROMPT;            ///< Запит основного меню
    static const std::string MAIN_MENU_LOCKED;            ///< Позначка заблокованої опції

    // Підменю
    static const std::string SUBMENU_TITLE;               ///< Заголовок підменю
    static const std::string SUBMENU_OPTION_1;            ///< Опція 1 підменю
    static const std::string SUBMENU_OPTION_2;            ///< Опція 2 підменю
    static const std::string SUBMENU_OPTION_3;            ///< Опція 3 підменю
    static const std::string SUBMENU_OPTION_4;            ///< Опція 4 підменю
    static const std::string SUBMENU_OPTION_5;            ///< Опція 5 підменю
    static const std::string SUBMENU_PROMPT;              ///< Запит підменю

    // Меню пошуку
    static const std::string SEARCH_MENU_TITLE;           ///< Заголовок меню пошуку
    static const std::string SEARCH_STUDENT_OPTIONS;      ///< Опції пошуку студентів
    static const std::string SEARCH_TEACHER_OPTIONS;      ///< Опції пошуку викладачів
    static const std::string SEARCH_SUBJECT_OPTIONS;      ///< Опції пошуку предметів
    static const std::string SEARCH_PROMPT;               ///< Запит меню пошуку

    // Загальні повідомлення
    static const std::string ACCESS_DENIED;               ///< Повідомлення про відмову в доступі
    static const std::string ADMIN_ONLY;                  ///< Повідомлення про доступ тільки для адміністраторів
    static const std::string INVALID_CHOICE_MSG;          ///< Повідомлення про невірний вибір
    static const std::string EXIT_SYSTEM_MSG;             ///< Повідомлення про вихід з системи
    static const std::string OPERATION_SUCCESS;           ///< Повідомлення про успішну операцію
    static const std::string NOT_FOUND;                   ///< Повідомлення про відсутність запису
    static const std::string UPDATED_SUCCESS;             ///< Повідомлення про успішне оновлення
    static const std::string DELETED_SUCCESS;             ///< Повідомлення про успішне видалення
    static const std::string ADDED_SUCCESS;               ///< Повідомлення про успішне додавання
    static const std::string SORTED_SUCCESS;              ///< Повідомлення про успішне сортування
    static const std::string PRESS_ENTER;                 ///< Запит натискання Enter

    // Заголовки результатів
    static const std::string SEARCH_RESULTS;              ///< Заголовок результатів пошуку
    static const std::string FILTER_RESULTS;              ///< Заголовок результатів фільтрації
    static const std::string LIST_TITLE;                  ///< Заголовок списку

    // Поля вводу
    static const std::string INPUT_NAME;                  ///< Запит імені
    static const std::string INPUT_LASTNAME;              ///< Запит прізвища
    static const std::string INPUT_EMAIL;                 ///< Запит email
    static const std::string INPUT_ID;                    ///< Запит ID
    static const std::string INPUT_PROGRAM;               ///< Запит освітньої програми
    static const std::string INPUT_DEPARTMENT;            ///< Запит кафедри
    static const std::string INPUT_DEGREE;                ///< Запит наукового ступеня
    static const std::string INPUT_CREDITS;               ///< Запит кредитів
    static const std::string INPUT_SEMESTER;              ///< Запит семестру
    static const std::string INPUT_TEACHER_ID;            ///< Запит ID викладача
    static const std::string INPUT_SEARCH_NAME;           ///< Запит для пошуку
    static const std::string INPUT_SORT_ORDER;            ///< Запит порядку сортування
};

} // namespace University

#endif // MENUMANAGER_H