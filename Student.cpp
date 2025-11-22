#include "Student.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cctype>

#ifdef _WIN32
    #include <windows.h>
#endif



namespace University {
    using namespace std;

// Статична ініціалізація
bool Student::ukrainianSupportInitialized = false;

//-----------------------------------------------------------------------------
// Приватні методи
//-----------------------------------------------------------------------------
void Student::initializeUkrainianSupport()
{
    if (ukrainianSupportInitialized)
    {
        return;
    }

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try
    {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }
    catch (...)
    {
        try
        {
            setlocale(LC_ALL, "C.UTF-8");
        }
        catch (...)
        {
            setlocale(LC_ALL, "");
        }
    }

    ukrainianSupportInitialized = true;
}

bool Student::validateStudentID(const string& id) const
{
    if (id.empty())
    {
        return false;
    }

    return all_of(id.begin(), id.end(), [](char c)
    {
        return isalnum(c);
    });
}

//-----------------------------------------------------------------------------
// Конструктори
//-----------------------------------------------------------------------------
Student::Student()
    : Person(), studentID(""), educationalProgram("")
{
    initializeUkrainianSupport();
}

Student::Student(const string& name, const string& lastName,
                 const string& email, const string& studentID,
                 const string& educationalProgram)
    : Person(name, lastName, email), studentID(studentID),
      educationalProgram(educationalProgram)
{
    initializeUkrainianSupport();

    if (!validateStudentID(studentID))
    {
        throw invalid_argument("Некоректний ID студента: " + studentID);
    }
}

Student::~Student()
{
    cout << "Студент знищений: " << studentID << " - " << getFullName() << endl;
}

//-----------------------------------------------------------------------------
// Властивості
//-----------------------------------------------------------------------------
string Student::getStudentID() const
{
    return studentID;
}

string Student::getEducationalProgram() const
{
    return educationalProgram;
}

vector<string> Student::getEnrolledSubjects() const
{
    return enrolledSubjects;
}

void Student::setStudentID(const string& studentID)
{
    if (!validateStudentID(studentID))
    {
        throw invalid_argument("Некоректний ID студента: " + studentID);
    }
    this->studentID = studentID;
}

void Student::setEducationalProgram(const string& educationalProgram)
{
    if (educationalProgram.empty())
    {
        throw invalid_argument("Освітня програма не може бути порожньою");
    }
    this->educationalProgram = educationalProgram;
}

//-----------------------------------------------------------------------------
// Методи
//-----------------------------------------------------------------------------
void Student::enrollSubject(const string& subjectId)
{
    if (subjectId.empty())
    {
        throw invalid_argument("ID предмета не може бути порожнім");
    }

    if (isEnrolled(subjectId))
    {
        throw invalid_argument("Студент вже записаний на предмет: " + subjectId);
    }

    if (!canEnrollMoreSubjects())
    {
        throw invalid_argument("Досягнуто максимальну кількість предметів");
    }

    enrolledSubjects.push_back(subjectId);
}

void Student::dropSubject(const string& subjectId)
{
    if (subjectId.empty())
    {
        throw invalid_argument("ID предмета не може бути порожнім");
    }

    auto it = find(enrolledSubjects.begin(), enrolledSubjects.end(), subjectId);
    if (it == enrolledSubjects.end())
    {
        throw invalid_argument("Студент не записаний на предмет: " + subjectId);
    }

    enrolledSubjects.erase(it);
}

bool Student::isEnrolled(const string& subjectId) const
{
    return find(enrolledSubjects.begin(), enrolledSubjects.end(), subjectId) != enrolledSubjects.end();
}

void Student::listSubjects() const
{
    cout << "Предмети студента " << getFullName() << ":" << endl;
    for (const auto& subject : enrolledSubjects)
    {
        cout << "  - " << subject << endl;
    }
}

void Student::clearSubjects()
{
    enrolledSubjects.clear();
}

int Student::getEnrolledSubjectsCount() const
{
    return enrolledSubjects.size();
}

void Student::changeEducationalProgram(const string& newEducationalProgram)
{
    if (newEducationalProgram.empty())
    {
        throw invalid_argument("Нова освітня програма не може бути порожньою");
    }
    educationalProgram = newEducationalProgram;
    clearSubjects();
}

double Student::calculateWorkload() const
{
    return enrolledSubjects.size() * 1.0;
}

bool Student::canEnrollMoreSubjects(int maxSubjects) const
{
    return enrolledSubjects.size() < maxSubjects;
}

bool Student::hasSubject(const string& subjectId) const
{
    return isEnrolled(subjectId);
}

//-----------------------------------------------------------------------------
// Перевизначені методи
//-----------------------------------------------------------------------------
void Student::print() const
{
    cout << "Студент: " << endl;
    cout << "  ID: " << studentID << endl;
    cout << "  Ім'я: " << getFullName() << endl;
    cout << "  Email: " << getEmail() << endl;
    cout << "  Освітня програма: " << educationalProgram << endl;
    cout << "  Кількість предметів: " << enrolledSubjects.size() << endl;
}

string Student::toString() const
{
    return "Студент[" + studentID + "] " + getFullName() + " - " + educationalProgram;
}

bool Student::isValid() const
{
    return Person::isValid() && !studentID.empty() && !educationalProgram.empty();
}

//-----------------------------------------------------------------------------
// Оператори
//-----------------------------------------------------------------------------
bool Student::operator==(const Student& other) const
{
    return studentID == other.studentID;
}

} // namespace University