/// @file     Teacher.h
/// @brief    Заголовний файл для класу викладача
/// @author   Student Name
/// @date     2024
/// @namespace University

#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"
#include <string>

namespace University {

/// @enum    AcademicDegree
/// @brief   Академічні ступені викладача
enum class AcademicDegree {
    BACHELOR,  ///< Бакалавр
    MASTER,    ///< Магістр
    DOCTOR     ///< Доктор наук
};

/// @class   Teacher
/// @brief   Клас для представлення викладача університету
class Teacher : public Person {
private:
    std::string teacherID;        ///< Ідентифікатор викладача
    std::string department;       ///< Кафедра викладача
    AcademicDegree academicDegree; ///< Академічний ступінь

    static bool ukrainianSupportInitialized;           ///< Стан ініціалізації української підтримки
    static const double DEFAULT_WORKLOAD_HOURS;        ///< Стандартна кількість годин навантаження

    /// @brief Ініціалізація української підтримки
    void initializeUkrainianSupport();

    /// @brief Валідація ідентифікатора викладача
    /// @param id Ідентифікатор для перевірки
    /// @return Результат валідації
    bool validateTeacherID(const std::string& id) const;

public:
    /// @brief Конструктор за замовчуванням
    Teacher();

    /// @brief Параметризований конструктор
    /// @param name          Ім'я викладача
    /// @param lastName      Прізвище викладача
    /// @param email         Електронна пошта
    /// @param teacherID     Ідентифікатор викладача
    /// @param department    Кафедра
    /// @param degree        Академічний ступінь
    Teacher(const std::string& name, const std::string& lastName,
            const std::string& email, const std::string& teacherID,
            const std::string& department, AcademicDegree degree);

    /// @brief Конструктор копіювання
    /// @param other Об'єкт для копіювання
    Teacher(const Teacher& other);

    /// @brief Конструктор переміщення
    /// @param other Об'єкт для переміщення
    Teacher(Teacher&& other) noexcept;

    /// @brief Деструктор
    ~Teacher() override;

    // Геттери
    [[nodiscard]] std::string getTeacherID() const;
    [[nodiscard]] std::string getDepartment() const;
    [[nodiscard]] AcademicDegree getAcademicDegree() const;

    // Сеттери
    void setTeacherID(const std::string& id);
    void setDepartment(const std::string& dep);
    void setAcademicDegree(AcademicDegree deg);

    /// @brief Підвищення академічного ступеня
    /// @param newDegree Новий академічний ступінь
    void promote(AcademicDegree newDegree);

    /// @brief Зміна кафедри
    /// @param newDep Нова кафедра
    void changeDepartment(const std::string& newDep);

    /// @brief Отримання статусу викладання
    /// @return Статус викладання
    [[nodiscard]] std::string getTeachingStatus() const;

    /// @brief Розрахунок навчального навантаження
    /// @return Кількість годин навантаження
    [[nodiscard]] double calculateWorkload() const;

    /// @brief Перевірка доступності для нового предмета
    /// @return Результат перевірки
    [[nodiscard]] bool isAvailableForNewSubject() const;

    /// @brief Оновлення академічного профілю
    /// @param deg Новий академічний ступінь
    /// @param dep Нова кафедра
    void updateAcademicProfile(AcademicDegree deg, const std::string& dep);

    /// @brief Отримання рядкового представлення академічного ступеня
    /// @return Рядкове представлення ступеня
    [[nodiscard]] std::string getAcademicDegreeString() const;

    // Перевизначені методи
    void print() const override;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] bool isValid() const override;

    // Оператори
    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;
    bool operator==(const Teacher& other) const;
    bool operator!=(const Teacher& other) const;
};

} // namespace University

#endif // TEACHER_H