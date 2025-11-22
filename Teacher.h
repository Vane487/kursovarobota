#pragma once

#include "Person.h"
#include <string>
#include <stdexcept>
#include <iostream>


namespace University {
    using namespace std;

/**
 * @enum AcademicDegree
 * @brief Наукові ступені викладачів
 */
enum class AcademicDegree {
    BACHELOR,      ///< Бакалавр
    MASTER,        ///< Магістр
    DOCTOR         ///< Доктор наук
};

/**
 * @class Teacher
 * @brief Клас, що представляє викладача університету
 *
 * Надає функціонал для управління інформацією про викладача,
 * включаючи призначення предметів, управління кафедрою та
 * науковим ступенем.
 */
class Teacher : public Person
{
private:
    // Поля
    std::string teacherID;                  ///< Ідентифікатор викладача
    std::string department;                 ///< Кафедра
    AcademicDegree academicDegree;          ///< Науковий ступінь
    std::string subjectId;                  ///< Ідентифікатор предмету
    static bool ukrainianSupportInitialized; ///< Підтримка української мови

    static constexpr double DEFAULT_WORKLOAD_HOURS = 120.0; ///< Стандартне навантаження

    // Приватні методи
    /**
     * @brief Валідує ідентифікатор викладача
     * @param id Ідентифікатор для валідації
     * @return true якщо ідентифікатор коректний
     */
    bool validateTeacherID(const std::string& id) const;

    /**
     * @brief Ініціалізує підтримку української мови
     */
    void initializeUkrainianSupport();

public:
    // Конструктори та деструктор
    Teacher();
    Teacher(const std::string& name, const std::string& lastName,
            const std::string& email, const std::string& teacherID,
            const std::string& department, AcademicDegree degree);
    Teacher(const Teacher& other);
    Teacher(Teacher&& other) noexcept;
    ~Teacher() override;

    // Властивості
    std::string getTeacherID() const;
    std::string getDepartment() const;
    AcademicDegree getAcademicDegree() const;
    std::string getSubjectId() const;
    std::string getAcademicDegreeString() const;

    void setTeacherID(const std::string& teacherID);
    void setDepartment(const std::string& department);
    void setAcademicDegree(AcademicDegree degree);
    void setSubjectId(const std::string& subjectId);

    // Методи
    bool assignToSubject(const std::string& subjectId);
    bool removeFromSubject();
    bool hasAssignedSubject() const;
    void promote(AcademicDegree newDegree);
    void changeDepartment(const std::string& newDepartment);
    bool canTeachSubject(const std::string& subjectId) const;
    std::string getTeachingStatus() const;
    double calculateWorkload() const;
    bool isAvailableForNewSubject() const;
    void updateAcademicProfile(AcademicDegree newDegree,
                              const std::string& newDepartment);

    // Перевизначені методи
    void print() const override;
    std::string toString() const override;
    bool isValid() const override;

    // Оператори
    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;
    bool operator==(const Teacher& other) const;
    bool operator!=(const Teacher& other) const;
};

} // namespace University
