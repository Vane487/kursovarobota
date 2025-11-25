#ifndef ASSIGNMENTMANAGER_H
#define ASSIGNMENTMANAGER_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

namespace University {

// Попереднє оголошення для DatabaseManager
class DatabaseManager;

class AssignmentManager {
private:
    std::map<std::string, std::string> m_teacherSubjects;
    std::map<std::string, std::string> m_subjectTeachers;
    std::unordered_map<std::string, std::vector<std::string>> m_studentSubjects;
    std::unordered_map<std::string, std::vector<std::string>> m_subjectStudents;

public:
    AssignmentManager();

    // Основні методи для викладачів
    bool assignToSubject(const std::string& teacherId, const std::string& subId);
    bool removeFromSubject(const std::string& teacherId);
    std::string getTeachingStatus(const std::string& teacherId) const;
    std::string getTeacherSubject(const std::string& teacherId) const;
    std::map<std::string, std::string> getAllTeacherAssignments() const;

    // Методи для студентів
    bool enrollStudentInSubject(const std::string& studentId, const std::string& subjectId);
    bool unenrollStudentFromSubject(const std::string& studentId, const std::string& subjectId);
    bool isStudentEnrolled(const std::string& studentId, const std::string& subjectId) const;
    std::vector<std::string> getStudentSubjects(const std::string& studentId) const;

    // Файлові операції
    bool loadFromFile();
    bool saveToFile() const;

    // ДОДАЄМО ЛИШЕ ЦІ ДВА МЕТОДИ, ЯКІ ВИМАГАЄ ПОМИЛКА:
    std::string getDetailedTeachingStatus(const std::string& teacherId, DatabaseManager* dbManager) const;
    void debugPrintAllAssignments() const;

    // Статичні константи
    static const std::string MSG_ERROR_TEACHER_HAS_SUBJECT;
    static const std::string MSG_ERROR_SUBJECT_HAS_TEACHER;
    static const std::string MSG_SUCCESS_TEACHER_ASSIGNED;
    static const std::string MSG_SUCCESS_TEACHER_REMOVED;
    static const std::string MSG_STATUS_NO_SUBJECT;
    static const std::string MSG_STATUS_HAS_SUBJECT;
    static const std::string MSG_ERROR_STUDENT_ALREADY_ENROLLED;
    static const std::string MSG_SUCCESS_STUDENT_ENROLLED;
    static const std::string MSG_SUCCESS_STUDENT_UNENROLLED;
};

} // namespace University

#endif // ASSIGNMENTMANAGER_H