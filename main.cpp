#include <iostream>
#include <memory>
#include "MenuManager.h"
#include "UserManager.h"
#include "DatabaseManager.h"
#include "AssignmentManager.h"

using namespace std;
using namespace University;

int main() {
    // Налаштування для української мови
    setlocale(LC_ALL, "uk_UA.UTF-8");

    cout << " Запуск системи управління Навчальним Закладом..." << endl;
    cout << "=============================================" << endl;

    try {

        auto userManager = make_unique<UserManager>();
        auto dbManager = make_unique<DatabaseManager>();
        auto assignmentManager = make_unique<AssignmentManager>();


        MenuManager menu(
            userManager.get(),
            dbManager.get(),
            assignmentManager.get(),
            "",
            UserRole::Student
        );


        menu.ShowWelcomeMenu();

    } catch (const exception& e) {
        cerr << " Помилка: " << e.what() << endl;
        cerr << "Програма завершує роботу..." << endl;
        return 1;
    }

    cout << " Система завершила роботу успішно!" << endl;
    return 0;
}