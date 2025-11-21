#pragma once
#include "Student.h"
#include "Teacher.h"
#include "Subject.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

class DatabaseManager {
private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    std::vector<Subject> subjects;

public:
    // Конструктори та деструктор
    DatabaseManager();
    DatabaseManager(const DatabaseManager& other);
    DatabaseManager(DatabaseManager&& other) noexcept;
    ~DatabaseManager();

    // Get методи для всіх контейнерів
    std::vector<Student>& getStudents() { return students; }
    const std::vector<Student>& getStudents() const { return students; }

    std::vector<Teacher>& getTeachers() { return teachers; }
    const std::vector<Teacher>& getTeachers() const { return teachers; }

    std::vector<Subject>& getSubjects() { return subjects; }
    const std::vector<Subject>& getSubjects() const { return subjects; }

    // Set методи для всіх контейнерів
    void setStudents(const std::vector<Student>& newStudents) { students = newStudents; }
    void setTeachers(const std::vector<Teacher>& newTeachers) { teachers = newTeachers; }
    void setSubjects(const std::vector<Subject>& newSubjects) { subjects = newSubjects; }

    // Студентські методи
    void addStudent(const Student& student);
    bool editStudent(const std::string& studentId, const Student& newData);
    bool deleteStudent(const std::string& studentId);
    Student* getStudent(const std::string& studentId);
    std::vector<Student> getAllStudents() const;
    std::vector<Student> searchStudentsByName(const std::string& name) const;
    std::vector<Student> searchStudentsByProgram(const std::string& program) const;
    void sortStudentsByName(bool ascending = true);
    void sortStudentsById(bool ascending = true);

    // Викладацькі методи
    void addTeacher(const Teacher& teacher);
    bool editTeacher(const std::string& teacherId, const Teacher& newData);
    bool deleteTeacher(const std::string& teacherId);
    Teacher* getTeacher(const std::string& teacherId);
    std::vector<Teacher> getAllTeachers() const;
    std::vector<Teacher> searchTeachersByName(const std::string& name) const;
    std::vector<Teacher> searchTeachersByDepartment(const std::string& department) const;
    std::vector<Teacher> filterTeachersByDegree(const std::string& degree) const;
    void sortTeachersByName(bool ascending = true);
    void sortTeachersById(bool ascending = true);

    // Предметні методи
    void addSubject(const Subject& subject);
    bool editSubject(const std::string& subjectId, const Subject& newData);
    bool deleteSubject(const std::string& subjectId);
    Subject* getSubject(const std::string& subjectId);
    std::vector<Subject> getAllSubjects() const;
    std::vector<Subject> searchSubjectsByName(const std::string& name) const;
    std::vector<Subject> filterSubjectsByCredits(int minCredits, int maxCredits) const;
    std::vector<Subject> filterSubjectsBySemester(int semester) const;
    std::vector<Subject> filterSubjectsByTeacher(const std::string& teacherId) const;
    void sortSubjectsByName(bool ascending = true);
    void sortSubjectsByCredits(bool ascending = true);

    // Файлові операції
    bool loadFromFile(const std::string& studentsFile, const std::string& teachersFile, const std::string& subjectsFile);
    bool saveToFile(const std::string& studentsFile, const std::string& teachersFile, const std::string& subjectsFile) const;

    // Утиліти
    void clear();
    int getStudentCount() const;
    int getTeacherCount() const;
    int getSubjectCount() const;

    // Розширений пошук
    std::vector<Teacher> findTeachersWithoutSubjects() const;
    std::vector<Subject> findSubjectsWithoutTeacher() const;

private:
    // Приватні методи для завантаження та збереження
    bool loadStudentsFromFile(const std::string& filename);
    bool loadTeachersFromFile(const std::string& filename);
    bool loadSubjectsFromFile(const std::string& filename);
    bool saveStudentsToFile(const std::string& filename) const;
    bool saveTeachersToFile(const std::string& filename) const;
    bool saveSubjectsToFile(const std::string& filename) const;
};