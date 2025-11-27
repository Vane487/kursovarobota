/**
 * @file Person.h
 * @brief Заголовний файл для базового класу Person
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <regex>

namespace University {

    /**
     * @class Person
     * @brief Базовий клас для представлення особи в системі
     *
     * Містить загальні властивості та методи для студентів та викладачів
     */
    class Person {
    private:
        std::string name;                    ///< Ім'я особи
        std::string lastName;                ///< Прізвище особи
        std::string email;                   ///< Електронна пошта
        static bool ukrainianSupportInitialized; ///< Прапори ініціалізації української мови

        /**
         * @brief Ініціалізує підтримку української мови
         */
        void initializeUkrainianSupport();

        /**
         * @brief Валідує дані особи
         * @throw invalid_argument якщо дані некоректні
         */
        void validateData() const;

    protected:
        static const int MIN_NAME_LENGTH = 2;   ///< Мінімальна довжина імені
        static const int MAX_NAME_LENGTH = 50;  ///< Максимальна довжина імені
        static const int MIN_EMAIL_LENGTH = 5;  ///< Мінімальна довжина email

    public:
        /**
         * @brief Конструктор за замовчуванням
         */
        Person();

        /**
         * @brief Конструктор з параметрами
         * @param name Ім'я
         * @param lastName Прізвище
         * @param email Електронна пошта
         */
        Person(const std::string& name, const std::string& lastName, const std::string& email);

        /**
         * @brief Конструктор копіювання
         * @param other Об'єкт для копіювання
         */
        Person(const Person& other);

        /**
         * @brief Конструктор переміщення
         * @param other Об'єкт для переміщення
         */
        Person(Person&& other) noexcept;

        /**
         * @brief Віртуальний деструктор
         */
        virtual ~Person();

        // Гетери
        std::string getName() const;
        std::string getLastName() const;
        std::string getEmail() const;
        std::string getFullName() const;

        // Сетери
        void setName(const std::string& name);
        void setLastName(const std::string& lastName);
        void setEmail(const std::string& email);

        // Методи
        virtual bool isValid() const;
        void updateContactInfo(const std::string& newEmail);
        virtual void print() const = 0;
        virtual std::string toString() const = 0;

        // Статичні методи валідації
        static bool validateEmail(const std::string& email);
        static bool validateName(const std::string& name);

        // Оператори
        Person& operator=(const Person& other);
        Person& operator=(Person&& other) noexcept;
        bool operator==(const Person& other) const;
    };

} // namespace University

#endif // PERSON_H