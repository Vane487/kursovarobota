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

namespace University {

class DatabaseManager
{
private:
    std::vector<Student> m_students;
    std::vector<Teacher> m_teachers;
    std::vector<Subject> m_subjects;

public:
    // Конструктори та деструктор
    DatabaseManager();
    DatabaseManager(const DatabaseManager& other);
    DatabaseManager(DatabaseManager&& other) noexcept;
    ~DatabaseManager();

    // Властивості
    std::vector<Student>& GetStudents();
    const std::vector<Student>& GetStudents() const;
    std::vector<Teacher>& GetTeachers();
    const std::vector<Teacher>& GetTeachers() const;
    std::vector<Subject>& GetSubjects();
    const std::vector<Subject>& GetSubjects() const;

    void SetStudents(const std::vector<Student>& newStudents);
    void SetTeachers(const std::vector<Teacher>& newTeachers);
    void SetSubjects(const std::vector<Subject>& newSubjects);

    // Студенти
    void AddStudent(const Student& student);
    bool EditStudent(const std::string& studentId, const Student& newData);
    bool DeleteStudent(const std::string& studentId);
    Student* GetStudent(const std::string& studentId);
    const Student* GetStudent(const std::string& studentId) const;
    std::vector<Student> GetAllStudents() const;
    std::vector<Student> SearchStudentsByName(const std::string& name) const;
    std::vector<Student> SearchStudentsByProgram(const std::string& program) const;
    void SortStudentsByName(bool ascending = true);
    void SortStudentsById(bool ascending = true);

    // Викладачі
    void AddTeacher(const Teacher& teacher);
    bool EditTeacher(const std::string& teacherId, const Teacher& newData);
    bool DeleteTeacher(const std::string& teacherId);
    Teacher* GetTeacher(const std::string& teacherId);
    const Teacher* GetTeacher(const std::string& teacherId) const;
    std::vector<Teacher> GetAllTeachers() const;
    std::vector<Teacher> SearchTeachersByName(const std::string& name) const;
    std::vector<Teacher> SearchTeachersByDepartment(const std::string& department) const;
    std::vector<Teacher> FilterTeachersByDegree(const std::string& degree) const;
    void SortTeachersByName(bool ascending = true);
    void SortTeachersById(bool ascending = true);

    // Предмети
    void AddSubject(const Subject& subject);
    bool EditSubject(const std::string& subjectId, const Subject& newData);
    bool DeleteSubject(const std::string& subjectId);
    Subject* GetSubject(const std::string& subjectId);
    const Subject* GetSubject(const std::string& subjectId) const;
    std::vector<Subject> GetAllSubjects() const;
    std::vector<Subject> SearchSubjectsByName(const std::string& name) const;
    std::vector<Subject> FilterSubjectsByCredits(int minCredits, int maxCredits) const;
    std::vector<Subject> FilterSubjectsBySemester(int semester) const;
    std::vector<Subject> FilterSubjectsByTeacher(const std::string& teacherId) const;
    void SortSubjectsByName(bool ascending = true);
    void SortSubjectsByCredits(bool ascending = true);

    // ПРИЗНАЧЕННЯ СТУДЕНТІВ НА ПРЕДМЕТИ - ДОДАЙТЕ ЦЕЙ БЛОК
    bool AssignStudentToSubject(const std::string& studentId, const std::string& subjectId);
    bool RemoveStudentFromSubject(const std::string& studentId, const std::string& subjectId);
    std::vector<Subject> GetStudentSubjects(const std::string& studentId) const;
    std::vector<Student> GetSubjectStudents(const std::string& subjectId) const;
    bool IsStudentAssignedToSubject(const std::string& studentId, const std::string& subjectId) const;

    // Файлові операції
    bool LoadFromFile(const std::string& studentsFile,
                     const std::string& teachersFile,
                     const std::string& subjectsFile);
    bool SaveToFile(const std::string& studentsFile,
                   const std::string& teachersFile,
                   const std::string& subjectsFile) const;

    // Утиліти
    void Clear();
    int GetStudentCount() const;
    int GetTeacherCount() const;
    int GetSubjectCount() const;

    // Розширений пошук
    std::vector<Teacher> FindTeachersWithoutSubjects() const;
    std::vector<Subject> FindSubjectsWithoutTeacher() const;

private:
    bool LoadStudentsFromFile(const std::string& filename);
    bool LoadTeachersFromFile(const std::string& filename);
    bool LoadSubjectsFromFile(const std::string& filename);
    bool SaveStudentsToFile(const std::string& filename) const;
    bool SaveTeachersToFile(const std::string& filename) const;
    bool SaveSubjectsToFile(const std::string& filename) const;
};

} // namespace University