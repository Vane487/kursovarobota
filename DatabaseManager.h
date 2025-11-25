#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Student.h"
#include "Teacher.h"
#include "Subject.h"
#include <vector>
#include <string>

namespace University {

class DatabaseManager {
private:
    std::vector<Student> m_students;
    std::vector<Teacher> m_teachers;
    std::vector<Subject> m_subjects;

public:
    // Constructors and destructor
    DatabaseManager();
    DatabaseManager(const std::string& studentsFile,
                   const std::string& teachersFile,
                   const std::string& subjectsFile);
    DatabaseManager(const DatabaseManager& other);
    DatabaseManager(DatabaseManager&& other) noexcept;
    ~DatabaseManager();

    // Student methods
    std::vector<Student> GetAllStudents() const;
    Student* GetStudent(const std::string& id);
    bool AddStudent(const Student& student);
    bool EditStudent(const std::string& id, const Student& updatedStudent);
    bool DeleteStudent(const std::string& id);

    // Teacher methods
    std::vector<Teacher> GetAllTeachers() const;
    Teacher* GetTeacher(const std::string& id);
    bool AddTeacher(const Teacher& teacher);
    bool EditTeacher(const std::string& id, const Teacher& updatedTeacher);
    bool DeleteTeacher(const std::string& id);

    // Subject methods
    std::vector<Subject> GetAllSubjects() const;
    Subject* GetSubject(const std::string& id);
    bool AddSubject(const Subject& subject);
    bool EditSubject(const std::string& id, const Subject& updatedSubject);
    bool DeleteSubject(const std::string& id);

    // Search
    std::vector<Student> SearchStudentsByName(const std::string& name) const;
    std::vector<Teacher> SearchTeachersByName(const std::string& name) const;
    std::vector<Subject> SearchSubjectsByName(const std::string& name) const;

    // Filtering
    std::vector<Student> FilterStudentsByProgram(const std::string& program) const;
    std::vector<Teacher> FilterTeachersByDepartment(const std::string& department) const;
    std::vector<Subject> FilterSubjectsBySemester(int semester) const;

    // Sorting
    void SortStudentsByName(bool ascending = true);
    void SortTeachersByName(bool ascending = true);
    void SortSubjectsByName(bool ascending = true);

    // File operations
    bool LoadFromFile(const std::string& studentsFile,
                     const std::string& teachersFile,
                     const std::string& subjectsFile);
    bool SaveToFile(const std::string& studentsFile,
                   const std::string& teachersFile,
                   const std::string& subjectsFile) const;

    // Utility
    void Clear();


    // Private file operation methods
    bool LoadStudentsFromFile(const std::string& filename);
    bool LoadTeachersFromFile(const std::string& filename);
    bool LoadSubjectsFromFile(const std::string& filename);
    bool SaveStudentsToFile(const std::string& filename) const;
    bool SaveTeachersToFile(const std::string& filename) const;
    bool SaveSubjectsToFile(const std::string& filename) const;
};

} // namespace University

#endif // DATABASEMANAGER_H