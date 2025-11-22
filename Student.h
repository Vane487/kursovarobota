#pragma once

#include "Person.h"
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Простір імен University для компонентів управління університетом
 */
namespace University {

/**
 * @class Student
 * @brief Клас, що представляє студента університету
 *
 * Надає функціонал для управління інформацією про студента,
 * включаючи запис на предмети, управління освітньою програмою та навчальним навантаженням.
 */
class Student : public Person
{
private:
    // Поля
    std::string studentID;                   ///< Ідентифікатор студента
    std::string educationalProgram;          ///< Освітня програма
    std::vector<std::string> enrolledSubjects; ///< Записані предмети
    static bool ukrainianSupportInitialized;  ///< Статус ініціалізації української мови

public:
    // Конструктори та деструктор

    /**
     * @brief Конструктор за замовчуванням
     */
    Student();

    /**
     * @brief Конструктор з параметрами
     * @param name Ім'я студента
     * @param lastName Прізвище студента
     * @param email Електронна пошта
     * @param studentID Ідентифікатор студента
     * @param educationalProgram Освітня програма
     */
    Student(const std::string& name, const std::string& lastName,
            const std::string& email, const std::string& studentID,
            const std::string& educationalProgram);

    /**
     * @brief Деструктор
     */
    ~Student() override;

    // Властивості

    /**
     * @brief Отримує ідентифікатор студента
     * @return Ідентифікатор студента
     */
    std::string getStudentID() const;

    /**
     * @brief Отримує освітню програму
     * @return Назва освітньої програми
     */
    std::string getEducationalProgram() const;

    /**
     * @brief Отримує список записаних предметів
     * @return Вектор ідентифікаторів предметів
     */
    std::vector<std::string> getEnrolledSubjects() const;

    /**
     * @brief Встановлює ідентифікатор студента
     * @param studentID Ідентифікатор студента
     */
    void setStudentID(const std::string& studentID);

    /**
     * @brief Встановлює освітню програму
     * @param educationalProgram Назва освітньої програми
     */
    void setEducationalProgram(const std::string& educationalProgram);

    // Публічні методи

    /**
     * @brief Записує студента на предмет
     * @param subjectId Ідентифікатор предмету
     */
    void enrollSubject(const std::string& subjectId);

    /**
     * @brief Відписує студента з предмету
     * @param subjectId Ідентифікатор предмету
     */
    void dropSubject(const std::string& subjectId);

    /**
     * @brief Перевіряє чи записаний студент на предмет
     * @param subjectId Ідентифікатор предмету
     * @return true якщо записаний на предмет
     */
    bool isEnrolled(const std::string& subjectId) const;

    /**
     * @brief Виводить список предметів студента
     */
    void listSubjects() const;

    /**
     * @brief Очищає список записаних предметів
     */
    void clearSubjects();

    /**
     * @brief Отримує кількість записаних предметів
     * @return Кількість предметів
     */
    int getEnrolledSubjectsCount() const;

    /**
     * @brief Змінює освітню програму
     * @param newEducationalProgram Нова освітня програма
     */
    void changeEducationalProgram(const std::string& newEducationalProgram);

    /**
     * @brief Розраховує навчальне навантаження
     * @return Навантаження у умовних одиницях
     */
    double calculateWorkload() const;

    /**
     * @brief Перевіряє чи може студент записатися на більше предметів
     * @param maxSubjects Максимальна кількість предметів
     * @return true якщо може записатися на більше предметів
     */
    bool canEnrollMoreSubjects(int maxSubjects = 10) const;

    /**
     * @brief Перевіряє чи має студент певний предмет
     * @param subjectId Ідентифікатор предмету
     * @return true якщо має предмет
     */
    bool hasSubject(const std::string& subjectId) const;

    // Перевизначені методи

    /**
     * @brief Виводить інформацію про студента
     */
    void print() const override;

    /**
     * @brief Перетворює об'єкт в рядок
     * @return Рядкове представлення об'єкта
     */
    std::string toString() const override;

    /**
     * @brief Перевіряє коректність даних студента
     * @return true якщо дані коректні
     */
    bool isValid() const override;

    // Оператори

    /**
     * @brief Оператор порівняння
     * @param other Об'єкт для порівняння
     * @return true якщо об'єкти рівні
     */
    bool operator==(const Student& other) const;

private:
    // Приватні методи

    /**
     * @brief Валідує ідентифікатор студента
     * @param id Ідентифікатор для валідації
     * @return true якщо ідентифікатор коректний
     */
    bool validateStudentID(const std::string& id) const;

    /**
     * @brief Ініціалізує підтримку української мови
     */
    void initializeUkrainianSupport();

    // Константи
    static constexpr int DEFAULT_MAX_SUBJECTS = 10; ///< Максимальна кількість предметів за замовчуванням
};

} // namespace University