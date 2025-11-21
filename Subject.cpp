#include "Subject.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

Subject::Subject() : subjectId(""), subjectName(""), ectsCredits(0), teacherId(""), semester(1) {}

Subject::Subject(const string& subjectId, const string& subjectName,
                 int ectsCredits, const string& teacherId, int semester)
    : subjectId(subjectId), subjectName(subjectName), ectsCredits(ectsCredits),
      teacherId(teacherId), semester(semester) {
    if (!validateSubjectID(subjectId)) {
        throw invalid_argument("Некоректний ID предмета: " + subjectId);
    }
    if (!validateCredits(ectsCredits)) {
        throw invalid_argument("Некоректна кількість кредитів: " + to_string(ectsCredits));
    }
    if (!validateSemester(semester)) {
        throw invalid_argument("Некоректний семестр: " + to_string(semester));
    }
}

Subject::Subject(const Subject& other)
    : subjectId(other.subjectId), subjectName(other.subjectName),
      ectsCredits(other.ectsCredits), teacherId(other.teacherId),
      semester(other.semester) {}

Subject::Subject(Subject&& other) noexcept
    : subjectId(move(other.subjectId)), subjectName(move(other.subjectName)),
      ectsCredits(other.ectsCredits), teacherId(move(other.teacherId)),
      semester(other.semester) {}

Subject::~Subject() {
    cout << "Предмет знищений: " << subjectId << " - " << subjectName << endl;
}

void Subject::setSubjectId(const string& subjectId) {
    if (!validateSubjectID(subjectId)) {
        throw invalid_argument("Некоректний ID предмета: " + subjectId);
    }
    this->subjectId = subjectId;
}

void Subject::setSubjectName(const string& subjectName) {
    if (subjectName.empty()) {
        throw invalid_argument("Назва предмета не може бути порожньою");
    }
    this->subjectName = subjectName;
}

void Subject::setEctsCredits(int ectsCredits) {
    if (!validateCredits(ectsCredits)) {
        throw invalid_argument("Некоректна кількість кредитів: " + to_string(ectsCredits));
    }
    this->ectsCredits = ectsCredits;
}

void Subject::setTeacherId(const string& teacherId) {
    this->teacherId = teacherId;
}

void Subject::setSemester(int semester) {
    if (!validateSemester(semester)) {
        throw invalid_argument("Некоректний семестр: " + to_string(semester));
    }
    this->semester = semester;
}

bool Subject::assignTeacher(const string& teacherId) {
    if (teacherId.empty()) {
        throw invalid_argument("ID викладача не може бути порожнім");
    }
    if (hasAssignedTeacher()) {
        throw invalid_argument("Предмет вже має призначеного викладача: " + this->teacherId);
    }
    this->teacherId = teacherId;
    return true;
}

bool Subject::removeTeacher() {
    if (!hasAssignedTeacher()) {
        throw invalid_argument("Предмет не має призначеного викладача");
    }
    teacherId.clear();
    return true;
}

bool Subject::hasAssignedTeacher() const {
    return !teacherId.empty();
}

void Subject::updateCredits(int newCredits) {
    if (!validateCredits(newCredits)) {
        throw invalid_argument("Некоректна кількість кредитів: " + to_string(newCredits));
    }
    ectsCredits = newCredits;
}

void Subject::changeSemester(int newSemester) {
    if (!validateSemester(newSemester)) {
        throw invalid_argument("Некоректний семестр: " + to_string(newSemester));
    }
    semester = newSemester;
}

bool Subject::isValid() const {
    return !subjectId.empty() && !subjectName.empty() &&
           validateCredits(ectsCredits) && validateSemester(semester);
}

string Subject::getSubjectInfo() const {
    return subjectName + " (" + subjectId + ") - " + to_string(ectsCredits) + " кредитів, семестр " + to_string(semester);
}

bool Subject::isAvailableForEnrollment() const {
    return hasAssignedTeacher() && semester >= 1 && semester <= 8;
}

bool Subject::matchesSearchCriteria(const string& criteria) const {
    string lowerCriteria = criteria;
    transform(lowerCriteria.begin(), lowerCriteria.end(), lowerCriteria.begin(), ::tolower);

    string lowerName = subjectName;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    string lowerId = subjectId;
    transform(lowerId.begin(), lowerId.end(), lowerId.begin(), ::tolower);

    return lowerName.find(lowerCriteria) != string::npos ||
           lowerId.find(lowerCriteria) != string::npos;
}

bool Subject::canBeAssignedToTeacher(const string& teacherId) const {
    return !hasAssignedTeacher() || this->teacherId == teacherId;
}

void Subject::print() const {
    cout << "Предмет: " << endl;
    cout << "  ID: " << subjectId << endl;
    cout << "  Назва: " << subjectName << endl;
    cout << "  Кредити ECTS: " << ectsCredits << endl;
    cout << "  Семестр: " << semester << endl;
    cout << "  Викладач: " << (hasAssignedTeacher() ? teacherId : "Не призначено") << endl;
    cout << "  Доступний для запису: " << (isAvailableForEnrollment() ? "Так" : "Ні") << endl;
}

string Subject::toString() const {
    return "Предмет[" + subjectId + "] " + subjectName + " - " + to_string(ectsCredits) + " кредитів";
}

Subject& Subject::operator=(const Subject& other) {
    if (this != &other) {
        subjectId = other.subjectId;
        subjectName = other.subjectName;
        ectsCredits = other.ectsCredits;
        teacherId = other.teacherId;
        semester = other.semester;
    }
    return *this;
}

Subject& Subject::operator=(Subject&& other) noexcept {
    if (this != &other) {
        subjectId = move(other.subjectId);
        subjectName = move(other.subjectName);
        ectsCredits = other.ectsCredits;
        teacherId = move(other.teacherId);
        semester = other.semester;
    }
    return *this;
}

bool Subject::operator==(const Subject& other) const {
    return subjectId == other.subjectId;
}

bool Subject::validateSubjectID(const string& id) const {
    if (id.empty()) return false;
    return all_of(id.begin(), id.end(), [](char c) {
        return isalnum(c);
    });
}

bool Subject::validateCredits(int credits) const {
    return credits >= 1 && credits <= 10;
}

bool Subject::validateSemester(int semester) const {
    return semester >= 1 && semester <= 8;
}