/**
* @file FileConstants.h
 * @brief Заголовний файл з константами для файлів та повідомлень
 */

#ifndef FILECONSTANTS_H
#define FILECONSTANTS_H

#include <string>

namespace University {

    /**
     * @class FileConstants
     * @brief Клас, що містить константи для шляхів до файлів, ролей користувачів та системних повідомлень
     */
    class FileConstants {
    public:
        // Шляхи до файлів
        static const std::string STUDENTS_FILE;   ///< Шлях до файлу студентів
        static const std::string TEACHERS_FILE;   ///< Шлях до файлу викладачів
        static const std::string SUBJECTS_FILE;   ///< Шлях до файлу предметів
        static const std::string USERS_FILE;      ///< Шлях до файлу користувачів

        // Ролі користувачів
        static const std::string ROLE_ADMIN;      ///< Роль адміністратора
        static const std::string ROLE_TEACHER;    ///< Роль викладача
        static const std::string ROLE_STUDENT;    ///< Роль студента

        // Повідомлення
        static const std::string MSG_EXIT_SYSTEM;     ///< Повідомлення про вихід з системи
        static const std::string MSG_LOGIN_PROMPT;    ///< Запит на введення логіну
        static const std::string MSG_PASSWORD_PROMPT; ///< Запит на введення паролю
        static const std::string MSG_LOGIN_SUCCESS;   ///< Повідомлення про успішний вхід
        static const std::string MSG_LOGIN_FAILED;    ///< Повідомлення про невдалий вхід
    };

} // namespace University

#endif // FILECONSTANTS_H