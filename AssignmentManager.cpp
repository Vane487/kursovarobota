#include "AssignmentManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "DatabaseManager.h"

using namespace std;

namespace University {

const string AssignmentManager::MSG_ERROR_TEACHER_HAS_SUBJECT =
    "Помилка: Викладач вже має призначений предмет!";
const string AssignmentManager::MSG_ERROR_SUBJECT_HAS_TEACHER =
    "Помилка: Предмет вже має призначеного викладача!";
const string AssignmentManager::MSG_SUCCESS_TEACHER_ASSIGNED =
    "Успішно призначено";
const string AssignmentManager::MSG_SUCCESS_TEACHER_REMOVED =
    "Успішно видалено призначення";
const string AssignmentManager::MSG_STATUS_NO_SUBJECT =
    "Викладач не має призначеного предмету";
const string AssignmentManager::MSG_STATUS_HAS_SUBJECT =
    "Викладач веде предмет: ";
const string AssignmentManager::MSG_ERROR_STUDENT_ALREADY_ENROLLED =
    "Помилка: Студент вже записаний на цей предмет!";
const string AssignmentManager::MSG_SUCCESS_STUDENT_ENROLLED =
    "Успішно записано студента на предмет";
const string AssignmentManager::MSG_SUCCESS_STUDENT_UNENROLLED =
    "Успішно видалено студента з предмету";

AssignmentManager::AssignmentManager()
{
    loadFromFile();
}

bool AssignmentManager::assignToSubject(const string& teacherId, const string& subId)
{
    if (m_teacherSubjects.find(teacherId) != m_teacherSubjects.end())
    {
        cout << MSG_ERROR_TEACHER_HAS_SUBJECT << endl;
        return false;
    }

    if (m_subjectTeachers.find(subId) != m_subjectTeachers.end())
    {
        cout << MSG_ERROR_SUBJECT_HAS_TEACHER << endl;
        return false;
    }

    m_teacherSubjects[teacherId] = subId;
    m_subjectTeachers[subId] = teacherId;

    cout << MSG_SUCCESS_TEACHER_ASSIGNED << ": " << teacherId << " -> " << subId << endl;
    saveToFile();
    return true;
}

bool AssignmentManager::removeFromSubject(const string& teacherId)
{
    auto it = m_teacherSubjects.find(teacherId);
    if (it == m_teacherSubjects.end())
    {
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

string AssignmentManager::getTeachingStatus(const string& teacherId) const
{
    auto it = m_teacherSubjects.find(teacherId);
    if (it == m_teacherSubjects.end())
    {
        return MSG_STATUS_NO_SUBJECT;
    }
    return MSG_STATUS_HAS_SUBJECT + it->second;
}

string AssignmentManager::getTeacherSubject(const string& teacherId) const
{
    auto it = m_teacherSubjects.find(teacherId);
    return (it != m_teacherSubjects.end()) ? it->second : "";
}

map<string, string> AssignmentManager::getAllTeacherAssignments() const
{
    return m_teacherSubjects;
}

bool AssignmentManager::enrollStudentInSubject(const string& studentId, const string& subjectId)
{
    if (isStudentEnrolled(studentId, subjectId))
    {
        cout << MSG_ERROR_STUDENT_ALREADY_ENROLLED << endl;
        return false;
    }

    m_studentSubjects[studentId].push_back(subjectId);
    m_subjectStudents[subjectId].push_back(studentId);

    cout << MSG_SUCCESS_STUDENT_ENROLLED << ": " << studentId << " -> " << subjectId << endl;
    saveToFile();
    return true;
}

bool AssignmentManager::unenrollStudentFromSubject(const string& studentId, const string& subjectId)
{
    if (!isStudentEnrolled(studentId, subjectId))
    {
        cout << "Помилка: Студент не записаний на цей предмет" << endl;
        return false;
    }

    auto& studentSubjects = m_studentSubjects[studentId];
    auto removeIt = remove(studentSubjects.begin(), studentSubjects.end(), subjectId);
    studentSubjects.erase(removeIt, studentSubjects.end());

    auto& subjectStudents = m_subjectStudents[subjectId];
    removeIt = remove(subjectStudents.begin(), subjectStudents.end(), studentId);
    subjectStudents.erase(removeIt, subjectStudents.end());

    if (studentSubjects.empty())
    {
        m_studentSubjects.erase(studentId);
    }
    if (subjectStudents.empty())
    {
        m_subjectStudents.erase(subjectId);
    }

    cout << MSG_SUCCESS_STUDENT_UNENROLLED << ": " << studentId << " <- " << subjectId << endl;
    saveToFile();
    return true;
}

bool AssignmentManager::isStudentEnrolled(const string& studentId, const string& subjectId) const
{
    auto it = m_studentSubjects.find(studentId);
    if (it == m_studentSubjects.end())
    {
        return false;
    }

    const auto& subjects = it->second;
    return find(subjects.begin(), subjects.end(), subjectId) != subjects.end();
}

vector<string> AssignmentManager::getStudentSubjects(const string& studentId) const
{
    auto it = m_studentSubjects.find(studentId);
    return (it != m_studentSubjects.end()) ? it->second : vector<string>();
}

string AssignmentManager::getDetailedTeachingStatus(const string& teacherId, DatabaseManager* dbManager) const
{
    auto it = m_teacherSubjects.find(teacherId);
    if (it == m_teacherSubjects.end())
    {
        return MSG_STATUS_NO_SUBJECT;
    }

    string subjectId = it->second;
    if (dbManager)
    {
        Subject* subject = dbManager->GetSubject(subjectId);
        if (subject)
        {
            return "Викладач призначений на предмет: " + subject->getSubjectName() +
                   " (ID: " + subjectId + ")";
        }
    }

    return MSG_STATUS_HAS_SUBJECT + subjectId;
}

void AssignmentManager::debugPrintAllAssignments() const
{
    cout << "=== ВСІ ПРИЗНАЧЕННЯ ВИКЛАДАЧІВ ===" << endl;
    if (m_teacherSubjects.empty())
    {
        cout << "Призначень не знайдено" << endl;
    }
    else
    {
        for (const auto& assignment : m_teacherSubjects)
        {
            cout << "Викладач " << assignment.first << " -> Предмет " << assignment.second << endl;
        }
    }
    cout << "=================================" << endl;
}

bool AssignmentManager::loadFromFile()
{
    ifstream file("assignments.csv");
    if (!file.is_open())
    {
        cout << "Інформація: Файл призначень не знайдений. Буде створений новий при збереженні." << endl;
        return true;
    }

    m_teacherSubjects.clear();
    m_subjectTeachers.clear();
    m_studentSubjects.clear();
    m_subjectStudents.clear();

    string line;
    int teacherCount = 0;
    int studentCount = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string type, id1, id2;

        if (getline(ss, type, '|') &&
            getline(ss, id1, '|') &&
            getline(ss, id2))
        {
            if (type == "T")
            {
                m_teacherSubjects[id1] = id2;
                m_subjectTeachers[id2] = id1;
                teacherCount++;
            }
            else if (type == "S")
            {
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

bool AssignmentManager::saveToFile() const
{
    ofstream file("assignments.csv");
    if (!file.is_open())
    {
        cerr << "Помилка: Не вдалося відкрити файл для запису: assignments.csv" << endl;
        return false;
    }

    int teacherCount = 0;
    int studentCount = 0;

    for (const auto& assignment : m_teacherSubjects)
    {
        file << "T" << "|" << assignment.first << "|" << assignment.second << "\n";
        teacherCount++;
    }

    for (const auto& enrollment : m_studentSubjects)
    {
        for (const auto& subjectId : enrollment.second)
        {
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