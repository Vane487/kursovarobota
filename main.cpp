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

// UKRAINIAN SUPPORT
#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

// UKRAINIAN SUPPORT FUNCTION
void setupUkrainianSupport() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    } catch (...) {
        try {
            setlocale(LC_ALL, "C.UTF-8");
        } catch (...) {
            setlocale(LC_ALL, "");
        }
    }
}

// Прототипи функцій
void displayHelp();
void clearInputBuffer();
void mainMenu(Admin& admin, DatabaseManager& db, bool isAdmin);
void manageStudents(Admin& admin, DatabaseManager& db, bool isAdmin);
void manageTeachers(Admin& admin, DatabaseManager& db, bool isAdmin);
void manageSubjects(Admin& admin, DatabaseManager& db, bool isAdmin);
void manageUsers(Admin& admin, DatabaseManager& db, bool isAdmin);
void searchAndFilter(Admin& admin, DatabaseManager& db, bool isAdmin);

void displayHelp() {
    cout << "\n=== ДОПОМОГА ===" << endl;
    cout << "1. Адміністратор може керувати студентами, викладачами, предметами та користувачами." << endl;
    cout << "2. Студент може тільки переглядати інформацію." << endl;
    cout << "3. Для виходу з програми виберіть відповідний пункт меню." << endl;
    cout << "==================" << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void searchAndFilter(Admin& admin, DatabaseManager& db, bool isAdmin) {
    int choice;
    do {
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

        switch (choice) {
            case 1: {
                string studentID;
                cout << "Введіть ID студента: ";
                getline(cin, studentID);
                Student* student = db.getStudent(studentID);
                if (student) {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    student->print();
                } else {
                    cout << "❌ Студента не знайдено!" << endl;
                }
                break;
            }
            case 2: {
                string teacherID;
                cout << "Введіть ID викладача: ";
                getline(cin, teacherID);
                Teacher* teacher = db.getTeacher(teacherID);
                if (teacher) {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    teacher->print();
                } else {
                    cout << "❌ Викладача не знайдено!" << endl;
                }
                break;
            }
            case 3: {
                string subjectId;
                cout << "Введіть ID предмета: ";
                getline(cin, subjectId);
                Subject* subject = db.getSubject(subjectId);
                if (subject) {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    subject->print();
                } else {
                    cout << "❌ Предмет не знайдено!" << endl;
                }
                break;
            }
            case 4: {
                string program;
                cout << "Введіть назву освітньої програми: ";
                getline(cin, program);
                vector<Student> students = db.getAllStudents();
                vector<Student> filtered;

                for (const auto& student : students) {
                    if (student.getEducationalProgram().find(program) != string::npos) {
                        filtered.push_back(student);
                    }
                }

                cout << "\n=== СТУДЕНТИ ЗА ПРОГРАМОЮ '" << program << "' (" << filtered.size() << ") ===" << endl;
                for (const auto& student : filtered) {
                    student.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 5: {
                int semester;
                cout << "Введіть номер семестру: ";
                cin >> semester;
                clearInputBuffer();
                vector<Subject> subjects = db.getAllSubjects();
                vector<Subject> filtered;

                for (const auto& subject : subjects) {
                    if (subject.getSemester() == semester) {
                        filtered.push_back(subject);
                    }
                }

                cout << "\n=== ПРЕДМЕТИ ЗА СЕМЕСТРОМ " << semester << " (" << filtered.size() << ") ===" << endl;
                for (const auto& subject : filtered) {
                    subject.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 6: {
                vector<Student> students = db.getAllStudents();
                sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                    return a.getLastName() < b.getLastName();
                });

                cout << "\n=== СТУДЕНТИ (ВІДСОРТОВАНІ ЗА ПРІЗВИЩЕМ) ===" << endl;
                for (const auto& student : students) {
                    student.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 7: {
                vector<Teacher> teachers = db.getAllTeachers();
                sort(teachers.begin(), teachers.end(), [](const Teacher& a, const Teacher& b) {
                    return a.getDepartment() < b.getDepartment();
                });

                cout << "\n=== ВИКЛАДАЧІ (ВІДСОРТОВАНІ ЗА КАФЕДРОЮ) ===" << endl;
                for (const auto& teacher : teachers) {
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
    } while (choice != 0);
}

void manageStudents(Admin& admin, DatabaseManager& db, bool isAdmin) {
    int choice;
    do {
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
        if (!isAdmin && (choice == 2 || choice == 3 || choice == 4)) {
            cout << "❌ ДОСТУП ЗАБОРОНЕНО! Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                vector<Student> students = db.getAllStudents();
                cout << "\n=== СПИСОК СТУДЕНТІВ (" << students.size() << ") ===" << endl;
                for (const auto& student : students) {
                    student.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2: {
                cout << "\n=== ДОДАВАННЯ СТУДЕНТА ===" << endl;
                string name, lastName, email, studentID, educationalProgram;
                cout << "Ім'я: "; getline(cin, name);
                cout << "Прізвище: "; getline(cin, lastName);
                cout << "Email: "; getline(cin, email);
                cout << "ID студента (формат ST001): "; getline(cin, studentID);
                cout << "Освітня програма: "; getline(cin, educationalProgram);

                try {
                    Student student(name, lastName, email, studentID, educationalProgram);
                    db.addStudent(student);
                    cout << "✅ Студента успішно додано!" << endl;
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\n=== РЕДАГУВАННЯ СТУДЕНТА ===" << endl;
                string studentID;
                cout << "Введіть ID студента для редагування: ";
                getline(cin, studentID);

                Student* student = db.getStudent(studentID);
                if (student) {
                    string name, lastName, email, educationalProgram;
                    cout << "Нове ім'я: "; getline(cin, name);
                    cout << "Нове прізвище: "; getline(cin, lastName);
                    cout << "Новий email: "; getline(cin, email);
                    cout << "Нова освітня програма: "; getline(cin, educationalProgram);

                    try {
                        Student newData(name, lastName, email, studentID, educationalProgram);
                        if (db.editStudent(studentID, newData)) {
                            cout << "✅ Студента успішно оновлено!" << endl;
                        }
                    } catch (const exception& e) {
                        cout << "❌ ПОМИЛКА: " << e.what() << endl;
                    }
                } else {
                    cout << "❌ Студента не знайдено!" << endl;
                }
                break;
            }
            case 4: {
                cout << "\n=== ВИДАЛЕННЯ СТУДЕНТА ===" << endl;
                string studentID;
                cout << "Введіть ID студента для видалення: ";
                getline(cin, studentID);

                try {
                    if (db.deleteStudent(studentID)) {
                        cout << "✅ Студента успішно видалено!" << endl;
                    } else {
                        cout << "❌ Студента не знайдено!" << endl;
                    }
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 5: {
                string studentID;
                cout << "Введіть ID студента: ";
                getline(cin, studentID);
                Student* student = db.getStudent(studentID);
                if (student) {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    student->print();
                } else {
                    cout << "❌ Студента не знайдено!" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

void manageTeachers(Admin& admin, DatabaseManager& db, bool isAdmin) {
    int choice;
    do {
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

        if (!isAdmin && (choice == 2 || choice == 3 || choice == 4)) {
            cout << "❌ ДОСТУП ЗАБОРОНЕНО! Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                vector<Teacher> teachers = db.getAllTeachers();
                cout << "\n=== СПИСОК ВИКЛАДАЧІВ (" << teachers.size() << ") ===" << endl;
                for (const auto& teacher : teachers) {
                    teacher.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2: {
                cout << "\n=== ДОДАВАННЯ ВИКЛАДАЧА ===" << endl;
                string name, lastName, email, teacherID, department, academicDegree;
                cout << "Ім'я: "; getline(cin, name);
                cout << "Прізвище: "; getline(cin, lastName);
                cout << "Email: "; getline(cin, email);
                cout << "ID викладача (формат PR001): "; getline(cin, teacherID);
                cout << "Кафедра: "; getline(cin, department);
                cout << "Вчений ступінь: "; getline(cin, academicDegree);

                try {
                    Teacher teacher(name, lastName, email, teacherID, department, academicDegree);
                    db.addTeacher(teacher);
                    cout << "✅ Викладача успішно додано!" << endl;
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\n=== РЕДАГУВАННЯ ВИКЛАДАЧА ===" << endl;
                string teacherID;
                cout << "Введіть ID викладача для редагування: ";
                getline(cin, teacherID);

                Teacher* teacher = db.getTeacher(teacherID);
                if (teacher) {
                    string name, lastName, email, department, academicDegree;
                    cout << "Нове ім'я: "; getline(cin, name);
                    cout << "Нове прізвище: "; getline(cin, lastName);
                    cout << "Новий email: "; getline(cin, email);
                    cout << "Нова кафедра: "; getline(cin, department);
                    cout << "Новий вчений ступінь: "; getline(cin, academicDegree);

                    try {
                        Teacher newData(name, lastName, email, teacherID, department, academicDegree);
                        if (db.editTeacher(teacherID, newData)) {
                            cout << "✅ Викладача успішно оновлено!" << endl;
                        }
                    } catch (const exception& e) {
                        cout << "❌ ПОМИЛКА: " << e.what() << endl;
                    }
                } else {
                    cout << "❌ Викладача не знайдено!" << endl;
                }
                break;
            }
            case 4: {
                cout << "\n=== ВИДАЛЕННЯ ВИКЛАДАЧА ===" << endl;
                string teacherID;
                cout << "Введіть ID викладача для видалення: ";
                getline(cin, teacherID);

                try {
                    if (db.deleteTeacher(teacherID)) {
                        cout << "✅ Викладача успішно видалено!" << endl;
                    } else {
                        cout << "❌ Викладача не знайдено!" << endl;
                    }
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 5: {
                string teacherID;
                cout << "Введіть ID викладача: ";
                getline(cin, teacherID);
                Teacher* teacher = db.getTeacher(teacherID);
                if (teacher) {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    teacher->print();
                } else {
                    cout << "❌ Викладача не знайдено!" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

void manageSubjects(Admin& admin, DatabaseManager& db, bool isAdmin) {
    int choice;
    do {
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

        if (!isAdmin && (choice == 2 || choice == 3 || choice == 4)) {
            cout << "❌ ДОСТУП ЗАБОРОНЕНО! Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                vector<Subject> subjects = db.getAllSubjects();
                cout << "\n=== СПИСОК ПРЕДМЕТІВ (" << subjects.size() << ") ===" << endl;
                for (const auto& subject : subjects) {
                    subject.print();
                    cout << "------------------------" << endl;
                }
                break;
            }
            case 2: {
                cout << "\n=== ДОДАВАННЯ ПРЕДМЕТА ===" << endl;
                string subjectId, subjectName, teacherId;
                int credits, semester;
                cout << "ID предмета (формат SJ001): "; getline(cin, subjectId);
                cout << "Назва предмета: "; getline(cin, subjectName);
                cout << "Кредити ECTS: "; cin >> credits;
                cout << "ID викладача (формат PR001): "; clearInputBuffer(); getline(cin, teacherId);
                cout << "Семестр: "; cin >> semester;
                clearInputBuffer();

                try {
                    Subject subject(subjectId, subjectName, credits, teacherId, semester);
                    db.addSubject(subject);
                    cout << "✅ Предмет успішно додано!" << endl;
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\n=== РЕДАГУВАННЯ ПРЕДМЕТА ===" << endl;
                string subjectId;
                cout << "Введіть ID предмета для редагування: ";
                getline(cin, subjectId);

                Subject* subject = db.getSubject(subjectId);
                if (subject) {
                    string subjectName, teacherId;
                    int credits, semester;
                    cout << "Нова назва предмета: "; getline(cin, subjectName);
                    cout << "Нові кредити ECTS: "; cin >> credits;
                    cout << "Новий ID викладача: "; clearInputBuffer(); getline(cin, teacherId);
                    cout << "Новий семестр: "; cin >> semester;
                    clearInputBuffer();

                    try {
                        Subject newData(subjectId, subjectName, credits, teacherId, semester);
                        if (db.editSubject(subjectId, newData)) {
                            cout << "✅ Предмет успішно оновлено!" << endl;
                        }
                    } catch (const exception& e) {
                        cout << "❌ ПОМИЛКА: " << e.what() << endl;
                    }
                } else {
                    cout << "❌ Предмет не знайдено!" << endl;
                }
                break;
            }
            case 4: {
                cout << "\n=== ВИДАЛЕННЯ ПРЕДМЕТА ===" << endl;
                string subjectId;
                cout << "Введіть ID предмета для видалення: ";
                getline(cin, subjectId);

                try {
                    if (db.deleteSubject(subjectId)) {
                        cout << "✅ Предмет успішно видалено!" << endl;
                    } else {
                        cout << "❌ Предмет не знайдено!" << endl;
                    }
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 5: {
                string subjectId;
                cout << "Введіть ID предмета: ";
                getline(cin, subjectId);
                Subject* subject = db.getSubject(subjectId);
                if (subject) {
                    cout << "\n=== РЕЗУЛЬТАТ ПОШУКУ ===" << endl;
                    subject->print();
                } else {
                    cout << "❌ Предмет не знайдено!" << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

void manageUsers(Admin& admin, DatabaseManager& db, bool isAdmin) {
    if (!isAdmin) {
        cout << "❌ ДОСТУП ЗАБОРОНЕНО! Ця функція доступна тільки для адміністратора." << endl;
        return;
    }

    int choice;
    do {
        cout << "\n=== КЕРУВАННЯ КОРИСТУВАЧАМИ ===" << endl;
        cout << "1. Переглянути всіх користувачів" << endl;
        cout << "2. Додати користувача" << endl;
        cout << "3. Видалити користувача" << endl;
        cout << "0. Повернутися до головного меню" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1: {
                cout << "\n=== СПИСОК КОРИСТУВАЧІВ ===" << endl;
                admin.listUsers();
                break;
            }
            case 2: {
                cout << "\n=== ДОДАВАННЯ КОРИСТУВАЧА ===" << endl;
                string username, password;
                cout << "Ім'я користувача: "; getline(cin, username);
                cout << "Пароль: "; getline(cin, password);

                try {
                    if (admin.addUser(username, password)) {
                        cout << "✅ Користувача успішно додано!" << endl;
                    }
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\n=== ВИДАЛЕННЯ КОРИСТУВАЧА ===" << endl;
                string username;
                cout << "Ім'я користувача для видалення: "; getline(cin, username);

                try {
                    if (admin.removeUser(username)) {
                        cout << "✅ Користувача успішно видалено!" << endl;
                    }
                } catch (const exception& e) {
                    cout << "❌ ПОМИЛКА: " << e.what() << endl;
                }
                break;
            }
            case 0:
                cout << "Повернення до головного меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

void mainMenu(Admin& admin, DatabaseManager& db, bool isAdmin) {
    int choice;
    do {
        cout << "\n=== ГОЛОВНЕ МЕНЮ ===" << endl;
        cout << "1. Керування студентами" << endl;
        cout << "2. Керування викладачами" << endl;
        cout << "3. Керування предметами" << endl;
        cout << "4. Керування користувачами" << (isAdmin ? "" : " (🔒)") << endl;
        cout << "5. Пошук та фільтрація" << endl;
        cout << "6. Допомога" << endl;
        cout << "0. Вийти" << endl;
        cout << "Оберіть опцію: ";
        cin >> choice;
        clearInputBuffer();

        // Перевірка прав для адмін-функцій
        if (!isAdmin && choice == 4) {
            cout << "❌ ДОСТУП ЗАБОРОНЕНО! Ця функція доступна тільки для адміністратора." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                manageStudents(admin, db, isAdmin);
                break;
            case 2:
                manageTeachers(admin, db, isAdmin);
                break;
            case 3:
                manageSubjects(admin, db, isAdmin);
                break;
            case 4:
                manageUsers(admin, db, isAdmin);
                break;
            case 5:
                searchAndFilter(admin, db, isAdmin);
                break;
            case 6:
                displayHelp();
                break;
            case 0:
                cout << "Вихід з меню..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (choice != 0);
}

int main() {
    setupUkrainianSupport();

    Admin admin;
    DatabaseManager db;

    cout << "=== СИСТЕМА УПРАВЛІННЯ НАВЧАЛЬНИМ ЗАКЛАДОМ ===" << endl;
    cout << "Версія з підтримкою української мови" << endl;

    // Завантаження даних при запуску
    try {
        admin.loadUsersFromFile("users.txt");
        db.loadFromFile("students.csv", "teachers.csv", "subjects.csv");
        cout << "Дані успішно завантажено!" << endl;
    } catch (const exception& e) {
        cout << "Помилка завантаження даних: " << e.what() << endl;
    }

    int mainChoice;
    do {
        cout << "\n=== ВХІД ДО СИСТЕМИ ===" << endl;
        cout << "1. Увійти як адміністратор" << endl;
        cout << "2. Увійти як студент" << endl;
        cout << "3. Вийти" << endl;
        cout << "Оберіть опцію: ";
        cin >> mainChoice;
        clearInputBuffer();

        switch (mainChoice) {
            case 1: {
                string username, password;
                cout << "Логін: "; getline(cin, username);
                cout << "Пароль: "; getline(cin, password);

                if (admin.authenticate(username, password)) {
                    cout << "✅ Успішний вхід як адміністратор!" << endl;
                    mainMenu(admin, db, true);
                } else {
                    cout << "❌ Помилка автентифікації! Невірний логін або пароль." << endl;
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "Логін: "; getline(cin, username);
                cout << "Пароль: "; getline(cin, password);

                if (admin.authenticate(username, password)) {
                    cout << "✅ Успішний вхід як студент!" << endl;
                    mainMenu(admin, db, false);
                } else {
                    cout << "❌ Помилка автентифікації! Невірний логін або пароль." << endl;
                }
                break;
            }
            case 3:
                cout << "Завершення роботи..." << endl;
                break;
            default:
                cout << "Невірний вибір!" << endl;
        }
    } while (mainChoice != 3);

    // Збереження даних при виході
    try {
        admin.saveUsersToFile("users.txt");
        db.saveToFile("students.csv", "teachers.csv", "subjects.csv");
        cout << "Дані успішно збережено!" << endl;
    } catch (const exception& e) {
        cout << "Помилка збереження даних: " << e.what() << endl;
    }

    cout << "Дякуємо за використання нашої системи!" << endl;
    return 0;
}