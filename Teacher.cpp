/// @file     Teacher.cpp
/// @brief    Реалізація класу викладача
/// @author   Student Name
/// @date     2024
/// @namespace University

#include "Teacher.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

namespace University {

bool Teacher::ukrainianSupportInitialized = false;
const double Teacher::DEFAULT_WORKLOAD_HOURS = 180.0;

void Teacher::initializeUkrainianSupport()
{
    if (ukrainianSupportInitialized) {
        return;
    }

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }
    catch (...) {
        try {
            setlocale(LC_ALL, "C.UTF-8");
        }
        catch (...) {
            setlocale(LC_ALL, "");
        }
    }

    ukrainianSupportInitialized = true;
}

bool Teacher::validateTeacherID(const string& id) const
{
    return !id.empty() && all_of(id.begin(), id.end(), [](char c) {
        return isalnum(c);
    });
}

Teacher::Teacher() : Person(), teacherID(""), department(""),
                     academicDegree(AcademicDegree::BACHELOR)
{
    initializeUkrainianSupport();
}

Teacher::Teacher(const string& name, const string& lastName,
                 const string& email, const string& teacherID,
                 const string& department, AcademicDegree degree)
    : Person(name, lastName, email), teacherID(teacherID),
      department(department), academicDegree(degree)
{
    initializeUkrainianSupport();
    if (!validateTeacherID(teacherID)) {
        throw invalid_argument("Некоректний ID викладача: " + teacherID);
    }
}

Teacher::Teacher(const Teacher& other)
    : Person(other), teacherID(other.teacherID),
      department(other.department), academicDegree(other.academicDegree)
{
}

Teacher::Teacher(Teacher&& other) noexcept
    : Person(move(other)), teacherID(move(other.teacherID)),
      department(move(other.department)), academicDegree(move(other.academicDegree))
{
}

Teacher::~Teacher()
{
    cout << "Об'єкт Teacher знищено: " << getName() << " "
         << getLastName() << " (" << teacherID << ")" << endl;
}

[[nodiscard]] string Teacher::getTeacherID() const
{
    return teacherID;
}

[[nodiscard]] string Teacher::getDepartment() const
{
    return department;
}

[[nodiscard]] AcademicDegree Teacher::getAcademicDegree() const
{
    return academicDegree;
}

[[nodiscard]] string Teacher::getAcademicDegreeString() const
{
    switch (academicDegree) {
        case AcademicDegree::BACHELOR:
            return "Бакалавр";
        case AcademicDegree::MASTER:
            return "Магістр";
        case AcademicDegree::DOCTOR:
            return "Доктор наук";
        default:
            return "Невідомий ступінь";
    }
}

void Teacher::setTeacherID(const string& id)
{
    if (!validateTeacherID(id)) {
        throw invalid_argument("Некоректний ID викладача: " + id);
    }
    teacherID = id;
}

void Teacher::setDepartment(const string& dep)
{
    if (dep.empty()) {
        throw invalid_argument("Кафедра не може бути порожньою");
    }
    department = dep;
}

void Teacher::setAcademicDegree(AcademicDegree deg)
{
    academicDegree = deg;
}

void Teacher::promote(AcademicDegree newDegree)
{
    setAcademicDegree(newDegree);
}

void Teacher::changeDepartment(const string& newDep)
{
    setDepartment(newDep);
}

[[nodiscard]] string Teacher::getTeachingStatus() const
{
    return "Активний";
}

[[nodiscard]] double Teacher::calculateWorkload() const
{
    return DEFAULT_WORKLOAD_HOURS;
}

[[nodiscard]] bool Teacher::isAvailableForNewSubject() const
{
    return calculateWorkload() < 200.0;
}

void Teacher::updateAcademicProfile(AcademicDegree deg, const string& dep)
{
    setAcademicDegree(deg);
    setDepartment(dep);
}

void Teacher::print() const
{
    cout << "Викладач: " << getFullName() << endl;
    cout << "ID: " << teacherID << endl;
    cout << "Кафедра: " << department << endl;
    cout << "Науковий ступінь: " << getAcademicDegreeString() << endl;
    cout << "Статус: " << getTeachingStatus() << endl;
    cout << "Навантаження: " << calculateWorkload() << " годин" << endl;
}

[[nodiscard]] string Teacher::toString() const
{
    stringstream ss;
    ss << "Teacher{name: " << getName() << ", lastName: " << getLastName()
       << ", teacherID: " << teacherID << ", department: " << department
       << ", degree: " << getAcademicDegreeString() << ", status: "
       << getTeachingStatus() << ", workload: " << calculateWorkload() << "}";
    return ss.str();
}

[[nodiscard]] bool Teacher::isValid() const
{
    return Person::isValid() && !teacherID.empty() && !department.empty();
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other) {
        Person::operator=(other);
        teacherID = other.teacherID;
        department = other.department;
        academicDegree = other.academicDegree;
    }
    return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
    if (this != &other) {
        Person::operator=(move(other));
        teacherID = move(other.teacherID);
        department = move(other.department);
        academicDegree = move(other.academicDegree);
    }
    return *this;
}

bool Teacher::operator==(const Teacher& other) const
{
    return Person::operator==(other) && teacherID == other.teacherID;
}

bool Teacher::operator!=(const Teacher& other) const
{
    return !(*this == other);
}

} // namespace University