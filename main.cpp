#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

#include "Admin.h"
#include "DatabaseManager.h"
#include "Student.h"
#include "Teacher.h"
#include "Subject.h"

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

/**
 * @brief Простір імен University для компонентів управління університетом
 */
namespace University {

// Константи
constexpr int MAX_SUBJECTS_PER_STUDENT = 10;
constexpr int MAX_SEMESTER = 8;
constexpr int MIN_SEMESTER = 1;

// Статичні змінні
static bool ukrainianSupportInitialized = false;

//-----------------------------------------------------------------------------
// Допоміжні функції
//-----------------------------------------------------------------------------

void initializeUkrainianSupport();
void clearInputBuffer();
void displayHelp();

//-----------------------------------------------------------------------------
// Оголошення функцій для призначення студентів на предмети
//-----------------------------------------------------------------------------

void ShowStudentAssignmentMenu(DatabaseManager& db);
void AssignStudentToSubjectUI(DatabaseManager& db);
void RemoveStudentFromSubjectUI(DatabaseManager& db);
void ShowStudentSubjectsUI(DatabaseManager& db);
void ShowSubjectStudentsUI(DatabaseManager& db);

//-----------------------------------------------------------------------------
// Оголошення функцій для керування викладачами та предметами
//-----------------------------------------------------------------------------

void manageTeachers(Admin& admin, DatabaseManager& db, bool isAdmin);
void manageSubjects(Admin& admin, DatabaseManager& db, bool isAdmin);

//-----------------------------------------------------------------------------
// Оголошення функцій для керування користувачами
//-----------------------------------------------------------------------------

void manageUsers(Admin& admin);
void changeOwnPasswordMenu(Admin& admin, const string& currentUsername);

//-----------------------------------------------------------------------------
// Реалізації функцій
//-----------------------------------------------------------------------------

/**
 * @brief Ініціалізує підтримку української мови
 */
void initializeUkrainianSupport()
{
    if (ukrainianSupportInitialized)
    {
        return;
    }

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try
    {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }
    catch (...)
    {
        try
        {
            setlocale(LC_ALL, "C.UTF-8");
        }
        catch (...)
        {
            setlocale(LC_ALL, "");
        }
    }

    ukrainianSupportInitialized = true;
}

/**
 * @brief Очищує вхідний буфер
 */
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Виводить довідкову інформацію
 */
void displayHelp()
{
    cout << "\n=== ДОПОМОГА ===" << endl;
    cout << "1. Адміністратор може керувати студентами, викладачами, "
         << "предметами та користувачами." << endl;
    cout << "2. Студент може тільки переглядати предмети." << endl;
    cout << "3. Для виходу з програми виберіть відповідний пункт меню." << endl;
    cout << "==================" << endl;
}

//-----------------------------------------------------------------------------
// Функції для керування користувачами
//-----------------------------------------------------------------------------

/**
 * @brief Меню керування користувачами
 * @param admin Об'єкт адміністратора
 */
void manageUsers(Admin& admin)
{
    int choice;
    do
    {
        cout << "\n=== КЕРУВАННЯ КОРИСТУВАЧАМИ ===" << endl;
        cout << "1. Створити нового користувача" << endl;
        cout << "2. Переглянути список користувачів" << endl;
        cout << "3. Видалити користувача" << endl;
        cout << "4. Змінити пароль користувача" << endl;
        cout << "5. Змінити роль користувача" << endl;
        cout << "6. Переглянути інформацію про користувача" << endl;
        cout << "0. Повернутися до попереднього меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        try
        {
            switch (choice)
            {
                case 1:
                {
                    string username, password;
                    int roleChoice;

                    cout << "\n=== СТВОРЕННЯ НОВОГО КОРИСТУВАЧА ===" << endl;
                    cout << "Ім'я користувача: ";
                    getline(cin, username);
                    cout << "Пароль: ";
                    getline(cin, password);
                    cout << "Роль (1 - Студент, 2 - Адміністратор): ";
                    cin >> roleChoice;
                    clearInputBuffer();

                    UserRole role = (roleChoice == 2) ? UserRole::ADMIN : UserRole::STUDENT;

                    if (admin.AddUser(username, password, role))
                    {
                        cout << " Користувача '" << username << "' успішно створено!" << endl;
                    }
                    break;
                }
                case 2:
                {
                    cout << "\n=== СПИСОК КОРИСТУВАЧІВ ===" << endl;
                    admin.ListUsers();
                    break;
                }
                case 3:
                {
                    string username;
                    cout << "\n=== ВИДАЛЕННЯ КОРИСТУВАЧА ===" << endl;
                    cout << "Ім'я користувача для видалення: ";
                    getline(cin, username);

                    if (admin.RemoveUser(username))
                    {
                        cout << " Користувача '" << username << "' успішно видалено!" << endl;
                    }
                    break;
                }
                case 4:
                {
                    string username, newPassword;
                    cout << "\n=== ЗМІНА ПАРОЛЯ ===" << endl;
                    cout << "Ім'я користувача: ";
                    getline(cin, username);
                    cout << "Новий пароль: ";
                    getline(cin, newPassword);

                    if (admin.ChangePassword(username, newPassword))
                    {
                        cout << " Пароль для користувача '" << username << "' успішно змінено!" << endl;
                    }
                    break;
                }
                case 5:
                {
                    string username;
                    int newRoleChoice;
                    cout << "\n=== ЗМІНА РОЛІ КОРИСТУВАЧА ===" << endl;
                    cout << "Ім'я користувача: ";
                    getline(cin, username);
                    cout << "Нова роль (1 - Студент, 2 - Адміністратор): ";
                    cin >> newRoleChoice;
                    clearInputBuffer();

                    UserRole newRole = (newRoleChoice == 2) ? UserRole::ADMIN : UserRole::STUDENT;

                    if (admin.ChangeUserRole(username, newRole))
                    {
                        cout << " Роль користувача '" << username << "' успішно змінено на "
                             << (newRole == UserRole::ADMIN ? "Адміністратор" : "Студент") << "!" << endl;
                    }
                    break;
                }
                case 6:
                {
                    string username;
                    cout << "\n=== ІНФОРМАЦІЯ ПРО КОРИСТУВАЧА ===" << endl;
                    cout << "Ім'я користувача: ";
                    getline(cin, username);
                    admin.DisplayUserInfo(username);
                    break;
                }
                case 0:
                    cout << "Повернення до попереднього меню..." << endl;
                    break;
                default:
                    cout << " Невірний вибір!" << endl;
            }
        }
        catch (const exception& e)
        {
            cout << " ПОМИЛКА: " << e.what() << endl;
        }
    }
    while (choice != 0);
}

/**
 * @brief Меню для зміни власного пароля
 * @param admin Об'єкт адміністратора
 * @param currentUsername Поточний користувач
 */
void changeOwnPasswordMenu(Admin& admin, const string& currentUsername)
{
    string newPassword;
    cout << "\n=== ЗМІНА ВЛАСНОГО ПАРОЛЯ ===" << endl;
    cout << "Поточний користувач: " << currentUsername << endl;
    cout << "Новий пароль: ";
    getline(cin, newPassword);

    try
    {
        admin.ChangeOwnPassword(newPassword);
        cout << " Ваш пароль успішно змінено!" << endl;
    }
    catch (const exception& e)
    {
        cout << " ПОМИЛКА: " << e.what() << endl;
    }
}

//-----------------------------------------------------------------------------
// Функції для керування викладачами
//-----------------------------------------------------------------------------

/**
 * @brief Меню керування викладачами
 * @param admin Об'єкт адміністратора
 * @param db Менеджер бази даних
 * @param isAdmin Права адміністратора
 */
void manageTeachers(Admin& admin, DatabaseManager& db, bool isAdmin)
{
    int choice;
    do
    {
        cout << "\n=== КЕРУВАННЯ ВИКЛАДАЧАМИ ===" << endl;
        cout << "1. Переглянути всіх викладачів" << endl;
        cout << "2. Додати викладача" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "3. Редагувати викладача" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "4. Видалити викладача" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "5. Пошук викладача за ID" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        // Перевірка прав для адмін-функцій
        if (!isAdmin && (choice == 2 || choice == 3 || choice == 4))
        {
            cout << " ДОСТУП ЗАБОРОНЕНО! "
                 << "Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                vector<Teacher> teachers = db.GetAllTeachers();
                cout << "\n=== СПИСОК ВИКЛАДАЧІВ (" << teachers.size() << ") ===" << endl;
                for (const auto& teacher : teachers)
                {
                    teacher.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2:
            {
                cout << "\n=== ДОДАВАННЯ ВИКЛАДАЧА ===" << endl;
                string name, lastName, email, teacherID, department;
                int degreeChoice;

                cout << "Ім'я: ";
                getline(cin, name);
                cout << "Прізвище: ";
                getline(cin, lastName);
                cout << "Email: ";
                getline(cin, email);
                cout << "ID викладача (формат PR001): ";
                getline(cin, teacherID);
                cout << "Кафедра: ";
                getline(cin, department);

                cout << "Науковий ступінь (1 - Бакалавр, 2 - Магістр, 3 - Доктор): ";
                cin >> degreeChoice;
                clearInputBuffer();

                AcademicDegree degree;
                switch (degreeChoice) {
                    case 1: degree = AcademicDegree::BACHELOR; break;
                    case 2: degree = AcademicDegree::MASTER; break;
                    case 3: degree = AcademicDegree::DOCTOR; break;
                    default: degree = AcademicDegree::BACHELOR; break;
                }

                try
                {
                    Teacher teacher(name, lastName, email, teacherID, department, degree);
                    db.AddTeacher(teacher);
                    cout << " Викладача успішно додано!" << endl;
                }
                catch (const exception& e)
                {
                    cout << " ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3:
            {
                cout << "\n=== РЕДАГУВАННЯ ВИКЛАДАЧА ===" << endl;
                string teacherID;
                cout << "Введіть ID викладача для редагування: ";
                getline(cin, teacherID);

                Teacher* teacher = db.GetTeacher(teacherID);
                if (teacher)
                {
                    string name, lastName, email, department;
                    int degreeChoice;

                    cout << "Нове ім'я: ";
                    getline(cin, name);
                    cout << "Нове прізвище: ";
                    getline(cin, lastName);
                    cout << "Новий email: ";
                    getline(cin, email);
                    cout << "Нова кафедра: ";
                    getline(cin, department);

                    cout << "Новий науковий ступінь (1 - Бакалавр, 2 - Магістр, 3 - Доктор): ";
                    cin >> degreeChoice;
                    clearInputBuffer();

                    AcademicDegree degree;
                    switch (degreeChoice) {
                        case 1: degree = AcademicDegree::BACHELOR; break;
                        case 2: degree = AcademicDegree::MASTER; break;
                        case 3: degree = AcademicDegree::DOCTOR; break;
                        default: degree = AcademicDegree::BACHELOR; break;
                    }

                    try
                    {
                        Teacher newData(name, lastName, email, teacherID, department, degree);
                        if (db.EditTeacher(teacherID, newData))
                        {
                            cout << " Викладача успішно оновлено!" << endl;
                        }
                    }
                    catch (const exception& e)
                    {
                        cout << " ПОМИЛКА: " << e.what() << endl;
                    }
                }
                else
                {
                    cout << " Викладача не знайдено!" << endl;
                }
                break;
            }
            case 4:
            {
                cout << "\n=== ВИДАЛЕННЯ ВИКЛАДАЧА ===" << endl;
                string teacherID;
                cout << "Введіть ID викладача для видалення: ";
                getline(cin, teacherID);

                try
                {
                    if (db.DeleteTeacher(teacherID))
                    {
                        cout << " Викладача успішно видалено!" << endl;
                    }
                    else
                    {
                        cout << " Викладача не знайдено!" << endl;
                    }
                }
                catch (const exception& e)
                {
                    cout << " ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 5:
            {
                string teacherID;
                cout << "Введіть ID викладача: ";
                getline(cin, teacherID);
                Teacher* teacher = db.GetTeacher(teacherID);
                if (teacher)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    teacher->print();
                }
                else
                {
                    cout << " Викладача не знайдено!" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    }
    while (choice != 0);
}

//-----------------------------------------------------------------------------
// Функції для керування предметами
//-----------------------------------------------------------------------------

/**
 * @brief Меню керування предметами
 * @param admin Об'єкт адміністратора
 * @param db Менеджер бази даних
 * @param isAdmin Права адміністратора
 */
void manageSubjects(Admin& admin, DatabaseManager& db, bool isAdmin)
{
    int choice;
    do
    {
        cout << "\n=== КЕРУВАННЯ ПРЕДМЕТАМИ ===" << endl;
        cout << "1. Переглянути всі предмети" << endl;
        cout << "2. Додати предмет" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "3. Редагувати предмет" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "4. Видалити предмет" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "5. Пошук предмета за ID" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        // Перевірка прав для адмін-функцій
        if (!isAdmin && (choice == 2 || choice == 3 || choice == 4))
        {
            cout << " ДОСТУП ЗАБОРОНЕНО! "
                 << "Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                vector<Subject> subjects = db.GetAllSubjects();
                cout << "\n=== СПИСОК ПРЕДМЕТІВ (" << subjects.size() << ") ===" << endl;
                for (const auto& subject : subjects)
                {
                    subject.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2:
            {
                cout << "\n=== ДОДАВАННЯ ПРЕДМЕТА ===" << endl;
                string subjectId, subjectName, teacherId;
                int credits, semester;

                cout << "ID предмету (формат SJ001): ";
                getline(cin, subjectId);
                cout << "Назва предмету: ";
                getline(cin, subjectName);
                cout << "Кількість кредитів: ";
                cin >> credits;
                cout << "ID викладача: ";
                clearInputBuffer();
                getline(cin, teacherId);
                cout << "Семестр: ";
                cin >> semester;
                clearInputBuffer();

                try
                {
                    Subject subject(subjectId, subjectName, credits, teacherId, semester);
                    db.AddSubject(subject);
                    cout << " Предмет успішно додано!" << endl;
                }
                catch (const exception& e)
                {
                    cout << " ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3:
            {
                cout << "\n=== РЕДАГУВАННЯ ПРЕДМЕТА ===" << endl;
                string subjectId;
                cout << "Введіть ID предмета для редагування: ";
                getline(cin, subjectId);

                Subject* subject = db.GetSubject(subjectId);
                if (subject)
                {
                    string subjectName, teacherId;
                    int credits, semester;

                    cout << "Нова назва предмету: ";
                    getline(cin, subjectName);
                    cout << "Нова кількість кредитів: ";
                    cin >> credits;
                    cout << "Новий ID викладача: ";
                    clearInputBuffer();
                    getline(cin, teacherId);
                    cout << "Новий семестр: ";
                    cin >> semester;
                    clearInputBuffer();

                    try
                    {
                        Subject newData(subjectId, subjectName, credits, teacherId, semester);
                        if (db.EditSubject(subjectId, newData))
                        {
                            cout << " Предмет успішно оновлено!" << endl;
                        }
                    }
                    catch (const exception& e)
                    {
                        cout << " ПОМИЛКА: " << e.what() << endl;
                    }
                }
                else
                {
                    cout << " Предмет не знайдено!" << endl;
                }
                break;
            }
            case 4:
            {
                cout << "\n=== ВИДАЛЕННЯ ПРЕДМЕТА ===" << endl;
                string subjectId;
                cout << "Введіть ID предмета для видалення: ";
                getline(cin, subjectId);

                try
                {
                    if (db.DeleteSubject(subjectId))
                    {
                        cout << " Предмет успішно видалено!" << endl;
                    }
                    else
                    {
                        cout << " Предмет не знайдено!" << endl;
                    }
                }
                catch (const exception& e)
                {
                    cout << " ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 5:
            {
                string subjectId;
                cout << "Введіть ID предмета: ";
                getline(cin, subjectId);
                Subject* subject = db.GetSubject(subjectId);
                if (subject)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    subject->print();
                }
                else
                {
                    cout << " Предмет не знайдено!" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    }
    while (choice != 0);
}

//-----------------------------------------------------------------------------
// Функції для призначення студентів на предмети
//-----------------------------------------------------------------------------

/**
 * @brief Меню призначення студентів на предмети
 * @param db Менеджер бази даних
 */
void ShowStudentAssignmentMenu(DatabaseManager& db)
{
    int choice;
    do {
        cout << "\n=== ПРИЗНАЧЕННЯ СТУДЕНТІВ НА ПРЕДМЕТИ ===" << endl;
        cout << "1. Додати студента до предмету" << endl;
        cout << "2. Видалити студента з предмету" << endl;
        cout << "3. Переглянути предмети студента" << endl;
        cout << "4. Переглянути студентів предмету" << endl;
        cout << "0. Повернутися до адміністративного меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                AssignStudentToSubjectUI(db);
                break;
            case 2:
                RemoveStudentFromSubjectUI(db);
                break;
            case 3:
                ShowStudentSubjectsUI(db);
                break;
            case 4:
                ShowSubjectStudentsUI(db);
                break;
            case 0:
                cout << "Повертаємося до адміністративного меню..." << endl;
                break;
            default:
                cout << " Неправильний вибір!" << endl;
        }
    } while (choice != 0);
}

/**
 * @brief UI для додавання студента до предмету
 * @param db Менеджер бази даних
 */
void AssignStudentToSubjectUI(DatabaseManager& db)
{
    try {
        string studentId, subjectId;

        cout << "\n--- Додати студента до предмету ---" << endl;
        cout << "Введіть ID студента: ";
        getline(cin, studentId);
        cout << "Введіть ID предмету: ";
        getline(cin, subjectId);

        if (db.AssignStudentToSubject(studentId, subjectId)) {
            cout << " Студента успішно додано до предмету!" << endl;
        }
    }
    catch (const exception& e) {
        cout << " Помилка: " << e.what() << endl;
    }
}

/**
 * @brief UI для видалення студента з предмету
 * @param db Менеджер бази даних
 */
void RemoveStudentFromSubjectUI(DatabaseManager& db)
{
    try {
        string studentId, subjectId;

        cout << "\n--- Видалити студента з предмету ---" << endl;
        cout << "Введіть ID студента: ";
        getline(cin, studentId);
        cout << "Введіть ID предмету: ";
        getline(cin, subjectId);

        if (db.RemoveStudentFromSubject(studentId, subjectId)) {
            cout << " Студента успішно видалено з предмету!" << endl;
        }
    }
    catch (const exception& e) {
        cout << " Помилка: " << e.what() << endl;
    }
}

/**
 * @brief UI для перегляду предметів студента
 * @param db Менеджер бази даних
 */
void ShowStudentSubjectsUI(DatabaseManager& db)
{
    try {
        string studentId;

        cout << "\n--- Предмети студента ---" << endl;
        cout << "Введіть ID студента: ";
        getline(cin, studentId);

        auto subjects = db.GetStudentSubjects(studentId);

        if (subjects.empty()) {
            cout << "Студент не записаний на жоден предмет." << endl;
        } else {
            cout << "Предмети студента:" << endl;
            for (const auto& subject : subjects) {
                cout << " - " << subject.getSubjectName()
                     << " (ID: " << subject.getSubjectId()
                     << ", Кредити: " << subject.getEctsCredits() << ")" << endl;
            }
        }
    }
    catch (const exception& e) {
        cout << " Помилка: " << e.what() << endl;
    }
}

/**
 * @brief UI для перегляду студентів предмету
 * @param db Менеджер бази даних
 */
void ShowSubjectStudentsUI(DatabaseManager& db)
{
    try {
        string subjectId;

        cout << "\n--- Студенти предмету ---" << endl;
        cout << "Введіть ID предмету: ";
        getline(cin, subjectId);

        auto students = db.GetSubjectStudents(subjectId);

        if (students.empty()) {
            cout << "На предмет не записано жодного студента." << endl;
        } else {
            cout << "Студенти предмету:" << endl;
            for (const auto& student : students) {
                cout << " - " << student.getFullName()
                     << " (ID: " << student.getStudentID() << ")" << endl;
            }
        }
    }
    catch (const exception& e) {
        cout << " Помилка: " << e.what() << endl;
    }
}

//-----------------------------------------------------------------------------
// Функції меню для студентів
//-----------------------------------------------------------------------------

/**
 * @brief Меню для студентів (тільки перегляд предметів)
 * @param db Менеджер бази даних
 */
void studentMenu(DatabaseManager& db)
{
    int choice;
    do
    {
        cout << "\n=== МЕНЮ СТУДЕНТА ===" << endl;
        cout << "1. Переглянути всі предмети" << endl;
        cout << "2. Пошук предмета за ID" << endl;
        cout << "3. Фільтрувати предмети за семестром" << endl;
        cout << "0. Вийти" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
            case 1:
            {
                vector<Subject> subjects = db.GetAllSubjects();
                cout << "\n=== СПИСОК УСІХ ПРЕДМЕТІВ (" << subjects.size() << ") ===" << endl;
                for (const auto& subject : subjects)
                {
                    subject.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2:
            {
                string subjectId;
                cout << "Введіть ID предмета: ";
                getline(cin, subjectId);
                Subject* subject = db.GetSubject(subjectId);
                if (subject)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    subject->print();
                }
                else
                {
                    cout << " Предмет не знайдено!" << endl;
                }
                break;
            }
            case 3:
            {
                int semester;
                cout << "Введіть номер семестру: ";
                cin >> semester;
                clearInputBuffer();
                vector<Subject> subjects = db.GetAllSubjects();
                vector<Subject> filtered;

                for (const auto& subject : subjects)
                {
                    if (subject.getSemester() == semester)
                    {
                        filtered.push_back(subject);
                    }
                }

                cout << "\n=== ПРЕДМЕТИ ЗА СЕМЕСТРОМ " << semester
                     << " (" << filtered.size() << ") ===" << endl;
                for (const auto& subject : filtered)
                {
                    subject.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    }
    while (choice != 0);
}

//-----------------------------------------------------------------------------
// Функції меню для адміністраторів
//-----------------------------------------------------------------------------

/**
 * @brief Меню пошуку та фільтрації
 * @param admin Об'єкт адміністратора
 * @param db Менеджер бази даних
 * @param isAdmin Права адміністратора
 */
void searchAndFilter(Admin& admin, DatabaseManager& db, bool isAdmin)
{
    int choice;
    do
    {
        cout << "\n=== ПОШУК ТА ФІЛЬТРАЦІЯ ===" << endl;
        cout << "1. Пошук студента за ID" << endl;
        cout << "2. Пошук викладача за ID" << endl;
        cout << "3. Пошук предмета за ID" << endl;
        cout << "4. Фільтрувати студентів за освітньою програмою" << endl;
        cout << "5. Фільтрувати предмети за семестром" << endl;
        cout << "6. Сортувати студентів за прізвищем" << endl;
        cout << "7. Сортувати викладачів за кафедрою" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
            case 1:
            {
                string studentID;
                cout << "Введіть ID студента: ";
                getline(cin, studentID);
                Student* student = db.GetStudent(studentID);
                if (student)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    student->print();
                }
                else
                {
                    cout << " Студента не знайдено!" << endl;
                }
                break;
            }
            case 2:
            {
                string teacherID;
                cout << "Введіть ID викладача: ";
                getline(cin, teacherID);
                Teacher* teacher = db.GetTeacher(teacherID);
                if (teacher)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    teacher->print();
                }
                else
                {
                    cout << " Викладача не знайдено!" << endl;
                }
                break;
            }
            case 3:
            {
                string subjectId;
                cout << "Введіть ID предмета: ";
                getline(cin, subjectId);
                Subject* subject = db.GetSubject(subjectId);
                if (subject)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    subject->print();
                }
                else
                {
                    cout << " Предмет не знайдено!" << endl;
                }
                break;
            }
            case 4:
            {
                string program;
                cout << "Введіть назву освітньої програми: ";
                getline(cin, program);
                vector<Student> students = db.GetAllStudents();
                vector<Student> filtered;

                for (const auto& student : students)
                {
                    if (student.getEducationalProgram().find(program) != string::npos)
                    {
                        filtered.push_back(student);
                    }
                }

                cout << "\n=== СТУДЕНТИ ЗА ПРОГРАМОЮ '" << program
                     << "' (" << filtered.size() << ") ===" << endl;
                for (const auto& student : filtered)
                {
                    student.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 5:
            {
                int semester;
                cout << "Введіть номер семестру: ";
                cin >> semester;
                clearInputBuffer();
                vector<Subject> subjects = db.GetAllSubjects();
                vector<Subject> filtered;

                for (const auto& subject : subjects)
                {
                    if (subject.getSemester() == semester)
                    {
                        filtered.push_back(subject);
                    }
                }

                cout << "\n=== ПРЕДМЕТИ ЗА СЕМЕСТРОМ " << semester
                     << " (" << filtered.size() << ") ===" << endl;
                for (const auto& subject : filtered)
                {
                    subject.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 6:
            {
                vector<Student> students = db.GetAllStudents();
                sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                {
                    return a.getLastName() < b.getLastName();
                });

                cout << "\n=== СТУДЕНТИ (ВІДСОРТОВАНІ ЗА ПРІЗВИЩЕМ) ===" << endl;
                for (const auto& student : students)
                {
                    student.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 7:
            {
                vector<Teacher> teachers = db.GetAllTeachers();
                sort(teachers.begin(), teachers.end(), [](const Teacher& a, const Teacher& b)
                {
                    return a.getDepartment() < b.getDepartment();
                });

                cout << "\n=== ВИКЛАДАЧІ (ВІДСОРТОВАНІ ЗА КАФЕДРОЮ) ===" << endl;
                for (const auto& teacher : teachers)
                {
                    teacher.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    }
    while (choice != 0);
}

/**
 * @brief Меню керування студентами
 * @param admin Об'єкт адміністратора
 * @param db Менеджер бази даних
 * @param isAdmin Права адміністратора
 */
void manageStudents(Admin& admin, DatabaseManager& db, bool isAdmin)
{
    int choice;
    do
    {
        cout << "\n=== КЕРУВАННЯ СТУДЕНТАМИ ===" << endl;
        cout << "1. Переглянути всіх студентів" << endl;
        cout << "2. Додати студента" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "3. Редагувати студента" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "4. Видалити студента" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "5. Пошук студента за ID" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        // Перевірка прав для адмін-функцій
        if (!isAdmin && (choice == 2 || choice == 3 || choice == 4))
        {
            cout << " ДОСТУП ЗАБОРОНЕНО! "
                 << "Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                vector<Student> students = db.GetAllStudents();
                cout << "\n=== СПИСОК СТУДЕНТІВ (" << students.size() << ") ===" << endl;
                for (const auto& student : students)
                {
                    student.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2:
            {
                cout << "\n=== ДОДАВАННЯ СТУДЕНТА ===" << endl;
                string name, lastName, email, studentID, educationalProgram;
                cout << "Ім'я: ";
                getline(cin, name);
                cout << "Прізвище: ";
                getline(cin, lastName);
                cout << "Email: ";
                getline(cin, email);
                cout << "ID студента (формат ST001): ";
                getline(cin, studentID);
                cout << "Освітня програма: ";
                getline(cin, educationalProgram);

                try
                {
                    Student student(name, lastName, email, studentID, educationalProgram);
                    db.AddStudent(student);
                    cout << " Студента успішно додано!" << endl;
                }
                catch (const exception& e)
                {
                    cout << " ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3:
            {
                cout << "\n=== РЕДАГУВАННЯ СТУДЕНТА ===" << endl;
                string studentID;
                cout << "Введіть ID студента для редагування: ";
                getline(cin, studentID);

                Student* student = db.GetStudent(studentID);
                if (student)
                {
                    string name, lastName, email, educationalProgram;
                    cout << "Нове ім'я: ";
                    getline(cin, name);
                    cout << "Нове прізвище: ";
                    getline(cin, lastName);
                    cout << "Новий email: ";
                    getline(cin, email);
                    cout << "Нова освітня програма: ";
                    getline(cin, educationalProgram);

                    try
                    {
                        Student newData(name, lastName, email, studentID, educationalProgram);
                        if (db.EditStudent(studentID, newData))
                        {
                            cout << " Студента успішно оновлено!" << endl;
                        }
                    }
                    catch (const exception& e)
                    {
                        cout << " ПОМИЛКА: " << e.what() << endl;
                    }
                }
                else
                {
                    cout << " Студента не знайдено!" << endl;
                }
                break;
            }
            case 4:
            {
                cout << "\n=== ВИДАЛЕННЯ СТУДЕНТА ===" << endl;
                string studentID;
                cout << "Введіть ID студента для видалення: ";
                getline(cin, studentID);

                try
                {
                    if (db.DeleteStudent(studentID))
                    {
                        cout << " Студента успішно видалено!" << endl;
                    }
                    else
                    {
                        cout << " Студента не знайдено!" << endl;
                    }
                }
                catch (const exception& e)
                {
                    cout << " ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 5:
            {
                string studentID;
                cout << "Введіть ID студента: ";
                getline(cin, studentID);
                Student* student = db.GetStudent(studentID);
                if (student)
                {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    student->print();
                }
                else
                {
                    cout << " Студента не знайдено!" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    }
    while (choice != 0);
}

/**
 * @brief Головне меню програми для адміністратора
 * @param admin Об'єкт адміністратора
 * @param db Менеджер бази даних
 * @param currentUsername Поточний користувач
 */
void adminMenu(Admin& admin, DatabaseManager& db, const string& currentUsername)
{
    int choice;
    do
    {
        cout << "\n=== АДМІНІСТРАТИВНЕ МЕНЮ ===" << endl;
        cout << "Поточний користувач: " << currentUsername << endl;
        cout << "1. Керування студентами" << endl;
        cout << "2. Керування викладачами" << endl;
        cout << "3. Керування предметами" << endl;
        cout << "4. Призначення студентів на предмети" << endl;
        cout << "5. Керування користувачами" << endl;
        cout << "6. Пошук та фільтрація" << endl;
        cout << "7. Змінити свій пароль" << endl;
        cout << "8. Допомога" << endl;
        cout << "0. Вийти" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                manageStudents(admin, db, true);
                break;
            case 2:
                manageTeachers(admin, db, true);
                break;
            case 3:
                manageSubjects(admin, db, true);
                break;
            case 4:
                ShowStudentAssignmentMenu(db);
                break;
            case 5:
                manageUsers(admin);
                break;
            case 6:
                searchAndFilter(admin, db, true);
                break;
            case 7:
                changeOwnPasswordMenu(admin, currentUsername);
                break;
            case 8:
                displayHelp();
                break;
            case 0:
                cout << "Вихід з адміністративного меню..." << endl;
                break;
            default:
                cout << " Невірний вибір!" << endl;
        }
    }
    while (choice != 0);
}

/**
 * @brief Точка входу в програму
 * @return Код завершення програми
 */
int main()
{
    initializeUkrainianSupport();

    Admin admin;
    DatabaseManager db;

    cout << "=== СИСТЕМА УПРАВЛІННЯ НАВЧАЛЬНИМ ЗАКЛАДОМ ===" << endl;
    cout << "Версія з підтримкою української мови" << endl;

    // Завантаження даних при запуску
    try
    {
        admin.LoadUsersFromFile("users.txt");
        db.LoadFromFile("students.csv", "teachers.csv", "subjects.csv");
        cout << "Дані успішно завантажено!" << endl;
    }
    catch (const exception& e)
    {
        cout << "Помилка завантаження даних: " << e.what() << endl;
    }

    int mainChoice;
    do
    {
        cout << "\n=== ВХІД ДО СИСТЕМИ ===" << endl;
        cout << "1. Увійти як адміністратор" << endl;
        cout << "2. Увійти як студент" << endl;
        cout << "3. Вийти" << endl;
        cout << "Оберіть опцію: ";
        cin >> mainChoice;
        clearInputBuffer();

        switch (mainChoice)
        {
            case 1:
            {
                string username, password;
                cout << "Логін: ";
                getline(cin, username);
                cout << "Пароль: ";
                getline(cin, password);

                if (admin.Authenticate(username, password))
                {
                    // Перевіряємо, чи є користувач адміністратором
                    if (admin.IsAdminUser(username))
                    {
                        cout << " Успішний вхід як адміністратор!" << endl;
                        adminMenu(admin, db, username);
                    }
                    else
                    {
                        cout << " Цей користувач не має прав адміністратора!" << endl;
                    }
                }
                else
                {
                    cout << " Помилка автентифікації! "
                         << "Невірний логін або пароль." << endl;
                }
                break;
            }
            case 2:
            {
                string username, password;
                cout << "Логін: ";
                getline(cin, username);
                cout << "Пароль: ";
                getline(cin, password);

                if (admin.Authenticate(username, password))
                {
                    cout << "✅ Успішний вхід як студент!" << endl;
                    studentMenu(db);
                }
                else
                {
                    cout << "❌ Помилка автентифікації! "
                         << "Невірний логін або пароль." << endl;
                }
                break;
            }
            case 3:
                cout << "Завершення роботи..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    }
    while (mainChoice != 3);

    // Збереження даних при виході
    try
    {
        admin.SaveUsersToFile("users.txt");
        db.SaveToFile("students.csv", "teachers.csv", "subjects.csv");
        cout << "Дані успішно збережено!" << endl;
    }
    catch (const exception& e)
    {
        cout << "Помилка збереження даних: " << e.what() << endl;
    }

    cout << "Дякуємо за використання нашої системи!" << endl;
    return 0;
}

} // namespace University

// Головна функція
int main()
{
    return University::main();
}