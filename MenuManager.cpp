#include "MenuManager.h"
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;
using namespace University;

// Ініціалізація констант для стартового меню
const string MenuManager::WELCOME_MENU_TITLE =
    "===========================================\n"
    "      СИСТЕМА УПРАВЛІННЯ УНІВЕРСИТЕТОМ\n"
    "===========================================";

const string MenuManager::WELCOME_MENU_OPTION_1 = "1. Увійти до системи";
const string MenuManager::WELCOME_MENU_OPTION_2 = "2. Допомога";
const string MenuManager::WELCOME_MENU_OPTION_3 = "3. Вийти";
const string MenuManager::WELCOME_MENU_PROMPT = "Оберіть опцію: ";

// Ініціалізація констант для головного меню
const string MenuManager::MAIN_MENU_TITLE = "=============== ГОЛОВНЕ МЕНЮ ===============";
const string MenuManager::MAIN_MENU_CURRENT_USER = "Користувач: ";
const string MenuManager::MAIN_MENU_OPTION_1 = "1. Управління користувачами";
const string MenuManager::MAIN_MENU_OPTION_2 = "2. Управління студентами";
const string MenuManager::MAIN_MENU_OPTION_3 = "3. Управління викладачами";
const string MenuManager::MAIN_MENU_OPTION_4 = "4. Управління предметами";
const string MenuManager::MAIN_MENU_OPTION_5 = "5. Призначення на предмети";
const string MenuManager::MAIN_MENU_OPTION_6 = "6. Пошук / Сортування / Фільтрація";
const string MenuManager::MAIN_MENU_OPTION_7 = "7. Допомога";
const string MenuManager::MAIN_MENU_OPTION_8 = "8. Вийти";
const string MenuManager::MAIN_MENU_PROMPT = "Оберіть пункт меню: ";
const string MenuManager::MAIN_MENU_LOCKED = " (🔒)";

// Константи для підменю управління
const string MenuManager::SUBMENU_TITLE = "=== УПРАВЛІННЯ ===";
const string MenuManager::SUBMENU_OPTION_1 = "1. Переглянути всі записи";
const string MenuManager::SUBMENU_OPTION_2 = "2. Додати запис";
const string MenuManager::SUBMENU_OPTION_3 = "3. Редагувати запис";
const string MenuManager::SUBMENU_OPTION_4 = "4. Видалити запис";
const string MenuManager::SUBMENU_OPTION_5 = "5. Пошук записів";
const string MenuManager::SUBMENU_PROMPT = "Оберіть опцію: ";

// Константи для меню пошуку
const string MenuManager::SEARCH_MENU_TITLE = "=== ПОШУК / СОРТУВАННЯ / ФІЛЬТРАЦІЯ ===";
const string MenuManager::SEARCH_STUDENT_OPTIONS =
    "=== СТУДЕНТИ ===\n"
    "1. Пошук за ім'ям\n"
    "2. Фільтрація за програмою\n"
    "3. Сортування за ім'ям";
const string MenuManager::SEARCH_TEACHER_OPTIONS =
    "=== ВИКЛАДАЧІ ===\n"
    "4. Пошук за ім'ям\n"
    "5. Фільтрація за кафедрою\n"
    "6. Сортування за ім'ям";
const string MenuManager::SEARCH_SUBJECT_OPTIONS =
    "=== ПРЕДМЕТИ ===\n"
    "7. Пошук за назвою\n"
    "8. Фільтрація за семестром\n"
    "9. Сортування за назвою";
const string MenuManager::SEARCH_PROMPT = "Оберіть опцію (0 - назад): ";

// Загальні текстові константи
const string MenuManager::ACCESS_DENIED = "Доступ заборонено!";
const string MenuManager::ADMIN_ONLY = " Ця дія доступна лише адміністраторам.";
const string MenuManager::INVALID_CHOICE_MSG = "Невірний вибір!";
const string MenuManager::EXIT_SYSTEM_MSG = "Вихід з системи...";
const string MenuManager::OPERATION_SUCCESS = "Операція успішна!";
const string MenuManager::NOT_FOUND = "Запис не знайдено!";
const string MenuManager::UPDATED_SUCCESS = "Запис оновлено!";
const string MenuManager::DELETED_SUCCESS = "Запис видалено!";
const string MenuManager::ADDED_SUCCESS = "Запис додано!";
const string MenuManager::SORTED_SUCCESS = "Відсортовано успішно!";
const string MenuManager::PRESS_ENTER = "\nНатисніть Enter, щоб продовжити...";

// Тексти результатів
const string MenuManager::SEARCH_RESULTS = "РЕЗУЛЬТАТИ ПОШУКУ";
const string MenuManager::FILTER_RESULTS = "РЕЗУЛЬТАТИ ФІЛЬТРАЦІЇ";
const string MenuManager::LIST_TITLE = "СПИСОК ЗАПИСІВ";

// Поля вводу
const string MenuManager::INPUT_NAME = "Введіть ім'я: ";
const string MenuManager::INPUT_LASTNAME = "Введіть прізвище: ";
const string MenuManager::INPUT_EMAIL = "Введіть email: ";
const string MenuManager::INPUT_ID = "Введіть ID: ";
const string MenuManager::INPUT_PROGRAM = "Введіть освітню програму: ";
const string MenuManager::INPUT_DEPARTMENT = "Введіть кафедру: ";
const string MenuManager::INPUT_DEGREE = "Введіть ступінь (1-Бакалавр, 2-Магістр, 3-Доктор): ";
const string MenuManager::INPUT_CREDITS = "Введіть кредити: ";
const string MenuManager::INPUT_SEMESTER = "Введіть семестр: ";
const string MenuManager::INPUT_TEACHER_ID = "Введіть ID викладача: ";
const string MenuManager::INPUT_SEARCH_NAME = "Введіть ім'я/назву для пошуку: ";
const string MenuManager::INPUT_SORT_ORDER = "Порядок сортування (1 - зростання, 0 - спадання): ";

// Конструктори та оператори
MenuManager::MenuManager(UserManager* userManager, DatabaseManager* dbManager,
                         AssignmentManager* assignmentManager, const string& username, UserRole role)
    : m_userManager(userManager), m_dbManager(dbManager), m_assignmentManager(assignmentManager),
      m_currentUser(username), m_currentRole(role) {}

MenuManager::MenuManager() : m_userManager(nullptr), m_dbManager(nullptr),
                            m_assignmentManager(nullptr), m_currentUser(""),
                            m_currentRole(UserRole::Student) {}

MenuManager::MenuManager(const MenuManager& other)
    : m_userManager(other.m_userManager), m_dbManager(other.m_dbManager),
      m_assignmentManager(other.m_assignmentManager), m_currentUser(other.m_currentUser),
      m_currentRole(other.m_currentRole) {}

MenuManager::MenuManager(MenuManager&& other) noexcept
    : m_userManager(other.m_userManager), m_dbManager(other.m_dbManager),
      m_assignmentManager(other.m_assignmentManager),
m_currentUser(std::move(other.m_currentUser)), m_currentRole(other.m_currentRole) {
    other.m_userManager = nullptr;
    other.m_dbManager = nullptr;
    other.m_assignmentManager = nullptr;
}

MenuManager::~MenuManager() {
    cout << "MenuManager для користувача " << m_currentUser << " знищено" << endl;
}

MenuManager& MenuManager::operator=(const MenuManager& other) {
    if (this != &other) {
        m_userManager = other.m_userManager;
        m_dbManager = other.m_dbManager;
        m_assignmentManager = other.m_assignmentManager;
        m_currentUser = other.m_currentUser;
        m_currentRole = other.m_currentRole;
    }
    return *this;
}

MenuManager& MenuManager::operator=(MenuManager&& other) noexcept {
    if (this != &other) {
        m_userManager = other.m_userManager;
        m_dbManager = other.m_dbManager;
        m_assignmentManager = other.m_assignmentManager;
        m_currentUser = std::move(other.m_currentUser);
        m_currentRole = other.m_currentRole;
        other.m_userManager = nullptr;
        other.m_dbManager = nullptr;
        other.m_assignmentManager = nullptr;
    }
    return *this;
}

// Гетери/Сетери
UserManager* MenuManager::getUserManager() const { return m_userManager; }
void MenuManager::setUserManager(UserManager* userManager) { m_userManager = userManager; }
DatabaseManager* MenuManager::getDatabaseManager() const { return m_dbManager; }
void MenuManager::setDatabaseManager(DatabaseManager* dbManager) { m_dbManager = dbManager; }
AssignmentManager* MenuManager::getAssignmentManager() const { return m_assignmentManager; }
void MenuManager::setAssignmentManager(AssignmentManager* assignmentManager) { m_assignmentManager = assignmentManager; }
string MenuManager::getCurrentUser() const { return m_currentUser; }
void MenuManager::setCurrentUser(const string& user) { m_currentUser = user; }
UserRole MenuManager::getCurrentRole() const { return m_currentRole; }
void MenuManager::setCurrentRole(UserRole role) { m_currentRole = role; }

// Основні методи
void MenuManager::DisplayWelcome() const {
    cout << "Ласкаво просимо, " << m_currentUser << "!" << endl;
}

void MenuManager::Logout() {
    m_currentUser = "";
    m_currentRole = UserRole::Student;
    cout << "Вихід виконано успішно" << endl;
}

bool MenuManager::ValidateAccess(UserRole requiredRole) const {
    return m_currentRole >= requiredRole;
}

bool MenuManager::IsAdmin() const {
    return m_currentRole == UserRole::Admin;
}

// Допоміжні методи
void MenuManager::Denied() {
    cout << ACCESS_DENIED << ADMIN_ONLY << endl;
    PressAnyKey();
}

string MenuManager::GetInput(const string& text) {
    cout << text;
    string s;
    getline(cin, s);
    return s;
}

int MenuManager::GetIntInput(const string& text) {
    cout << text;
    int x;
    cin >> x;
    ClearInputBuffer();
    return x;
}

void MenuManager::ClearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void MenuManager::ClearScreen() const {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}

void MenuManager::PressAnyKey() const {
    cout << PRESS_ENTER;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string MenuManager::RoleToString(UserRole role) const {
    switch (role) {
        case UserRole::Admin: return FileConstants::ROLE_ADMIN;
        case UserRole::Teacher: return FileConstants::ROLE_TEACHER;
        case UserRole::Student: return FileConstants::ROLE_STUDENT;
        default: return "Невідома роль";
    }
}

// Методи для виводу списків
void MenuManager::PrintStudentList(const vector<Student>& list, const string& title) const {
    cout << "\n=== " << title << " ===\n";
    if (list.empty()) {
        cout << "Студенти відсутні\n";
        return;
    }
    for (const auto& student : list) {
        cout << "ID: " << student.getStudentID()
             << " | Ім'я: " << student.getName()
             << " " << student.getLastName()
             << " | Email: " << student.getEmail()
             << " | Програма: " << student.getEducationalProgram() << "\n";
    }
    cout << "Всього студентів: " << list.size() << "\n";
}

void MenuManager::PrintTeacherList(const vector<Teacher>& list, const string& title) const {
    cout << "\n=== " << title << " ===\n";
    if (list.empty()) {
        cout << "Викладачі відсутні\n";
        return;
    }
    for (const auto& teacher : list) {
        string degreeStr;
        switch(teacher.getAcademicDegree()) {
            case AcademicDegree::BACHELOR: degreeStr = "Бакалавр"; break;
            case AcademicDegree::MASTER: degreeStr = "Магістр"; break;
            case AcademicDegree::DOCTOR: degreeStr = "Доктор"; break;
            default: degreeStr = "Невідомий";
        }

        cout << "ID: " << teacher.getTeacherID()
             << " | Ім'я: " << teacher.getName()
             << " " << teacher.getLastName()
             << " | Email: " << teacher.getEmail()
             << " | Кафедра: " << teacher.getDepartment()
             << " | Ступінь: " << degreeStr << "\n";
    }
    cout << "Всього викладачів: " << list.size() << "\n";
}

void MenuManager::PrintSubjectList(const vector<Subject>& list, const string& title) const {
    cout << "\n=== " << title << " ===\n";
    if (list.empty()) {
        cout << "Предмети відсутні\n";
        return;
    }
    for (const auto& subject : list) {
        cout << "ID: " << subject.getSubjectId()
             << " | Назва: " << subject.getSubjectName()
             << " | Кредити: " << subject.getEctsCredits()
             << " | Викладач ID: " << subject.getTeacherId()
             << " | Семестр: " << subject.getSemester() << "\n";
    }
    cout << "Всього предметів: " << list.size() << "\n";
}

// НОВИЙ МЕТОД: Завантаження всіх даних
void MenuManager::LoadAllData() {
    if (m_dbManager && m_userManager) {
        cout << "Завантаження даних з файлів..." << endl;

        m_dbManager->LoadStudentsFromFile(FileConstants::STUDENTS_FILE);
        m_dbManager->LoadTeachersFromFile(FileConstants::TEACHERS_FILE);
        m_dbManager->LoadSubjectsFromFile(FileConstants::SUBJECTS_FILE);
        m_userManager->LoadUsersFromFile(FileConstants::USERS_FILE);

        cout << "Дані успішно завантажені!" << endl;
        PressAnyKey();
    }
}

// Меню
void MenuManager::ShowWelcomeMenu() {
    LoadAllData();

    int choice;
    do {
        ClearScreen();
        cout << WELCOME_MENU_TITLE << "\n\n";
        cout << WELCOME_MENU_OPTION_1 << "\n";
        cout << WELCOME_MENU_OPTION_2 << "\n";
        cout << WELCOME_MENU_OPTION_3 << "\n\n";
        cout << WELCOME_MENU_PROMPT;

        cin >> choice;
        ClearInputBuffer();

        switch (choice) {
            case 1: {
                string username = GetInput(FileConstants::MSG_LOGIN_PROMPT);
                string password = GetInput(FileConstants::MSG_PASSWORD_PROMPT);

                string authResult = m_userManager->Authenticate(username, password);
                if (authResult.find("УСПІХ") != string::npos) {
                    m_currentUser = username;
                    m_currentRole = m_userManager->GetUserRole(username);
                    cout << FileConstants::MSG_LOGIN_SUCCESS << endl;
                    PressAnyKey();
                    ShowMainMenu();
                } else {
                    cout << FileConstants::MSG_LOGIN_FAILED << endl;
                    PressAnyKey();
                }
                break;
            }
            case 2:
                ShowHelp();
                break;
            case 3:
                cout << FileConstants::MSG_EXIT_SYSTEM << endl;
                return;
            default:
                cout << INVALID_CHOICE_MSG << endl;
                PressAnyKey();
        }
    } while (true);
}

void MenuManager::ShowMainMenu() {
    int choice;
    do {
        ClearScreen();
        cout << MAIN_MENU_TITLE << "\n\n";
        cout << MAIN_MENU_CURRENT_USER << m_currentUser << "    |    Роль: " << RoleToString(m_currentRole) << "\n\n";

        cout << MAIN_MENU_OPTION_1 << (IsAdmin() ? "" : MAIN_MENU_LOCKED) << "\n";
        cout << MAIN_MENU_OPTION_2 << "\n";
        cout << MAIN_MENU_OPTION_3 << "\n";
        cout << MAIN_MENU_OPTION_4 << "\n";
        cout << MAIN_MENU_OPTION_5 << "\n";
        cout << MAIN_MENU_OPTION_6 << "\n";
        cout << MAIN_MENU_OPTION_7 << "\n";
        cout << MAIN_MENU_OPTION_8 << "\n\n";
        cout << MAIN_MENU_PROMPT;

        cin >> choice;
        ClearInputBuffer();

        if (choice == 1 && !IsAdmin()) {
            Denied();
            continue;
        }

        switch (choice) {
            case 1: ShowUserManagement(); break;
            case 2: ShowStudentManagement(); break;
            case 3: ShowTeacherManagement(); break;
            case 4: ShowSubjectManagement(); break;
            case 5: ShowAssignmentManagement(); break;
            case 6: ShowSearchMenu(); break;
            case 7: ShowHelp(); break;
            case 8:
                cout << FileConstants::MSG_EXIT_SYSTEM << endl;
                return;
            default:
                cout << INVALID_CHOICE_MSG << endl;
                PressAnyKey();
        }
    } while (true);
}

void MenuManager::ShowUserManagement() {
    if (!IsAdmin()) {
        Denied();
        return;
    }

    int choice;
    do {
        ClearScreen();
        cout << SUBMENU_TITLE << " - КОРИСТУВАЧІ\n\n";
        cout << SUBMENU_OPTION_1 << "\n";
        cout << SUBMENU_OPTION_2 << "\n";
        cout << SUBMENU_OPTION_3 << "\n";
        cout << SUBMENU_OPTION_4 << "\n";
        cout << SUBMENU_OPTION_5 << "\n";
        cout << "0. Назад\n\n";
        cout << SUBMENU_PROMPT;

        cin >> choice;
        ClearInputBuffer();

        switch (choice) {
            case 1:
                cout << m_userManager->ListUsers() << endl;
                PressAnyKey();
                break;
            case 2: {
                string username = GetInput("Введіть ім'я користувача: ");
                string password = GetInput("Введіть пароль: ");
                int roleChoice = GetIntInput("Виберіть роль (1-Студент, 2-Викладач, 3-Адмін): ");

                UserRole role = UserRole::Student;
                if (roleChoice == 2) role = UserRole::Teacher;
                else if (roleChoice == 3) role = UserRole::Admin;

                string result = m_userManager->AddUser(username, password, role);
                cout << result << endl;
                PressAnyKey();
                break;
            }

            case 3: {
                string username = GetInput("Введіть ім'я користувача для редагування: ");
                string currentInfo = m_userManager->DisplayUserInfo(username);
                cout << currentInfo << endl;

                if (currentInfo.find("не знайдено") == string::npos) {
                    string newPassword = GetInput("Введіть новий пароль: ");
                    int newRole = GetIntInput("Введіть нову роль (1-Студент, 2-Викладач, 3-Адмін): ");

                    string result = m_userManager->EditUser(username, newPassword, newRole);
                    cout << result << endl;
                } else {
                    cout << "Користувача не знайдено." << endl;
                }
                PressAnyKey();
                break;
            }
            case 4: {
                string username = GetInput("Введіть ім'я користувача для видалення: ");
                string result = m_userManager->RemoveUser(username);
                cout << result << endl;
                PressAnyKey();
                break;
            }
            case 5: {
                string username = GetInput("Введіть ім'я користувача для пошуку: ");
                string result = m_userManager->DisplayUserInfo(username);
                cout << result << endl;
                PressAnyKey();
                break;
            }
            case 0:
                break;
            default:
                cout << INVALID_CHOICE_MSG << endl;
                PressAnyKey();
        }
    } while (choice != 0);
}

void MenuManager::ShowStudentManagement() {
    ShowGenericManagementMenu("СТУДЕНТИ", 1);
}

void MenuManager::ShowTeacherManagement() {
    ShowGenericManagementMenu("ВИКЛАДАЧІ", 2);
}

void MenuManager::ShowSubjectManagement() {
    ShowGenericManagementMenu("ПРЕДМЕТИ", 3);
}

void MenuManager::ShowGenericManagementMenu(const string& title, int type) {
    int choice;
    do {
        ClearScreen();
        cout << SUBMENU_TITLE << " - " << title << "\n\n";
        cout << SUBMENU_OPTION_1 << "\n";
        cout << SUBMENU_OPTION_2 << (IsAdmin() ? "" : MAIN_MENU_LOCKED) << "\n";
        cout << SUBMENU_OPTION_3 << (IsAdmin() ? "" : MAIN_MENU_LOCKED) << "\n";
        cout << SUBMENU_OPTION_4 << (IsAdmin() ? "" : MAIN_MENU_LOCKED) << "\n";
        cout << SUBMENU_OPTION_5 << "\n";
        cout << "0. Назад\n\n";
        cout << SUBMENU_PROMPT;

        cin >> choice;
        ClearInputBuffer();

        if (!IsAdmin() && (choice == 2 || choice == 3 || choice == 4)) {
            Denied();
            continue;
        }

        switch (choice) {
            case 1:
                if (type == 1) PrintStudentList(m_dbManager->GetAllStudents(), LIST_TITLE + " - СТУДЕНТИ");
                else if (type == 2) PrintTeacherList(m_dbManager->GetAllTeachers(), LIST_TITLE + " - ВИКЛАДАЧІ");
                else if (type == 3) PrintSubjectList(m_dbManager->GetAllSubjects(), LIST_TITLE + " - ПРЕДМЕТИ");
                PressAnyKey();
                break;

            case 2:
                if (type == 1) {
                    string name = GetInput(INPUT_NAME);
                    string last = GetInput(INPUT_LASTNAME);
                    string email = GetInput(INPUT_EMAIL);
                    string id = GetInput(INPUT_ID);
                    string program = GetInput(INPUT_PROGRAM);

                    try {
                        m_dbManager->AddStudent(Student(name, last, email, id, program));
                        cout << ADDED_SUCCESS << endl;
                    } catch (const exception& e) {
                        cout << "ПОМИЛКА: " << e.what() << endl;
                    }
                }
                else if (type == 2) {
                    string name = GetInput(INPUT_NAME);
                    string last = GetInput(INPUT_LASTNAME);
                    string email = GetInput(INPUT_EMAIL);
                    string id = GetInput(INPUT_ID);
                    string dept = GetInput(INPUT_DEPARTMENT);
                    int deg = GetIntInput(INPUT_DEGREE);

                    AcademicDegree d = (deg == 2 ? AcademicDegree::MASTER :
                                       deg == 3 ? AcademicDegree::DOCTOR :
                                                  AcademicDegree::BACHELOR);

                    try {
                        m_dbManager->AddTeacher(Teacher(name, last, email, id, dept, d));
                        cout << ADDED_SUCCESS << endl;
                    } catch (const exception& e) {
                        cout << "ПОМИЛКА: " << e.what() << endl;
                    }
                }
                else if (type == 3) {
                    string id = GetInput(INPUT_ID);
                    string name = GetInput(INPUT_NAME);
                    int credits = GetIntInput(INPUT_CREDITS);
                    string teacher = GetInput(INPUT_TEACHER_ID);
                    int sem = GetIntInput(INPUT_SEMESTER);

                    try {
                        m_dbManager->AddSubject(Subject(id, name, credits, teacher, sem));
                        cout << ADDED_SUCCESS << endl;
                    } catch (const exception& e) {
                        cout << "ПОМИЛКА: " << e.what() << endl;
                    }
                }
                PressAnyKey();
                break;

            case 3: {
                string id = GetInput("Введіть ID для редагування: ");
                bool found = false;

                if (type == 1) {
                    auto* s = m_dbManager->GetStudent(id);
                    if (s) {
                        string name = GetInput("Нове ім'я: ");
                        string last = GetInput("Нове прізвище: ");
                        string email = GetInput("Новий email: ");
                        string program = GetInput("Нова освітня програма: ");

                        Student upd(name, last, email, id, program);
                        m_dbManager->EditStudent(id, upd);
                        cout << UPDATED_SUCCESS << endl;
                        found = true;
                    }
                }
                else if (type == 2) {
                    auto* t = m_dbManager->GetTeacher(id);
                    if (t) {
                        string name = GetInput("Нове ім'я: ");
                        string last = GetInput("Нове прізвище: ");
                        string email = GetInput("Новий email: ");
                        string dept = GetInput("Нова кафедра: ");
                        int deg = GetIntInput("Новий ступінь (1,2,3): ");

                        AcademicDegree d = (deg == 2 ? AcademicDegree::MASTER :
                                           deg == 3 ? AcademicDegree::DOCTOR :
                                                      AcademicDegree::BACHELOR);

                        m_dbManager->EditTeacher(id, Teacher(name, last, email, id, dept, d));
                        cout << UPDATED_SUCCESS << endl;
                        found = true;
                    }
                }
                else if (type == 3) {
                    auto* s = m_dbManager->GetSubject(id);
                    if (s) {
                        string name = GetInput("Нова назва: ");
                        int credits = GetIntInput("Нові кредити: ");
                        string teacher = GetInput("Новий ID викладача: ");
                        int sem = GetIntInput("Новий семестр: ");

                        m_dbManager->EditSubject(id, Subject(id, name, credits, teacher, sem));
                        cout << UPDATED_SUCCESS << endl;
                        found = true;
                    }
                }

                if (!found) cout << NOT_FOUND << endl;
                PressAnyKey();
                break;
            }

            case 4: {
                string id = GetInput("Введіть ID для видалення: ");
                bool success = false;

                if (type == 1) success = m_dbManager->DeleteStudent(id);
                else if (type == 2) success = m_dbManager->DeleteTeacher(id);
                else if (type == 3) success = m_dbManager->DeleteSubject(id);

                cout << (success ? DELETED_SUCCESS : NOT_FOUND) << endl;
                PressAnyKey();
                break;
            }

            case 5: {
                string search = GetInput("Введіть ім'я для пошуку: ");
                if (type == 1) PrintStudentList(m_dbManager->SearchStudentsByName(search), SEARCH_RESULTS);
                else if (type == 2) PrintTeacherList(m_dbManager->SearchTeachersByName(search), SEARCH_RESULTS);
                else if (type == 3) PrintSubjectList(m_dbManager->SearchSubjectsByName(search), SEARCH_RESULTS);
                PressAnyKey();
                break;
            }

            case 0:
                break;

            default:
                cout << INVALID_CHOICE_MSG << endl;
                PressAnyKey();
        }
    } while (choice != 0);
}

void MenuManager::ShowAssignmentManagement() {
    int choice;
    do {
        ClearScreen();
        cout << "=== ПРИЗНАЧЕННЯ НА ПРЕДМЕТИ ===\n\n";
        cout << "1. Призначити викладача на предмет\n";
        cout << "2. Видалити призначення\n";
        cout << "3. Переглянути всі призначення\n";
        cout << "4. Перевірити статус викладача\n";
        cout << "5. Записати студента на предмет\n";
        cout << "6. Видалити студента з предмету\n";
        cout << "7. Переглянути записи студентів\n";
        cout << "0. Назад\n\n";
        cout << "Оберіть опцію: ";

        cin >> choice;
        ClearInputBuffer();

        try {
            switch (choice) {
                case 1: {
                    string teacherId = GetInput("Введіть ID викладача: ");
                    string subjectId = GetInput("Введіть ID предмета: ");

                    // Перевірка чи існує викладач
                    Teacher* teacher = m_dbManager->GetTeacher(teacherId);
                    if (!teacher) {
                        cout << "Помилка: Викладач з ID " << teacherId << " не знайдений!\n";
                        PressAnyKey();
                        break;
                    }

                    // Перевірка чи існує предмет
                    Subject* subject = m_dbManager->GetSubject(subjectId);
                    if (!subject) {
                        cout << "Помилка: Предмет з ID " << subjectId << " не знайдений!\n";
                        PressAnyKey();
                        break;
                    }

                    if (m_assignmentManager->assignToSubject(teacherId, subjectId)) {
                        cout << "Призначення успішне!\n";
                    }
                    PressAnyKey();
                    break;
                }
                case 2: {
                    string teacherId = GetInput("Введіть ID викладача для видалення призначення: ");

                    // Перевірка чи існує викладач
                    Teacher* teacher = m_dbManager->GetTeacher(teacherId);
                    if (!teacher) {
                        cout << "Помилка: Викладач з ID " << teacherId << " не знайдений!\n";
                        PressAnyKey();
                        break;
                    }

                    if (m_assignmentManager->removeFromSubject(teacherId)) {
                        cout << "Призначення видалено!\n";
                    }
                    PressAnyKey();
                    break;
                }
                case 3: {
                    auto assignments = m_assignmentManager->getAllTeacherAssignments();
                    cout << "\n=== ВСІ ПРИЗНАЧЕННЯ ВИКЛАДАЧІВ ===\n";
                    if (assignments.empty()) {
                        cout << "Призначень немає\n";
                    } else {
                        for (const auto& assignment : assignments) {
                            Teacher* teacher = m_dbManager->GetTeacher(assignment.first);
                            Subject* subject = m_dbManager->GetSubject(assignment.second);

                            string teacherName = teacher ? teacher->getFullName() : "Невідомий викладач";
                            string subjectName = subject ? subject->getSubjectName() : "Невідомий предмет";

                            cout << "Викладач: " << assignment.first << " (" << teacherName
                                 << ") -> Предмет: " << assignment.second << " (" << subjectName << ")\n";
                        }
                    }
                    PressAnyKey();
                    break;
                }
                case 4: {
                    string teacherId = GetInput("Введіть ID викладача: ");

                    // Перевірка чи існує викладач
                    Teacher* teacher = m_dbManager->GetTeacher(teacherId);
                    if (!teacher) {
                        cout << "Помилка: Викладач з ID " << teacherId << " не знайдений!\n";
                        PressAnyKey();
                        break;
                    }

                    // ВИПРАВЛЕННЯ: Додаємо другий параметр m_dbManager
                    string status = m_assignmentManager->getDetailedTeachingStatus(teacherId, m_dbManager);
                    cout << "Статус: " << status << endl;

                    // Додаткова інформація про викладача
                    cout << "\nІнформація про викладача:\n";
                    cout << " - Ім'я: " << teacher->getFullName() << "\n";
                    cout << " - Кафедра: " << teacher->getDepartment() << "\n";
                    cout << " - Email: " << teacher->getEmail() << "\n";

                    PressAnyKey();
                    break;
                }
                case 5: {
                    string studentId = GetInput("Введіть ID студента: ");
                    string subjectId = GetInput("Введіть ID предмета: ");

                    // Перевірка чи існує студент
                    Student* student = m_dbManager->GetStudent(studentId);
                    if (!student) {
                        cout << "Помилка: Студент з ID " << studentId << " не знайдений!\n";
                        PressAnyKey();
                        break;
                    }

                    // Перевірка чи існує предмет
                    Subject* subject = m_dbManager->GetSubject(subjectId);
                    if (!subject) {
                        cout << "Помилка: Предмет з ID " << subjectId << " не знайдений!\n";
                        PressAnyKey();
                        break;
                    }

                    if (m_assignmentManager->enrollStudentInSubject(studentId, subjectId)) {
                        cout << "Студента успішно записано на предмет!\n";
                    }
                    PressAnyKey();
                    break;
                }
                case 6: {
                    string studentId = GetInput("Введіть ID студента: ");
                    string subjectId = GetInput("Введіть ID предмета: ");

                    if (m_assignmentManager->unenrollStudentFromSubject(studentId, subjectId)) {
                        cout << "Студента успішно видалено з предмету!\n";
                    } else {
                        cout << "Запис не знайдено!\n";
                    }
                    PressAnyKey();
                    break;
                }
                case 7: {
                    // ВИПРАВЛЕННЯ: Замінюємо getAllStudentEnrollments на пошук через всіх студентів
                    cout << "\n=== ВСІ ЗАПИСИ СТУДЕНТІВ ===\n";
                    vector<Student> allStudents = m_dbManager->GetAllStudents();
                    bool foundEnrollments = false;

                    for (const auto& student : allStudents) {
                        string studentId = student.getStudentID();
                        vector<string> studentSubjects = m_assignmentManager->getStudentSubjects(studentId);

                        if (!studentSubjects.empty()) {
                            foundEnrollments = true;
                            cout << "Студент: " << studentId << " (" << student.getFullName() << ") -> Предмети: ";

                            for (size_t i = 0; i < studentSubjects.size(); ++i) {
                                Subject* subject = m_dbManager->GetSubject(studentSubjects[i]);
                                string subjectName = subject ? subject->getSubjectName() : "Невідомий предмет";
                                cout << studentSubjects[i] << " (" << subjectName << ")";
                                if (i < studentSubjects.size() - 1) cout << ", ";
                            }
                            cout << "\n";
                        }
                    }

                    if (!foundEnrollments) {
                        cout << "Записів немає\n";
                    }
                    PressAnyKey();
                    break;
                }
                case 0:
                    break;
                default:
                    cout << INVALID_CHOICE_MSG << endl;
                    PressAnyKey();
            }
        } catch (const std::exception& e) {
            cout << "ПОМИЛКА: " << e.what() << endl;
            PressAnyKey();
        }
    } while (choice != 0);
}

void MenuManager::ShowSearchMenu() {
    int choice;
    do {
        ClearScreen();
        cout << SEARCH_MENU_TITLE << "\n\n";
        cout << SEARCH_STUDENT_OPTIONS << "\n\n";
        cout << SEARCH_TEACHER_OPTIONS << "\n\n";
        cout << SEARCH_SUBJECT_OPTIONS << "\n\n";
        cout << "0. Назад до головного меню\n\n";
        cout << SEARCH_PROMPT;

        cin >> choice;
        ClearInputBuffer();

        switch (choice) {
            case 1: {
                string name = GetInput(INPUT_SEARCH_NAME);
                auto results = m_dbManager->SearchStudentsByName(name);
                PrintStudentList(results, SEARCH_RESULTS + " - Студенти");
                PressAnyKey();
                break;
            }
            case 2: {
                string program = GetInput(INPUT_PROGRAM);
                auto results = m_dbManager->FilterStudentsByProgram(program);
                PrintStudentList(results, FILTER_RESULTS + " - Студенти");
                PressAnyKey();
                break;
            }
            case 3: {
                int order = GetIntInput(INPUT_SORT_ORDER);
                m_dbManager->SortStudentsByName(order == 1);
                cout << SORTED_SUCCESS << endl;
                PressAnyKey();
                break;
            }
            case 4: {
                string name = GetInput(INPUT_SEARCH_NAME);
                auto results = m_dbManager->SearchTeachersByName(name);
                PrintTeacherList(results, SEARCH_RESULTS + " - Викладачі");
                PressAnyKey();
                break;
            }
            case 5: {
                string department = GetInput(INPUT_DEPARTMENT);
                auto results = m_dbManager->FilterTeachersByDepartment(department);
                PrintTeacherList(results, FILTER_RESULTS + " - Викладачі");
                PressAnyKey();
                break;
            }
            case 6: {
                int order = GetIntInput(INPUT_SORT_ORDER);
                m_dbManager->SortTeachersByName(order == 1);
                cout << SORTED_SUCCESS << endl;
                PressAnyKey();
                break;
            }
            case 7: {
                string name = GetInput(INPUT_SEARCH_NAME);
                auto results = m_dbManager->SearchSubjectsByName(name);
                PrintSubjectList(results, SEARCH_RESULTS + " - Предмети");
                PressAnyKey();
                break;
            }
            case 8: {
                int semester = GetIntInput(INPUT_SEMESTER);
                auto results = m_dbManager->FilterSubjectsBySemester(semester);
                PrintSubjectList(results, FILTER_RESULTS + " - Предмети");
                PressAnyKey();
                break;
            }
            case 9: {
                int order = GetIntInput(INPUT_SORT_ORDER);
                m_dbManager->SortSubjectsByName(order == 1);
                cout << SORTED_SUCCESS << endl;
                PressAnyKey();
                break;
            }
            case 0:
                return;
            default:
                cout << INVALID_CHOICE_MSG << endl;
                PressAnyKey();
        }
    } while (choice != 0);
}

void MenuManager::ShowHelp() {
    ClearScreen();
    cout << "=== ДОПОМОГА ===\n"
         << "Це консольна система університету.\n"
         << "Оберіть пункт меню, щоб виконати дію.\n\n"
         << "Доступні операції:\n"
         << "- Додавання нових об'єктів\n"
         << "- Редагування існуючих\n"
         << "- Видалення об'єктів\n"
         << "- Перегляд списків\n"
         << "- Пошук за критеріями\n"
         << "- Сортування даних\n"
         << "- Фільтрація записів\n\n"
         << "Права доступу:\n"
         << "- Адміністратор: повний доступ\n"
         << "- Викладач: перегляд та пошук\n"
         << "- Студент: перегляд та пошук\n";
    PressAnyKey();
}