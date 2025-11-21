#ifndef KURSOVA_STUDENT_H
#define KURSOVA_STUDENT_H

#pragma once
#include "Person.h"
#include <vector>
#include <string>
#include <stdexcept>

class Student : public Person {
private:
    std::string studentID;
    std::string educationalProgram;
    std::vector<std::string> enrolledSubjects;

public:
    // Конструктори
    Student();
    Student(const std::string& name, const std::string& lastName,
            const std::string& email,
            const std::string& studentID, const std::string& educationalProgram);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    ~Student() override;

    // Getter методи
    std::string getStudentID() const { return studentID; }
    std::string getEducationalProgram() const { return educationalProgram; }
    std::vector<std::string> getEnrolledSubjects() const { return enrolledSubjects; }

    // Setter методи
    void setStudentID(const std::string& studentID);
    void setEducationalProgram(const std::string& educationalProgram);

    // ВЛАСНІ МЕТОДИ (8+ методів):
    void enrollSubject(const std::string& subjectId);
    void dropSubject(const std::string& subjectId);
    bool isEnrolled(const std::string& subjectId) const;
    void listSubjects() const;
    void clearSubjects();
    int getEnrolledSubjectsCount() const;
    void changeEducationalProgram(const std::string& newEducationalProgram);
    double calculateWorkload() const;
    bool canEnrollMoreSubjects(int maxSubjects = 10) const;
    bool hasSubject(const std::string& subjectId) const;

    // Перевизначені методи
    void print() const override;
    std::string toString() const override;
    bool isValid() const override;

    // Оператори
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;
    bool operator==(const Student& other) const;

private:
    bool validateStudentID(const std::string& id) const;
};
#endif