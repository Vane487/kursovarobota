#pragma once
#include <string>

namespace University {

    class FileConstants {
    public:
        // Шляхи до файлів
        static const std::string STUDENTS_FILE;
        static const std::string TEACHERS_FILE;
        static const std::string SUBJECTS_FILE;
        static const std::string USERS_FILE;
        static const std::string ASSIGNMENTS_FILE;

        // Роздільники
        static const std::string FILE_DELIMITER;
        static const std::string TEACHER_SUBJECT_DELIMITER;

        // Ролі
        static const std::string ROLE_ADMIN;
        static const std::string ROLE_TEACHER;
        static const std::string ROLE_STUDENT;

        // Повідомлення для аутентифікації
        static const std::string MSG_LOGIN_PROMPT;
        static const std::string MSG_PASSWORD_PROMPT;
        static const std::string MSG_LOGIN_SUCCESS;
        static const std::string MSG_LOGIN_FAILED;
        static const std::string MSG_ADMIN_SUCCESS;
        static const std::string MSG_NO_ADMIN_RIGHTS;
        static const std::string MSG_EXIT_SYSTEM;
    };

} // namespace University