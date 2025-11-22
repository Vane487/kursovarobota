#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>



namespace University {
    using namespace std;

DatabaseManager::DatabaseManager()
{
    cout << "DatabaseManager конструктор за замовчуванням викликаний" << endl;
}

DatabaseManager::DatabaseManager(const DatabaseManager& other)
    : m_students(other.m_students), m_teachers(other.m_teachers),
      m_subjects(other.m_subjects)
{
    cout << "DatabaseManager копіювальний конструктор викликаний" << endl;
}

DatabaseManager::DatabaseManager(DatabaseManager&& other) noexcept
    : m_students(move(other.m_students)), m_teachers(move(other.m_teachers)),
      m_subjects(move(other.m_subjects))
{
    cout << "DatabaseManager переміщувальний конструктор викликаний" << endl;
}

DatabaseManager::~DatabaseManager()
{
    cout << "DatabaseManager деструктор викликаний" << endl;
    cout << "Знищено: " << m_students.size() << " студентів, "
         << m_teachers.size() << " викладачів, "
         << m_subjects.size() << " предметів" << endl;
}

// Гетери та сетери
vector<Student>& DatabaseManager::GetStudents() { return m_students; }
const vector<Student>& DatabaseManager::GetStudents() const { return m_students; }
vector<Teacher>& DatabaseManager::GetTeachers() { return m_teachers; }
const vector<Teacher>& DatabaseManager::GetTeachers() const { return m_teachers; }
vector<Subject>& DatabaseManager::GetSubjects() { return m_subjects; }
const vector<Subject>& DatabaseManager::GetSubjects() const { return m_subjects; }

void DatabaseManager::SetStudents(const vector<Student>& newStudents)
{
    m_students = newStudents;
}

void DatabaseManager::SetTeachers(const vector<Teacher>& newTeachers)
{
    m_teachers = newTeachers;
}

void DatabaseManager::SetSubjects(const vector<Subject>& newSubjects)
{
    m_subjects = newSubjects;
}

// Студенти
void DatabaseManager::AddStudent(const Student& student)
{
    if (!student.isValid())
    {
        throw invalid_argument("Некоректні дані студента");
    }
    if (GetStudent(student.getStudentID()) != nullptr)
    {
        throw invalid_argument("Студент з таким ID вже існує: " +
                              student.getStudentID());
    }
    m_students.push_back(student);
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
        return true;
    }
    return false;
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

const Student* DatabaseManager::GetStudent(const string& studentId) const
{
    for (const auto& student : m_students)
    {
        if (student.getStudentID() == studentId)
        {
            return &student;
        }
    }
    return nullptr;
}

vector<Student> DatabaseManager::GetAllStudents() const
{
    return m_students;
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

vector<Student> DatabaseManager::SearchStudentsByProgram(const string& program) const
{
    vector<Student> result;
    string lowerProgram = program;
    transform(lowerProgram.begin(), lowerProgram.end(), lowerProgram.begin(), ::tolower);

    for (const auto& student : m_students)
    {
        string studentProgram = student.getEducationalProgram();
        transform(studentProgram.begin(), studentProgram.end(),
                  studentProgram.begin(), ::tolower);
        if (studentProgram.find(lowerProgram) != string::npos)
        {
            result.push_back(student);
        }
    }
    return result;
}

void DatabaseManager::SortStudentsByName(bool ascending)
{
    sort(m_students.begin(), m_students.end(),
        [ascending](const Student& a, const Student& b)
        {
            if (ascending)
            {
                return a.getFullName() < b.getFullName();
            }
            else
            {
                return a.getFullName() > b.getFullName();
            }
        });
}

void DatabaseManager::SortStudentsById(bool ascending)
{
    sort(m_students.begin(), m_students.end(),
        [ascending](const Student& a, const Student& b)
        {
            if (ascending)
            {
                return a.getStudentID() < b.getStudentID();
            }
            else
            {
                return a.getStudentID() > b.getStudentID();
            }
        });
}

// Викладачі
void DatabaseManager::AddTeacher(const Teacher& teacher)
{
    if (!teacher.isValid())
    {
        throw invalid_argument("Некоректні дані викладача");
    }
    if (GetTeacher(teacher.getTeacherID()) != nullptr)
    {
        throw invalid_argument("Викладач з таким ID вже існує: " +
                              teacher.getTeacherID());
    }
    m_teachers.push_back(teacher);
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
            return true;
        }
    }
    return false;
}

bool DatabaseManager::DeleteTeacher(const string& teacherId)
{
    for (const auto& subject : m_subjects)
    {
        if (subject.getTeacherId() == teacherId)
        {
            throw invalid_argument("Не можна видалити викладача: " +
                                  subject.getSubjectName());
        }
    }

    auto it = remove_if(m_teachers.begin(), m_teachers.end(),
        [&](const Teacher& t) { return t.getTeacherID() == teacherId; });
    if (it != m_teachers.end())
    {
        m_teachers.erase(it, m_teachers.end());
        return true;
    }
    return false;
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

// ДОДАЙТЕ ЦЕЙ МЕТОД - він відсутній і викликає помилку лінкування!
const Teacher* DatabaseManager::GetTeacher(const string& teacherId) const
{
    for (const auto& teacher : m_teachers)
    {
        if (teacher.getTeacherID() == teacherId)
        {
            return &teacher;
        }
    }
    return nullptr;
}

vector<Teacher> DatabaseManager::GetAllTeachers() const
{
    return m_teachers;
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

vector<Teacher> DatabaseManager::SearchTeachersByDepartment(const string& department) const
{
    vector<Teacher> result;
    string lowerDepartment = department;
    transform(lowerDepartment.begin(), lowerDepartment.end(),
              lowerDepartment.begin(), ::tolower);

    for (const auto& teacher : m_teachers)
    {
        string teacherDepartment = teacher.getDepartment();
        transform(teacherDepartment.begin(), teacherDepartment.end(),
                  teacherDepartment.begin(), ::tolower);
        if (teacherDepartment.find(lowerDepartment) != string::npos)
        {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Teacher> DatabaseManager::FilterTeachersByDegree(const string& degree) const
{
    vector<Teacher> result;
    string lowerDegree = degree;
    transform(lowerDegree.begin(), lowerDegree.end(), lowerDegree.begin(), ::tolower);

    for (const auto& teacher : m_teachers)
    {
        string teacherDegreeStr;
        AcademicDegree teacherDegree = teacher.getAcademicDegree();

        if (teacherDegree == AcademicDegree::BACHELOR)
        {
            teacherDegreeStr = "bachelor";
        }
        else if (teacherDegree == AcademicDegree::MASTER)
        {
            teacherDegreeStr = "master";
        }
        else if (teacherDegree == AcademicDegree::DOCTOR)
        {
            teacherDegreeStr = "doctor";
        }
        else
        {
            teacherDegreeStr = "bachelor";
        }

        if (teacherDegreeStr.find(lowerDegree) != string::npos)
        {
            result.push_back(teacher);
        }
    }
    return result;
}

void DatabaseManager::SortTeachersByName(bool ascending)
{
    sort(m_teachers.begin(), m_teachers.end(),
        [ascending](const Teacher& a, const Teacher& b)
        {
            if (ascending)
            {
                return a.getFullName() < b.getFullName();
            }
            else
            {
                return a.getFullName() > b.getFullName();
            }
        });
}

void DatabaseManager::SortTeachersById(bool ascending)
{
    sort(m_teachers.begin(), m_teachers.end(),
        [ascending](const Teacher& a, const Teacher& b)
        {
            if (ascending)
            {
                return a.getTeacherID() < b.getTeacherID();
            }
            else
            {
                return a.getTeacherID() > b.getTeacherID();
            }
        });
}

// Предмети
void DatabaseManager::AddSubject(const Subject& subject)
{
    if (!subject.isValid())
    {
        throw invalid_argument("Некоректні дані предмета");
    }
    if (GetSubject(subject.getSubjectId()) != nullptr)
    {
        throw invalid_argument("Предмет з таким ID вже існує: " +
                              subject.getSubjectId());
    }
    m_subjects.push_back(subject);
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
            return true;
        }
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
        return true;
    }
    return false;
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

const Subject* DatabaseManager::GetSubject(const string& subjectId) const
{
    for (const auto& subject : m_subjects)
    {
        if (subject.getSubjectId() == subjectId)
        {
            return &subject;
        }
    }
    return nullptr;
}

vector<Subject> DatabaseManager::GetAllSubjects() const
{
    return m_subjects;
}

vector<Subject> DatabaseManager::SearchSubjectsByName(const string& name) const
{
    vector<Subject> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& subject : m_subjects)
    {
        string subjectName = subject.getSubjectName();
        transform(subjectName.begin(), subjectName.end(),
                  subjectName.begin(), ::tolower);
        if (subjectName.find(lowerName) != string::npos)
        {
            result.push_back(subject);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::FilterSubjectsByCredits(int minCredits, int maxCredits) const
{
    vector<Subject> result;
    for (const auto& subject : m_subjects)
    {
        int credits = subject.getEctsCredits();
        if (credits >= minCredits && credits <= maxCredits)
        {
            result.push_back(subject);
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

vector<Subject> DatabaseManager::FilterSubjectsByTeacher(const string& teacherId) const
{
    vector<Subject> result;
    for (const auto& subject : m_subjects)
    {
        if (subject.getTeacherId() == teacherId)
        {
            result.push_back(subject);
        }
    }
    return result;
}

void DatabaseManager::SortSubjectsByName(bool ascending)
{
    sort(m_subjects.begin(), m_subjects.end(),
        [ascending](const Subject& a, const Subject& b)
        {
            if (ascending)
            {
                return a.getSubjectName() < b.getSubjectName();
            }
            else
            {
                return a.getSubjectName() > b.getSubjectName();
            }
        });
}

void DatabaseManager::SortSubjectsByCredits(bool ascending)
{
    sort(m_subjects.begin(), m_subjects.end(),
        [ascending](const Subject& a, const Subject& b)
        {
            if (ascending)
            {
                return a.getEctsCredits() < b.getEctsCredits();
            }
            else
            {
                return a.getEctsCredits() > b.getEctsCredits();
            }
        });
}

// Файлові операції
bool DatabaseManager::LoadFromFile(const string& studentsFile,
                                  const string& teachersFile,
                                  const string& subjectsFile)
{
    return LoadStudentsFromFile(studentsFile) &&
           LoadTeachersFromFile(teachersFile) &&
           LoadSubjectsFromFile(subjectsFile);
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

int DatabaseManager::GetStudentCount() const
{
    return m_students.size();
}

int DatabaseManager::GetTeacherCount() const
{
    return m_teachers.size();
}

int DatabaseManager::GetSubjectCount() const
{
    return m_subjects.size();
}

vector<Teacher> DatabaseManager::FindTeachersWithoutSubjects() const
{
    vector<Teacher> result;
    for (const auto& teacher : m_teachers)
    {
        bool hasSubject = false;
        for (const auto& subject : m_subjects)
        {
            if (subject.getTeacherId() == teacher.getTeacherID())
            {
                hasSubject = true;
                break;
            }
        }
        if (!hasSubject)
        {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::FindSubjectsWithoutTeacher() const
{
    vector<Subject> result;
    for (const auto& subject : m_subjects)
    {
        // Тут викликається const версія GetTeacher() - саме її ми додали
        if (subject.getTeacherId().empty() ||
            GetTeacher(subject.getTeacherId()) == nullptr)
        {
            result.push_back(subject);
        }
    }
    return result;
}

// Приватні файлові методи
bool DatabaseManager::LoadStudentsFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    m_students.clear();
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name, lastName, email, studentID, educationalProgram;

        getline(ss, name, ',');
        getline(ss, lastName, ',');
        getline(ss, email, ',');
        getline(ss, studentID, ',');
        getline(ss, educationalProgram, ',');

        try
        {
            Student student(name, lastName, email, studentID, educationalProgram);
            m_students.push_back(student);
        }
        catch (const exception& e)
        {
            cerr << "Помилка завантаження студента: " << e.what() << endl;
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
        return false;
    }

    m_teachers.clear();
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name, lastName, email, teacherID, department, degreeStr;

        getline(ss, name, ',');
        getline(ss, lastName, ',');
        getline(ss, email, ',');
        getline(ss, teacherID, ',');
        getline(ss, department, ',');
        getline(ss, degreeStr, ',');

        try
        {
            AcademicDegree degree;
            if (degreeStr == "BACHELOR")
            {
                degree = AcademicDegree::BACHELOR;
            }
            else if (degreeStr == "MASTER")
            {
                degree = AcademicDegree::MASTER;
            }
            else if (degreeStr == "DOCTOR")
            {
                degree = AcademicDegree::DOCTOR;
            }
            else
            {
                degree = AcademicDegree::BACHELOR;
            }

            Teacher teacher(name, lastName, email, teacherID, department, degree);
            m_teachers.push_back(teacher);
        }
        catch (const exception& e)
        {
            cerr << "Помилка завантаження викладача: " << e.what() << endl;
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
        return false;
    }

    m_subjects.clear();
    string line;
    int loadedCount = 0;
    int skippedCount = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string subjectId, subjectName, teacherId, creditsStr, semesterStr;

        getline(ss, subjectId, ',');
        getline(ss, subjectName, ',');
        getline(ss, creditsStr, ',');
        getline(ss, teacherId, ',');
        getline(ss, semesterStr, ',');

        if (subjectId.length() != 5 ||
            subjectId.substr(0, 2) != "SJ" ||
            !all_of(subjectId.begin() + 2, subjectId.end(), ::isdigit))
        {
            skippedCount++;
            cerr << "Пропущено предмет з некоректним ID: " << subjectId << endl;
            continue;
        }

        if (teacherId.length() != 5 ||
            teacherId.substr(0, 2) != "PR" ||
            !all_of(teacherId.begin() + 2, teacherId.end(), ::isdigit))
        {
            skippedCount++;
            cerr << "Пропущено предмет з некоректним ID викладача: "
                 << teacherId << endl;
            continue;
        }

        try
        {
            int credits = stoi(creditsStr);
            int semester = stoi(semesterStr);
            Subject subject(subjectId, subjectName, credits, teacherId, semester);
            m_subjects.push_back(subject);
            loadedCount++;
        }
        catch (const exception& e)
        {
            skippedCount++;
            cerr << "Помилка завантаження предмета: " << e.what() << endl;
        }
    }

    file.close();

    if (skippedCount > 0)
    {
        cout << "Завантажено " << loadedCount << " предметів. Пропущено "
             << skippedCount << " записів." << endl;
    }
    else
    {
        cout << "Успішно завантажено " << loadedCount << " предметів." << endl;
    }

    return loadedCount > 0;
}

bool DatabaseManager::SaveStudentsToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (const auto& student : m_students)
    {
        file << student.getName() << ","
             << student.getLastName() << ","
             << student.getEmail() << ","
             << student.getStudentID() << ","
             << student.getEducationalProgram() << endl;
    }

    file.close();
    cout << "Збережено " << m_students.size() << " студентів у файл: "
         << filename << endl;
    return true;
}

bool DatabaseManager::SaveTeachersToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (const auto& teacher : m_teachers)
    {
        string degreeStr;
        AcademicDegree degree = teacher.getAcademicDegree();

        if (degree == AcademicDegree::BACHELOR)
        {
            degreeStr = "BACHELOR";
        }
        else if (degree == AcademicDegree::MASTER)
        {
            degreeStr = "MASTER";
        }
        else if (degree == AcademicDegree::DOCTOR)
        {
            degreeStr = "DOCTOR";
        }
        else
        {
            degreeStr = "BACHELOR";
        }

        file << teacher.getName() << ","
             << teacher.getLastName() << ","
             << teacher.getEmail() << ","
             << teacher.getTeacherID() << ","
             << teacher.getDepartment() << ","
             << degreeStr << endl;
    }

    file.close();
    cout << "Збережено " << m_teachers.size() << " викладачів у файл: "
         << filename << endl;
    return true;
}

bool DatabaseManager::SaveSubjectsToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (const auto& subject : m_subjects)
    {
        file << subject.getSubjectId() << ","
             << subject.getSubjectName() << ","
             << subject.getEctsCredits() << ","
             << subject.getTeacherId() << ","
             << subject.getSemester() << endl;
    }

    file.close();
    cout << "Збережено " << m_subjects.size() << " предметів у файл: "
         << filename << endl;
    return true;
}
    // Призначення студентів на предмети
bool DatabaseManager::AssignStudentToSubject(const string& studentId, const string& subjectId)
{
    Student* student = GetStudent(studentId);
    if (!student)
    {
        throw invalid_argument("Студент не знайдений: " + studentId);
    }

    Subject* subject = GetSubject(subjectId);
    if (!subject)
    {
        throw invalid_argument("Предмет не знайдений: " + subjectId);
    }

    // Перевіряємо, чи не записаний вже студент на цей предмет
    if (IsStudentAssignedToSubject(studentId, subjectId))
    {
        throw invalid_argument("Студент вже записаний на цей предмет");
    }

    // Додаємо предмет до студента
    student->enrollSubject(subjectId);

    cout << "✅ Студента " << student->getFullName()
         << " успішно записано на предмет: " << subject->getSubjectName() << endl;
    return true;
}

bool DatabaseManager::RemoveStudentFromSubject(const string& studentId, const string& subjectId)
{
    Student* student = GetStudent(studentId);
    if (!student)
    {
        throw invalid_argument("Студент не знайдений: " + studentId);
    }

    Subject* subject = GetSubject(subjectId);
    if (!subject)
    {
        throw invalid_argument("Предмет не знайдений: " + subjectId);
    }

    // Перевіряємо, чи записаний студент на предмет
    if (!IsStudentAssignedToSubject(studentId, subjectId))
    {
        throw invalid_argument("Студент не записаний на цей предмет");
    }

    // Видаляємо предмет у студента
    student->dropSubject(subjectId);

    cout << "✅ Студента " << student->getFullName()
         << " видалено з предмету: " << subject->getSubjectName() << endl;
    return true;
}

vector<Subject> DatabaseManager::GetStudentSubjects(const string& studentId) const
{
    const Student* student = GetStudent(studentId);
    if (!student)
    {
        throw invalid_argument("Студент не знайдений: " + studentId);
    }

    // Отримуємо список ID предметів студента
    vector<string> subjectIds = student->getEnrolledSubjects();
    vector<Subject> subjects;

    // Знаходимо об'єкти Subject за ID
    for (const auto& subjectId : subjectIds)
    {
        const Subject* subject = GetSubject(subjectId);
        if (subject)
        {
            subjects.push_back(*subject);
        }
    }

    return subjects;
}

vector<Student> DatabaseManager::GetSubjectStudents(const string& subjectId) const
{
    vector<Student> result;
    const Subject* subject = GetSubject(subjectId);
    if (!subject)
    {
        throw invalid_argument("Предмет не знайдений: " + subjectId);
    }

    // Шукаємо всіх студентів, які мають цей предмет
    for (const auto& student : m_students)
    {
        if (IsStudentAssignedToSubject(student.getStudentID(), subjectId))
        {
            result.push_back(student);
        }
    }

    return result;
}

bool DatabaseManager::IsStudentAssignedToSubject(const string& studentId, const string& subjectId) const
{
    const Student* student = GetStudent(studentId);
    if (!student)
    {
        return false;
    }

    // Використовуємо метод isEnrolled з класу Student
    return student->isEnrolled(subjectId);
}


} // namespace University