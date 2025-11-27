#include "FileConstants.h"

namespace University {

    // File paths
    const std::string FileConstants::STUDENTS_FILE = "students.csv";
    const std::string FileConstants::TEACHERS_FILE = "teachers.csv";
    const std::string FileConstants::SUBJECTS_FILE = "subjects.csv";
    const std::string FileConstants::USERS_FILE = "users.csv";

    // User roles
    const std::string FileConstants::ROLE_ADMIN = "Адміністратор";
    const std::string FileConstants::ROLE_TEACHER = "Викладач";
    const std::string FileConstants::ROLE_STUDENT = "Студент";

    // Messages
    const std::string FileConstants::MSG_EXIT_SYSTEM = "Вихід з системи...";
    const std::string FileConstants::MSG_LOGIN_PROMPT = "Введіть ім'я користувача: ";
    const std::string FileConstants::MSG_PASSWORD_PROMPT = "Введіть пароль: ";
    const std::string FileConstants::MSG_LOGIN_SUCCESS = "Успішний вхід!";
    const std::string FileConstants::MSG_LOGIN_FAILED = "Невірне ім'я користувача або пароль!";

} // namespace University