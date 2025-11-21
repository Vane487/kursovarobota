#include "Teacher.h"
#include <sstream>
#include <cctype>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

void Teacher::setupUkrainianSupport() const {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    } catch (...) {
        try {
            setlocale(LC_ALL, "C.UTF-8");
        } catch (...) {
            setlocale(LC_ALL, "");
        }
    }
}

Teacher::Teacher() : Person(), teacherID(""), department(""), academicDegree(""), subjectId("") {
    setupUkrainianSupport();
    cout << "Конструктор Teacher за замовчуванням викликаний" << endl;
}

Teacher::Teacher(const string& name, const string& lastName,
                 const string& email,
                 const string& teacherID, const string& department,
                 const string& academicDegree)
    : Person(name, lastName, email),
      teacherID(teacherID), department(department), academicDegree(academicDegree), subjectId("") {
    setupUkrainianSupport();
    if (!validateTeacherID(teacherID)) {
        throw invalid_argument("Некоректний ID викладача: " + teacherID);
    }
    cout << "Конструктор Teacher з параметрами викликаний для: " << getFullName() << endl;
}

Teacher::Teacher(const Teacher& other)
    : Person(other),
      teacherID(other.teacherID),
      department(other.department),
      academicDegree(other.academicDegree),
      subjectId(other.subjectId) {
    setupUkrainianSupport();
    cout << "Копіювальний конструктор Teacher викликаний для: " << getFullName() << endl;
}

Teacher::Teacher(Teacher&& other) noexcept
    : Person(move(other)),
      teacherID(move(other.teacherID)),
      department(move(other.department)),
      academicDegree(move(other.academicDegree)),
      subjectId(move(other.subjectId)) {
    setupUkrainianSupport();
    cout << "Переміщувальний конструктор Teacher викликаний для: " << getFullName() << endl;
}

Teacher::~Teacher() {
    setupUkrainianSupport();
    cout << "Об'єкт Teacher знищено: " << getName() << " " << getLastName() << " (" << teacherID << ")" << endl;
}

void Teacher::setTeacherID(const string& teacherID) {
    if (!validateTeacherID(teacherID)) {
        throw invalid_argument("Некоректний ID викладача: " + teacherID);
    }
    this->teacherID = teacherID;
}

void Teacher::setDepartment(const string& department) {
    if (department.empty()) {
        throw invalid_argument("Кафедра не може бути порожньою");
    }
    this->department = department;
}

void Teacher::setAcademicDegree(const string& academicDegree) {
    if (academicDegree.empty()) {
        throw invalid_argument("Науковий ступінь не може бути порожнім");
    }
    this->academicDegree = academicDegree;
}

void Teacher::setSubjectId(const string& subjectId) {
    this->subjectId = subjectId;
}

bool Teacher::assignToSubject(const string& subjectId) {
    if (subjectId.empty()) return false;
    this->subjectId = subjectId;
    return true;
}

bool Teacher::removeFromSubject() {
    if (subjectId.empty()) return false;
    subjectId = "";
    return true;
}

bool Teacher::hasAssignedSubject() const {
    return !subjectId.empty();
}

void Teacher::promote(const string& newDegree) {
    setAcademicDegree(newDegree);
}

void Teacher::changeDepartment(const string& newDepartment) {
    setDepartment(newDepartment);
}

bool Teacher::canTeachSubject(const string& subjectId) const {
    return !hasAssignedSubject() || this->subjectId == subjectId;
}

string Teacher::getTeachingStatus() const {
    if (subjectId.empty()) return "Вільний";
    return "Викладає предмет " + subjectId;
}

double Teacher::calculateWorkload() const {
    return hasAssignedSubject() ? 120.0 : 0.0;
}

bool Teacher::isAvailableForNewSubject() const {
    return !hasAssignedSubject();
}

void Teacher::updateAcademicProfile(const string& newDegree, const string& newDepartment) {
    setAcademicDegree(newDegree);
    setDepartment(newDepartment);
}

void Teacher::print() const {
    setupUkrainianSupport();
    cout << "Викладач: " << getFullName() << endl;
    cout << "ID: " << teacherID << endl;
    cout << "Кафедра: " << department << endl;
    cout << "Науковий ступінь: " << academicDegree << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Статус: " << getTeachingStatus() << endl;
}

string Teacher::toString() const {
    stringstream ss;
    ss << "Teacher{name: " << getName() << ", lastName: " << getLastName()
       << ", teacherID: " << teacherID << ", department: " << department
       << ", degree: " << academicDegree << ", subject: " << subjectId << "}";
    return ss.str();
}

bool Teacher::isValid() const {
    return Person::isValid() && !teacherID.empty() && !department.empty() && !academicDegree.empty();
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Person::operator=(other);
        teacherID = other.teacherID;
        department = other.department;
        academicDegree = other.academicDegree;
        subjectId = other.subjectId;
    }
    return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept {
    if (this != &other) {
        Person::operator=(move(other));
        teacherID = move(other.teacherID);
        department = move(other.department);
        academicDegree = move(other.academicDegree);
        subjectId = move(other.subjectId);
    }
    return *this;
}

bool Teacher::operator==(const Teacher& other) const {
    return Person::operator==(other) && teacherID == other.teacherID;
}

bool Teacher::operator!=(const Teacher& other) const {
    return !(*this == other);
}

bool Teacher::validateTeacherID(const string& id) const {
    if (id.empty()) return false;
    return all_of(id.begin(), id.end(), [](char c) {
        return isalnum(c);
    });
}