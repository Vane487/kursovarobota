#include "FileConstants.h"

namespace University {

    const std::string FileConstants::STUDENTS_FILE = "students.csv";
    const std::string FileConstants::TEACHERS_FILE = "teachers.csv";
    const std::string FileConstants::SUBJECTS_FILE = "subjects.csv";
    const std::string FileConstants::USERS_FILE = "users.txt";
    const std::string FileConstants::ASSIGNMENTS_FILE = "assignments.csv";

    const std::string FileConstants::FILE_DELIMITER = ",";
    const std::string FileConstants::TEACHER_SUBJECT_DELIMITER = "|";

    const std::string FileConstants::ROLE_ADMIN = "Адміністратор";
    const std::string FileConstants::ROLE_TEACHER = "Викладач";
    const std::string FileConstants::ROLE_STUDENT = "Студент";

    const std::string FileConstants::MSG_LOGIN_PROMPT = "Логін: ";
    const std::string FileConstants::MSG_PASSWORD_PROMPT = "Пароль: ";
    const std::string FileConstants::MSG_LOGIN_SUCCESS = "Успішний вхід!";
    const std::string FileConstants::MSG_LOGIN_FAILED = "Помилка автентифікації! Невірний логін або пароль.";
    const std::string FileConstants::MSG_ADMIN_SUCCESS = "Успішний вхід як адміністратор!";
    const std::string FileConstants::MSG_NO_ADMIN_RIGHTS = "Цей користувач не має прав адміністратора!";
    const std::string FileConstants::MSG_EXIT_SYSTEM = "Вихід з системи...";

} // namespace University