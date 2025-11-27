/**
 * @file Student.h
 * @brief Заголовний файл для класу Student
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <vector>
#include <string>

namespace University {

    /**
     * @class Student
     * @brief Клас для представлення студента у системі
     * 
     * Наслідує від Person та додає функціональність для управління 
     * записами на предмети та освітньою програмою
     */
    class Student : public Person {
    private:
        std::string studentID;                          ///< Унікальний ідентифікатор студента
        std::string educationalProgram;                 ///< Освітня програма студента
        std::vector<std::string> enrolledSubjects;      ///< Список предметів, на які записаний студент
        static bool ukrainianSupportInitialized;        ///< Прапор ініціалізації української мови

        /**
         * @brief Ініціалізує підтримку української мови
         */
        void initializeUkrainianSupport();

        /**
         * @brief Валідує ID студента
         * @param id ID для валідації
         * @return true якщо ID коректний, false в іншому випадку
         */
        bool validateStudentID(const std::string& id) const;

    public:
        /**
         * @brief Конструктор за замовчуванням
         */
        Student();

        /**
         * @brief Конструктор з параметрами
         * @param name Ім'я студента
         * @param lastName Прізвище студента
         * @param email Електронна пошта
         * @param studentID Унікальний ідентифікатор
         * @param educationalProgram Освітня програма
         */
        Student(const std::string& name, const std::string& lastName,
                const std::string& email, const std::string& studentID,
                const std::string& educationalProgram);

        /**
         * @brief Конструктор копіювання
         * @param other Об'єкт для копіювання
         */
        Student(const Student& other);

        /**
         * @brief Конструктор переміщення
         * @param other Об'єкт для переміщення
         */
        Student(Student&& other) noexcept;

        /**
         * @brief Деструктор
         */
        ~Student();

        // Гетери
        std::string getStudentID() const;
        std::string getEducationalProgram() const;
        std::vector<std::string> getEnrolledSubjects() const;
        int getEnrolledSubjectsCount() const;

        // Сетери
        void setStudentID(const std::string& studentID);
        void setEducationalProgram(const std::string& educationalProgram);

        // Методи
        void enrollSubject(const std::string& subjectId);
        void dropSubject(const std::string& subjectId);
        bool isEnrolled(const std::string& subjectId) const;
        void listSubjects() const;
        void clearSubjects();
        void changeEducationalProgram(const std::string& newEducationalProgram);

        // Перевизначені методи
        void print() const override;
        std::string toString() const override;
        bool isValid() const override;

        // Оператори
        Student& operator=(const Student& other);
        Student& operator=(Student&& other) noexcept;
        bool operator==(const Student& other) const;
    };

} // namespace University

#endif // STUDENT_H