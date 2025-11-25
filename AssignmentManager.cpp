#include "AssignmentManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DatabaseManager.h"

using namespace std;

namespace University {

// Константи повідомлень
const string AssignmentManager::MSG_ERROR_TEACHER_HAS_SUBJECT = "Помилка: Викладач вже має призначений предмет!";
const string AssignmentManager::MSG_ERROR_SUBJECT_HAS_TEACHER = "Помилка: Предмет вже має призначеного викладача!";
const string AssignmentManager::MSG_SUCCESS_TEACHER_ASSIGNED = "Успішно призначено";
const string AssignmentManager::MSG_SUCCESS_TEACHER_REMOVED = "Успішно видалено призначення";
const string AssignmentManager::MSG_STATUS_NO_SUBJECT = "Викладач не має призначеного предмету";
const string AssignmentManager::MSG_STATUS_HAS_SUBJECT = "Викладач веде предмет: ";

// Нові константи для студентів
const string AssignmentManager::MSG_ERROR_STUDENT_ALREADY_ENROLLED = "Помилка: Студент вже записаний на цей предмет!";
const string AssignmentManager::MSG_SUCCESS_STUDENT_ENROLLED = "Успішно записано студента на предмет";
const string AssignmentManager::MSG_SUCCESS_STUDENT_UNENROLLED = "Успішно видалено студента з предмету";

AssignmentManager::AssignmentManager() {
    loadFromFile();
}

// === МЕТОДИ ДЛЯ ВИКЛАДАЧІВ ===

bool AssignmentManager::assignToSubject(const std::string& teacherId, const std::string& subId) {
    // Перевіряємо чи вже має предмет
    if (m_teacherSubjects.find(teacherId) != m_teacherSubjects.end()) {
        cout << MSG_ERROR_TEACHER_HAS_SUBJECT << endl;
        return false;
    }

    // Перевіряємо чи предмет вже має викладача
    if (m_subjectTeachers.find(subId) != m_subjectTeachers.end()) {
        cout << MSG_ERROR_SUBJECT_HAS_TEACHER << endl;
        return false;
    }

    m_teacherSubjects[teacherId] = subId;
    m_subjectTeachers[subId] = teacherId;

    cout << MSG_SUCCESS_TEACHER_ASSIGNED << ": " << teacherId << " -> " << subId << endl;
    saveToFile();
    return true;
}

bool AssignmentManager::removeFromSubject(const std::string& teacherId) {
    auto it = m_teacherSubjects.find(teacherId);
    if (it == m_teacherSubjects.end()) {
        cout << "Помилка: Викладач не має призначених предметів для видалення" << endl;
        return false;
    }

    string subjectId = it->second;
    m_teacherSubjects.erase(it);
    m_subjectTeachers.erase(subjectId);

    cout << MSG_SUCCESS_TEACHER_REMOVED << ": " << teacherId << " з предмету " << subjectId << endl;
    saveToFile();
    return true;
}

std::string AssignmentManager::getTeachingStatus(const std::string& teacherId) const {
    auto it = m_teacherSubjects.find(teacherId);
    if (it == m_teacherSubjects.end()) return MSG_STATUS_NO_SUBJECT;
    return MSG_STATUS_HAS_SUBJECT + it->second;
}

std::string AssignmentManager::getTeacherSubject(const std::string& teacherId) const {
    auto it = m_teacherSubjects.find(teacherId);
    return (it != m_teacherSubjects.end()) ? it->second : "";
}

std::map<std::string, std::string> AssignmentManager::getAllTeacherAssignments() const {
    return m_teacherSubjects;
}

// === НОВІ МЕТОДИ ДЛЯ СТУДЕНТІВ ===

bool AssignmentManager::enrollStudentInSubject(const std::string& studentId, const std::string& subjectId) {
    // Перевіряємо, чи студент вже записаний на цей предмет
    if (isStudentEnrolled(studentId, subjectId)) {
        cout << MSG_ERROR_STUDENT_ALREADY_ENROLLED << endl;
        return false;
    }

    // Додаємо студента до предмету
    m_studentSubjects[studentId].push_back(subjectId);
    m_subjectStudents[subjectId].push_back(studentId);

    cout << MSG_SUCCESS_STUDENT_ENROLLED << ": " << studentId << " -> " << subjectId << endl;
    saveToFile();
    return true;
}

bool AssignmentManager::unenrollStudentFromSubject(const std::string& studentId, const std::string& subjectId) {
    // Перевіряємо, чи студент записаний на предмет
    if (!isStudentEnrolled(studentId, subjectId)) {
        cout << "Помилка: Студент не записаний на цей предмет" << endl;
        return false;
    }

    // Видаляємо студента з предмету
    auto& studentSubjects = m_studentSubjects[studentId];
    studentSubjects.erase(remove(studentSubjects.begin(), studentSubjects.end(), subjectId), studentSubjects.end());

    auto& subjectStudents = m_subjectStudents[subjectId];
    subjectStudents.erase(remove(subjectStudents.begin(), subjectStudents.end(), studentId), subjectStudents.end());

    // Видаляємо порожні записи
    if (studentSubjects.empty()) {
        m_studentSubjects.erase(studentId);
    }
    if (subjectStudents.empty()) {
        m_subjectStudents.erase(subjectId);
    }

    cout << MSG_SUCCESS_STUDENT_UNENROLLED << ": " << studentId << " <- " << subjectId << endl;
    saveToFile();
    return true;
}

bool AssignmentManager::isStudentEnrolled(const std::string& studentId, const std::string& subjectId) const {
    auto it = m_studentSubjects.find(studentId);
    if (it == m_studentSubjects.end()) return false;

    const auto& subjects = it->second;
    return find(subjects.begin(), subjects.end(), subjectId) != subjects.end();
}

std::vector<std::string> AssignmentManager::getStudentSubjects(const std::string& studentId) const {
    auto it = m_studentSubjects.find(studentId);
    return (it != m_studentSubjects.end()) ? it->second : std::vector<std::string>();
}

// === ДОДАТКОВІ МЕТОДИ ===

std::string AssignmentManager::getDetailedTeachingStatus(const std::string& teacherId, DatabaseManager* dbManager) const {
    auto it = m_teacherSubjects.find(teacherId);
    if (it == m_teacherSubjects.end()) {
        return MSG_STATUS_NO_SUBJECT;
    }

    string subjectId = it->second;
    if (dbManager) {
        Subject* subject = dbManager->GetSubject(subjectId);
        if (subject) {
            return "Викладач призначений на предмет: " + subject->getSubjectName() + " (ID: " + subjectId + ")";
        }
    }

    return MSG_STATUS_HAS_SUBJECT + subjectId;
}

void AssignmentManager::debugPrintAllAssignments() const {
    cout << "=== ВСІ ПРИЗНАЧЕННЯ ВИКЛАДАЧІВ ===" << endl;
    if (m_teacherSubjects.empty()) {
        cout << "Призначень не знайдено" << endl;
    } else {
        for (const auto& assignment : m_teacherSubjects) {
            cout << "Викладач " << assignment.first << " -> Предмет " << assignment.second << endl;
        }
    }
    cout << "=================================" << endl;
}

// === ФАЙЛОВІ ОПЕРАЦІЇ ===

bool AssignmentManager::loadFromFile() {
    // Використовуємо прямий шлях до файлу
    ifstream file("assignments.csv");
    if (!file.is_open()) {
        cout << "Інформація: Файл призначень не знайдений. Буде створений новий при збереженні." << endl;
        return true;
    }

    // Очищаємо поточні дані перед завантаженням
    m_teacherSubjects.clear();
    m_subjectTeachers.clear();
    m_studentSubjects.clear();
    m_subjectStudents.clear();

    string line;
    int teacherCount = 0;
    int studentCount = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, id1, id2;

        // Використовуємо кому як роздільник
        if (getline(ss, type, '|') &&
            getline(ss, id1, '|') &&
            getline(ss, id2)) {

            if (type == "T") {
                // teacherId -> subjectId
                m_teacherSubjects[id1] = id2;
                m_subjectTeachers[id2] = id1;
                teacherCount++;
            } else if (type == "S") {
                // studentId -> subjectId
                m_studentSubjects[id1].push_back(id2);
                m_subjectStudents[id2].push_back(id1);
                studentCount++;
            }
        }
    }

    file.close();
    cout << "Завантажено " << teacherCount << " призначень викладачів та "
         << studentCount << " записів студентів з файлу" << endl;
    return true;
}

bool AssignmentManager::saveToFile() const {
    // Використовуємо прямий шлях до файлу
    ofstream file("assignments.csv");
    if (!file.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл для запису: assignments.csv" << endl;
        return false;
    }

    int teacherCount = 0;
    int studentCount = 0;

    // Зберігаємо призначення викладачів
    for (const auto& assignment : m_teacherSubjects) {
        file << "T" << "|" << assignment.first << "|" << assignment.second << "\n";
        teacherCount++;
    }

    // Зберігаємо записи студентів
    for (const auto& enrollment : m_studentSubjects) {
        for (const auto& subjectId : enrollment.second) {
            file << "S" << "|" << enrollment.first << "|" << subjectId << "\n";
            studentCount++;
        }
    }

    file.close();
    cout << "Збережено " << teacherCount << " призначень викладачів та "
         << studentCount << " записів студентів у файл" << endl;
    return true;
}

} // namespace University
