#include "Teacher.h"
#include <sstream>
#include <cctype>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

namespace University {

// Статична ініціалізація
bool Teacher::ukrainianSupportInitialized = false;

//-----------------------------------------------------------------------------
// Приватні методи
//-----------------------------------------------------------------------------
bool Teacher::validateTeacherID(const string& id) const
{
    return !id.empty() && all_of(id.begin(), id.end(), [](char c)
    {
        return isalnum(c);
    });
}

void Teacher::initializeUkrainianSupport()
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

//-----------------------------------------------------------------------------
// Конструктори
//-----------------------------------------------------------------------------
Teacher::Teacher()
    : Person(), teacherID(""), department(""),
      academicDegree(AcademicDegree::BACHELOR), subjectId("")
{
    initializeUkrainianSupport();
    cout << "Конструктор Teacher за замовчуванням викликаний" << endl;
}

Teacher::Teacher(const string& name, const string& lastName,
                 const string& email, const string& teacherID,
                 const string& department, AcademicDegree degree)
    : Person(name, lastName, email), teacherID(teacherID),
      department(department), academicDegree(degree), subjectId("")
{
    initializeUkrainianSupport();

    if (!validateTeacherID(teacherID))
    {
        throw invalid_argument("Некоректний ID викладача: " + teacherID);
    }

    cout << "Конструктор Teacher з параметрами викликаний для: "
         << getFullName() << endl;
}

Teacher::Teacher(const Teacher& other)
    : Person(other), teacherID(other.teacherID),
      department(other.department),
      academicDegree(other.academicDegree),
      subjectId(other.subjectId)
{
    cout << "Копіювальний конструктор Teacher викликаний для: "
         << getFullName() << endl;
}

Teacher::Teacher(Teacher&& other) noexcept
    : Person(move(other)), teacherID(move(other.teacherID)),
      department(move(other.department)),
      academicDegree(move(other.academicDegree)),
      subjectId(move(other.subjectId))
{
    cout << "Переміщувальний конструктор Teacher викликаний для: "
         << getFullName() << endl;
}

Teacher::~Teacher()
{
    cout << "Об'єкт Teacher знищено: " << getName() << " "
         << getLastName() << " (" << teacherID << ")" << endl;
}

//-----------------------------------------------------------------------------
// Властивості
//-----------------------------------------------------------------------------
string Teacher::getTeacherID() const { return teacherID; }
string Teacher::getDepartment() const { return department; }
AcademicDegree Teacher::getAcademicDegree() const { return academicDegree; }
string Teacher::getSubjectId() const { return subjectId; }

string Teacher::getAcademicDegreeString() const
{
    switch (academicDegree)
    {
        case AcademicDegree::BACHELOR: return "Бакалавр";
        case AcademicDegree::MASTER:   return "Магістр";
        case AcademicDegree::DOCTOR:   return "Доктор наук";
        default:                       return "Невідомий ступінь";
    }
}

void Teacher::setTeacherID(const string& id)
{
    if (!validateTeacherID(id))
    {
        throw invalid_argument("Некоректний ID викладача: " + id);
    }
    teacherID = id;
}

void Teacher::setDepartment(const string& dep)
{
    if (dep.empty())
    {
        throw invalid_argument("Кафедра не може бути порожньою");
    }
    department = dep;
}

void Teacher::setAcademicDegree(AcademicDegree deg) { academicDegree = deg; }
void Teacher::setSubjectId(const string& subId) { subjectId = subId; }

//-----------------------------------------------------------------------------
// Методи
//-----------------------------------------------------------------------------
bool Teacher::assignToSubject(const string& subId)
{
    if (subId.empty()) return false;
    subjectId = subId;
    return true;
}

bool Teacher::removeFromSubject()
{
    if (subjectId.empty()) return false;
    subjectId.clear();
    return true;
}

bool Teacher::hasAssignedSubject() const { return !subjectId.empty(); }

void Teacher::promote(AcademicDegree newDegree) { setAcademicDegree(newDegree); }
void Teacher::changeDepartment(const string& newDep) { setDepartment(newDep); }

bool Teacher::canTeachSubject(const string& subId) const
{
    return !hasAssignedSubject() || subjectId == subId;
}

string Teacher::getTeachingStatus() const
{
    return subjectId.empty() ? "Вільний"
                             : "Викладає предмет " + subjectId;
}

double Teacher::calculateWorkload() const
{
    return hasAssignedSubject() ? DEFAULT_WORKLOAD_HOURS : 0.0;
}

bool Teacher::isAvailableForNewSubject() const { return !hasAssignedSubject(); }

void Teacher::updateAcademicProfile(AcademicDegree deg, const string& dep)
{
    setAcademicDegree(deg);
    setDepartment(dep);
}

//-----------------------------------------------------------------------------
// Перевизначені методи
//-----------------------------------------------------------------------------
void Teacher::print() const
{
    cout << "Викладач: " << getFullName() << endl;
    cout << "ID: " << teacherID << endl;
    cout << "Кафедра: " << department << endl;
    cout << "Науковий ступінь: " << getAcademicDegreeString() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Статус: " << getTeachingStatus() << endl;
}

string Teacher::toString() const
{
    stringstream ss;
    ss << "Teacher{name: " << getName()
       << ", lastName: " << getLastName()
       << ", teacherID: " << teacherID
       << ", department: " << department
       << ", degree: " << getAcademicDegreeString()
       << ", subject: " << subjectId << "}";
    return ss.str();
}

bool Teacher::isValid() const
{
    return Person::isValid() && !teacherID.empty() && !department.empty();
}

//-----------------------------------------------------------------------------
// Оператори
//-----------------------------------------------------------------------------
Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        teacherID = other.teacherID;
        department = other.department;
        academicDegree = other.academicDegree;
        subjectId = other.subjectId;
    }
    return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(move(other));
        teacherID = move(other.teacherID);
        department = move(other.department);
        academicDegree = move(other.academicDegree);
        subjectId = move(other.subjectId);
    }
    return *this;
}

bool Teacher::operator==(const Teacher& other) const
{
    return Person::operator==(other) && teacherID == other.teacherID;
}

bool Teacher::operator!=(const Teacher& other) const { return !(*this == other); }

} // namespace University
