#include "DatabaseManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "FileConstants.h"

using namespace std;

namespace University {

DatabaseManager::DatabaseManager()
{
    LoadFromFile(FileConstants::STUDENTS_FILE,
                 FileConstants::TEACHERS_FILE,
                 FileConstants::SUBJECTS_FILE);
}

DatabaseManager::DatabaseManager(const string& studentsFile,
                                 const string& teachersFile,
                                 const string& subjectsFile)
{
    LoadFromFile(studentsFile, teachersFile, subjectsFile);
}

DatabaseManager::DatabaseManager(const DatabaseManager& other)
    : m_students(other.m_students),
      m_teachers(other.m_teachers),
      m_subjects(other.m_subjects)
{
}

DatabaseManager::DatabaseManager(DatabaseManager&& other) noexcept
    : m_students(std::move(other.m_students)),
      m_teachers(std::move(other.m_teachers)),
      m_subjects(std::move(other.m_subjects))
{
}

DatabaseManager::~DatabaseManager()
{
}

bool DatabaseManager::AddStudent(const Student& student)
{
    if (!student.isValid())
    {
        throw invalid_argument("Некоректні дані студента");
    }
    if (GetStudent(student.getStudentID()) != nullptr)
    {
        throw invalid_argument("Студент з таким ID вже існує: " + student.getStudentID());
    }
    m_students.push_back(student);
    SaveToFile(FileConstants::STUDENTS_FILE,
               FileConstants::TEACHERS_FILE,
               FileConstants::SUBJECTS_FILE);
    return true;
}

bool DatabaseManager::AddTeacher(const Teacher& teacher)
{
    if (!teacher.isValid())
    {
        throw invalid_argument("Некоректні дані викладача");
    }
    if (GetTeacher(teacher.getTeacherID()) != nullptr)
    {
        throw invalid_argument("Викладач з таким ID вже існує: " + teacher.getTeacherID());
    }
    m_teachers.push_back(teacher);
    SaveToFile(FileConstants::STUDENTS_FILE,
               FileConstants::TEACHERS_FILE,
               FileConstants::SUBJECTS_FILE);
    return true;
}

bool DatabaseManager::AddSubject(const Subject& subject)
{
    if (!subject.isValid())
    {
        throw invalid_argument("Некоректні дані предмета");
    }
    if (GetSubject(subject.getSubjectId()) != nullptr)
    {
        throw invalid_argument("Предмет з таким ID вже існує: " + subject.getSubjectId());
    }
    m_subjects.push_back(subject);
    SaveToFile(FileConstants::STUDENTS_FILE,
               FileConstants::TEACHERS_FILE,
               FileConstants::SUBJECTS_FILE);
    return true;
}

bool DatabaseManager::EditStudent(const string& studentId, const Student& newData)
{
    if (!newData.isValid())
    {
        throw invalid_argument("Некоректні нові дані студента");
    }
    for (auto& student : m_students)
    {
        if (student.getStudentID() == studentId)
        {
            student = newData;
            SaveToFile(FileConstants::STUDENTS_FILE,
                       FileConstants::TEACHERS_FILE,
                       FileConstants::SUBJECTS_FILE);
            return true;
        }
    }
    return false;
}

bool DatabaseManager::EditTeacher(const string& teacherId, const Teacher& newData)
{
    if (!newData.isValid())
    {
        throw invalid_argument("Некоректні нові дані викладача");
    }
    for (auto& teacher : m_teachers)
    {
        if (teacher.getTeacherID() == teacherId)
        {
            teacher = newData;
            SaveToFile(FileConstants::STUDENTS_FILE,
                       FileConstants::TEACHERS_FILE,
                       FileConstants::SUBJECTS_FILE);
            return true;
        }
    }
    return false;
}

bool DatabaseManager::EditSubject(const string& subjectId, const Subject& newData)
{
    if (!newData.isValid())
    {
        throw invalid_argument("Некоректні нові дані предмета");
    }
    for (auto& subject : m_subjects)
    {
        if (subject.getSubjectId() == subjectId)
        {
            subject = newData;
            SaveToFile(FileConstants::STUDENTS_FILE,
                       FileConstants::TEACHERS_FILE,
                       FileConstants::SUBJECTS_FILE);
            return true;
        }
    }
    return false;
}

bool DatabaseManager::DeleteStudent(const string& studentId)
{
    auto it = remove_if(m_students.begin(), m_students.end(),
        [&](const Student& s) { return s.getStudentID() == studentId; });
    if (it != m_students.end())
    {
        m_students.erase(it, m_students.end());
        SaveToFile(FileConstants::STUDENTS_FILE,
                   FileConstants::TEACHERS_FILE,
                   FileConstants::SUBJECTS_FILE);
        return true;
    }
    return false;
}

bool DatabaseManager::DeleteTeacher(const string& teacherId)
{
    auto it = remove_if(m_teachers.begin(), m_teachers.end(),
        [&](const Teacher& t) { return t.getTeacherID() == teacherId; });
    if (it != m_teachers.end())
    {
        m_teachers.erase(it, m_teachers.end());
        SaveToFile(FileConstants::STUDENTS_FILE,
                   FileConstants::TEACHERS_FILE,
                   FileConstants::SUBJECTS_FILE);
        return true;
    }
    return false;
}

bool DatabaseManager::DeleteSubject(const string& subjectId)
{
    auto it = remove_if(m_subjects.begin(), m_subjects.end(),
        [&](const Subject& s) { return s.getSubjectId() == subjectId; });
    if (it != m_subjects.end())
    {
        m_subjects.erase(it, m_subjects.end());
        SaveToFile(FileConstants::STUDENTS_FILE,
                   FileConstants::TEACHERS_FILE,
                   FileConstants::SUBJECTS_FILE);
        return true;
    }
    return false;
}

vector<Student> DatabaseManager::GetAllStudents() const
{
    return m_students;
}

vector<Teacher> DatabaseManager::GetAllTeachers() const
{
    return m_teachers;
}

vector<Subject> DatabaseManager::GetAllSubjects() const
{
    return m_subjects;
}

Student* DatabaseManager::GetStudent(const string& studentId)
{
    for (auto& student : m_students)
    {
        if (student.getStudentID() == studentId)
        {
            return &student;
        }
    }
    return nullptr;
}

Teacher* DatabaseManager::GetTeacher(const string& teacherId)
{
    for (auto& teacher : m_teachers)
    {
        if (teacher.getTeacherID() == teacherId)
        {
            return &teacher;
        }
    }
    return nullptr;
}

Subject* DatabaseManager::GetSubject(const string& subjectId)
{
    for (auto& subject : m_subjects)
    {
        if (subject.getSubjectId() == subjectId)
        {
            return &subject;
        }
    }
    return nullptr;
}

vector<Student> DatabaseManager::SearchStudentsByName(const string& name) const
{
    vector<Student> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& student : m_students)
    {
        string fullName = student.getFullName();
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        if (fullName.find(lowerName) != string::npos)
        {
            result.push_back(student);
        }
    }
    return result;
}

vector<Teacher> DatabaseManager::SearchTeachersByName(const string& name) const
{
    vector<Teacher> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& teacher : m_teachers)
    {
        string fullName = teacher.getFullName();
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        if (fullName.find(lowerName) != string::npos)
        {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::SearchSubjectsByName(const string& name) const
{
    vector<Subject> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& subject : m_subjects)
    {
        string subjectName = subject.getSubjectName();
        transform(subjectName.begin(), subjectName.end(), subjectName.begin(), ::tolower);
        if (subjectName.find(lowerName) != string::npos)
        {
            result.push_back(subject);
        }
    }
    return result;
}

vector<Student> DatabaseManager::FilterStudentsByProgram(const string& program) const
{
    vector<Student> result;
    string lowerProgram = program;
    transform(lowerProgram.begin(), lowerProgram.end(), lowerProgram.begin(), ::tolower);

    for (const auto& student : m_students)
    {
        string studentProgram = student.getEducationalProgram();
        transform(studentProgram.begin(), studentProgram.end(), studentProgram.begin(), ::tolower);
        if (studentProgram.find(lowerProgram) != string::npos)
        {
            result.push_back(student);
        }
    }
    return result;
}

vector<Teacher> DatabaseManager::FilterTeachersByDepartment(const string& department) const
{
    vector<Teacher> result;
    string lowerDepartment = department;
    transform(lowerDepartment.begin(), lowerDepartment.end(), lowerDepartment.begin(), ::tolower);

    for (const auto& teacher : m_teachers)
    {
        string teacherDepartment = teacher.getDepartment();
        transform(teacherDepartment.begin(), teacherDepartment.end(), teacherDepartment.begin(), ::tolower);
        if (teacherDepartment.find(lowerDepartment) != string::npos)
        {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::FilterSubjectsBySemester(int semester) const
{
    vector<Subject> result;
    for (const auto& subject : m_subjects)
    {
        if (subject.getSemester() == semester)
        {
            result.push_back(subject);
        }
    }
    return result;
}

void DatabaseManager::SortStudentsByName(bool ascending)
{
    sort(m_students.begin(), m_students.end(),
        [ascending](const Student& a, const Student& b)
        {
            return ascending ? a.getFullName() < b.getFullName()
                            : a.getFullName() > b.getFullName();
        });
}

void DatabaseManager::SortTeachersByName(bool ascending)
{
    sort(m_teachers.begin(), m_teachers.end(),
        [ascending](const Teacher& a, const Teacher& b)
        {
            return ascending ? a.getFullName() < b.getFullName()
                            : a.getFullName() > b.getFullName();
        });
}

void DatabaseManager::SortSubjectsByName(bool ascending)
{
    sort(m_subjects.begin(), m_subjects.end(),
        [ascending](const Subject& a, const Subject& b)
        {
            return ascending ? a.getSubjectName() < b.getSubjectName()
                            : a.getSubjectName() > b.getSubjectName();
        });
}

void DatabaseManager::DisplaySortedStudents(bool ascending)
{
    SortStudentsByName(ascending);
    vector<Student> students = GetAllStudents();

    if (students.empty())
    {
        cout << " Немає студентів для відображення" << endl;
        return;
    }

    cout << "=== " << (ascending ? "ВІДСОРТОВАНІ СТУДЕНТИ (A-Z)"
                                : "ВІДСОРТОВАНІ СТУДЕНТИ (Z-A)") << " ===" << endl;
    for (size_t i = 0; i < students.size(); i++)
    {
        cout << i + 1 << ". " << students[i].getFullName()
             << " (ID: " << students[i].getStudentID()
             << ", Програма: " << students[i].getEducationalProgram() << ")" << endl;
    }
}

void DatabaseManager::DisplaySortedTeachers(bool ascending)
{
    SortTeachersByName(ascending);
    vector<Teacher> teachers = GetAllTeachers();

    if (teachers.empty())
    {
        cout << " Немає викладачів для відображення" << endl;
        return;
    }

    cout << "=== " << (ascending ? "ВІДСОРТОВАНІ ВИКЛАДАЧІ (A-Z)"
                                : "ВІДСОРТОВАНІ ВИКЛАДАЧІ (Z-A)") << " ===" << endl;
    for (size_t i = 0; i < teachers.size(); i++)
    {
        cout << i + 1 << ". " << teachers[i].getFullName()
             << " (ID: " << teachers[i].getTeacherID()
             << ", Кафедра: " << teachers[i].getDepartment() << ")" << endl;
    }
}

void DatabaseManager::DisplaySortedSubjects(bool ascending)
{
    SortSubjectsByName(ascending);
    vector<Subject> subjects = GetAllSubjects();

    if (subjects.empty())
    {
        cout << " Немає предметів для відображення" << endl;
        return;
    }

    cout << "=== " << (ascending ? "ВІДСОРТОВАНІ ПРЕДМЕТИ (A-Z)"
                                : "ВІДСОРТОВАНІ ПРЕДМЕТИ (Z-A)") << " ===" << endl;
    for (size_t i = 0; i < subjects.size(); i++)
    {
        cout << i + 1 << ". " << subjects[i].getSubjectName()
             << " (ID: " << subjects[i].getSubjectId()
             << ", Семестр: " << subjects[i].getSemester()
             << ", Кредити: " << subjects[i].getEctsCredits() << ")" << endl;
    }
}

vector<Student> DatabaseManager::GetSortedStudentsByName(bool ascending)
{
    SortStudentsByName(ascending);
    return m_students;
}

vector<Teacher> DatabaseManager::GetSortedTeachersByName(bool ascending)
{
    SortTeachersByName(ascending);
    return m_teachers;
}

vector<Subject> DatabaseManager::GetSortedSubjectsByName(bool ascending)
{
    SortSubjectsByName(ascending);
    return m_subjects;
}

bool DatabaseManager::LoadFromFile(const string& studentsFile,
                                   const string& teachersFile,
                                   const string& subjectsFile)
{
    bool success = true;

    if (!LoadStudentsFromFile(studentsFile))
    {
        cerr << "Помилка завантаження студентів з файлу: " << studentsFile << endl;
        success = false;
    }

    if (!LoadTeachersFromFile(teachersFile))
    {
        cerr << "Помилка завантаження викладачів з файлу: " << teachersFile << endl;
        success = false;
    }

    if (!LoadSubjectsFromFile(subjectsFile))
    {
        cerr << "Помилка завантаження предметів з файлу: " << subjectsFile << endl;
        success = false;
    }

    return success;
}

bool DatabaseManager::SaveToFile(const string& studentsFile,
                                 const string& teachersFile,
                                 const string& subjectsFile) const
{
    return SaveStudentsToFile(studentsFile) &&
           SaveTeachersToFile(teachersFile) &&
           SaveSubjectsToFile(subjectsFile);
}

void DatabaseManager::Clear()
{
    m_students.clear();
    m_teachers.clear();
    m_subjects.clear();
}

bool DatabaseManager::LoadStudentsFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не вдалося відкрити файл студентів: " << filename << endl;
        return false;
    }

    m_students.clear();
    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string id, name, lastName, program, email;

        if (getline(ss, id, ',') && getline(ss, name, ',') &&
            getline(ss, lastName, ',') && getline(ss, program, ',') &&
            getline(ss, email))
        {
            m_students.push_back(Student(name, lastName, email, id, program));
        }
    }

    file.close();
    return true;
}

bool DatabaseManager::LoadTeachersFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не вдалося відкрити файл викладачів: " << filename << endl;
        return false;
    }

    m_teachers.clear();
    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string id, name, lastName, department, degreeStr, email;

        if (getline(ss, id, ',') && getline(ss, name, ',') &&
            getline(ss, lastName, ',') && getline(ss, department, ',') &&
            getline(ss, degreeStr, ',') && getline(ss, email))
        {
            try
            {
                int degreeInt = stoi(degreeStr);
                AcademicDegree degree = static_cast<AcademicDegree>(degreeInt);
                m_teachers.push_back(Teacher(name, lastName, email, id, department, degree));
            }
            catch (const exception& e)
            {
                cerr << "Помилка парсингу даних викладача: " << e.what() << endl;
            }
        }
    }

    file.close();
    return true;
}

bool DatabaseManager::LoadSubjectsFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не вдалося відкрити файл предметів: " << filename << endl;
        return false;
    }

    m_subjects.clear();
    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string id, name, creditsStr, semesterStr, teacherId;

        if (getline(ss, id, ',') && getline(ss, name, ',') &&
            getline(ss, creditsStr, ',') && getline(ss, semesterStr, ',') &&
            getline(ss, teacherId))
        {
            try
            {
                int credits = stoi(creditsStr);
                int semester = stoi(semesterStr);
                m_subjects.push_back(Subject(id, name, credits, teacherId, semester));
            }
            catch (const exception& e)
            {
                cerr << "Помилка парсингу даних предмета: " << e.what() << endl;
            }
        }
    }

    file.close();
    return true;
}

bool DatabaseManager::SaveStudentsToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не вдалося відкрити файл для збереження студентів: " << filename << endl;
        return false;
    }

    for (const auto& student : m_students)
    {
        file << student.getStudentID() << ","
             << student.getName() << ","
             << student.getLastName() << ","
             << student.getEducationalProgram() << ","
             << student.getEmail() << endl;
    }

    file.close();
    return true;
}

bool DatabaseManager::SaveTeachersToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не вдалося відкрити файл для збереження викладачів: " << filename << endl;
        return false;
    }

    for (const auto& teacher : m_teachers)
    {
        file << teacher.getTeacherID() << ","
             << teacher.getName() << ","
             << teacher.getLastName() << ","
             << teacher.getDepartment() << ","
             << static_cast<int>(teacher.getAcademicDegree()) << ","
             << teacher.getEmail() << endl;
    }

    file.close();
    return true;
}

bool DatabaseManager::SaveSubjectsToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Не вдалося відкрити файл для збереження предметів: " << filename << endl;
        return false;
    }

    for (const auto& subject : m_subjects)
    {
        file << subject.getSubjectId() << ","
             << subject.getSubjectName() << ","
             << subject.getEctsCredits() << ","
             << subject.getSemester() << ","
             << subject.getTeacherId() << endl;
    }

    file.close();
    return true;
}

} // namespace University