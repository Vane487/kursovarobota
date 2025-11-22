#include "Subject.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

namespace University {

//-----------------------------------------------------------------------------
// Конструктори
//-----------------------------------------------------------------------------
Subject::Subject()
    : subjectId(""), subjectName(""), ectsCredits(0),
      teacherId(""), semester(1)
{
}

Subject::Subject(const string& subjectId, const string& subjectName,
                 int ectsCredits, const string& teacherId, int semester)
    : subjectId(subjectId), subjectName(subjectName),
      ectsCredits(ectsCredits), teacherId(teacherId), semester(semester)
{
    if (!validateSubjectID(subjectId))
    {
        throw invalid_argument("Некоректний ID предмета: " + subjectId);
    }

    if (!validateCredits(ectsCredits))
    {
        throw invalid_argument("Некоректна кількість кредитів: " +
                              to_string(ectsCredits));
    }

    if (!validateSemester(semester))
    {
        throw invalid_argument("Некоректний семестр: " + to_string(semester));
    }
}

Subject::~Subject()
{
    cout << "Предмет знищений: " << subjectId << " - " << subjectName << endl;
}

//-----------------------------------------------------------------------------
// Властивості
//-----------------------------------------------------------------------------
string Subject::getSubjectId() const { return subjectId; }
string Subject::getSubjectName() const { return subjectName; }
int Subject::getEctsCredits() const { return ectsCredits; }
string Subject::getTeacherId() const { return teacherId; }
int Subject::getSemester() const { return semester; }

void Subject::setSubjectId(const string& id)
{
    if (!validateSubjectID(id))
    {
        throw invalid_argument("Некоректний ID предмета: " + id);
    }
    subjectId = id;
}

void Subject::setSubjectName(const string& name)
{
    if (name.empty())
    {
        throw invalid_argument("Назва предмета не може бути порожньою");
    }
    subjectName = name;
}

void Subject::setEctsCredits(int credits)
{
    if (!validateCredits(credits))
    {
        throw invalid_argument("Некоректна кількість кредитів: " +
                              to_string(credits));
    }
    ectsCredits = credits;
}

void Subject::setTeacherId(const string& teacherId)
{
    this->teacherId = teacherId;
}

void Subject::setSemester(int sem)
{
    if (!validateSemester(sem))
    {
        throw invalid_argument("Некоректний семестр: " + to_string(sem));
    }
    semester = sem;
}

//-----------------------------------------------------------------------------
// Методи
//-----------------------------------------------------------------------------
bool Subject::assignTeacher(const string& teacherId)
{
    if (teacherId.empty())
    {
        throw invalid_argument("ID викладача не може бути порожнім");
    }

    if (hasAssignedTeacher())
    {
        throw invalid_argument("Предмет вже має призначеного викладача: " +
                              this->teacherId);
    }

    this->teacherId = teacherId;
    return true;
}

bool Subject::removeTeacher()
{
    if (!hasAssignedTeacher())
    {
        throw invalid_argument("Предмет не має призначеного викладача");
    }

    teacherId.clear();
    return true;
}

bool Subject::hasAssignedTeacher() const
{
    return !teacherId.empty();
}

void Subject::updateCredits(int newCredits)
{
    if (!validateCredits(newCredits))
    {
        throw invalid_argument("Некоректна кількість кредитів: " +
                              to_string(newCredits));
    }
    ectsCredits = newCredits;
}

void Subject::changeSemester(int newSemester)
{
    if (!validateSemester(newSemester))
    {
        throw invalid_argument("Некоректний семестр: " + to_string(newSemester));
    }
    semester = newSemester;
}

bool Subject::isValid() const
{
    return !subjectId.empty() && !subjectName.empty() &&
           validateCredits(ectsCredits) && validateSemester(semester);
}

string Subject::getSubjectInfo() const
{
    return subjectName + " (" + subjectId + ") - " +
           to_string(ectsCredits) + " кредитів, семестр " +
           to_string(semester);
}

bool Subject::matchesSearchCriteria(const string& criteria) const
{
    string lowerCriteria = criteria;
    transform(lowerCriteria.begin(), lowerCriteria.end(),
              lowerCriteria.begin(), ::tolower);

    string lowerName = subjectName;
    transform(lowerName.begin(), lowerName.end(),
              lowerName.begin(), ::tolower);

    string lowerId = subjectId;
    transform(lowerId.begin(), lowerId.end(),
              lowerId.begin(), ::tolower);

    return lowerName.find(lowerCriteria) != string::npos ||
           lowerId.find(lowerCriteria) != string::npos;
}

bool Subject::canBeAssignedToTeacher(const string& teacherId) const
{
    return !hasAssignedTeacher() || this->teacherId == teacherId;
}

//-----------------------------------------------------------------------------
// Перевизначені методи
//-----------------------------------------------------------------------------
void Subject::print() const
{
    cout << "Предмет: " << endl;
    cout << "  ID: " << subjectId << endl;
    cout << "  Назва: " << subjectName << endl;
    cout << "  Кредити ECTS: " << ectsCredits << endl;
    cout << "  Семестр: " << semester << endl;
    cout << "  Викладач: " << (hasAssignedTeacher() ? teacherId : "Не призначено") << endl;
}

string Subject::toString() const
{
    return "Предмет[" + subjectId + "] " + subjectName + " - " +
           to_string(ectsCredits) + " кредитів";
}

//-----------------------------------------------------------------------------
// Оператори
//-----------------------------------------------------------------------------
bool Subject::operator==(const Subject& other) const
{
    return subjectId == other.subjectId;
}

//-----------------------------------------------------------------------------
// Приватні методи
//-----------------------------------------------------------------------------
bool Subject::validateSubjectID(const string& id) const
{
    if (id.empty()) return false;

    return all_of(id.begin(), id.end(), [](char c)
    {
        return isalnum(c);
    });
}

bool Subject::validateCredits(int credits) const
{
    return credits >= MIN_CREDITS && credits <= MAX_CREDITS;
}

bool Subject::validateSemester(int semester) const
{
    return semester >= MIN_SEMESTER && semester <= MAX_SEMESTER;
}

} // namespace University