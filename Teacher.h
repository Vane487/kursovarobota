#pragma once
#include "Person.h"
#include <string>
#include <stdexcept>
#include <iostream>

class Teacher : public Person {
private:
    std::string teacherID;
    std::string department;
    std::string academicDegree;
    std::string subjectId;

public:
    // Конструктори
    Teacher();
    Teacher(const std::string& name, const std::string& lastName,
            const std::string& email,
            const std::string& teacherID, const std::string& department,
            const std::string& academicDegree);
    Teacher(const Teacher& other);
    Teacher(Teacher&& other) noexcept;
    ~Teacher() override;

    // Getter методи
    std::string getTeacherID() const { return teacherID; }
    std::string getDepartment() const { return department; }
    std::string getAcademicDegree() const { return academicDegree; }
    std::string getSubjectId() const { return subjectId; }

    // Setter методи
    void setTeacherID(const std::string& teacherID);
    void setDepartment(const std::string& department);
    void setAcademicDegree(const std::string& academicDegree);
    void setSubjectId(const std::string& subjectId);

    // ВЛАСНІ МЕТОДИ (7+ методів):
    bool assignToSubject(const std::string& subjectId);
    bool removeFromSubject();
    bool hasAssignedSubject() const;
    void promote(const std::string& newDegree);
    void changeDepartment(const std::string& newDepartment);
    bool canTeachSubject(const std::string& subjectId) const;
    std::string getTeachingStatus() const;
    double calculateWorkload() const;
    bool isAvailableForNewSubject() const;
    void updateAcademicProfile(const std::string& newDegree, const std::string& newDepartment);

    // Перевизначені методи
    void print() const override;
    std::string toString() const override;
    bool isValid() const override;

    // Оператори
    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;
    bool operator==(const Teacher& other) const;
    bool operator!=(const Teacher& other) const;

private:
    bool validateTeacherID(const std::string& id) const;
    void setupUkrainianSupport() const;
};