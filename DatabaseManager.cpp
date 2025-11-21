#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

DatabaseManager::DatabaseManager() {
    cout << "DatabaseManager конструктор за замовчуванням викликаний" << endl;
}

DatabaseManager::DatabaseManager(const DatabaseManager& other)
    : students(other.students), teachers(other.teachers), subjects(other.subjects) {
    cout << "DatabaseManager копіювальний конструктор викликаний" << endl;
}

DatabaseManager::DatabaseManager(DatabaseManager&& other) noexcept
    : students(move(other.students)), teachers(move(other.teachers)), subjects(move(other.subjects)) {
    cout << "DatabaseManager переміщувальний конструктор викликаний" << endl;
}

DatabaseManager::~DatabaseManager() {
    cout << "DatabaseManager деструктор викликаний" << endl;
    cout << "Знищено: " << students.size() << " студентів, "
         << teachers.size() << " викладачів, "
         << subjects.size() << " предметів" << endl;
}

void DatabaseManager::addStudent(const Student& student) {
    if (!student.isValid()) {
        throw invalid_argument("Некоректні дані студента");
    }
    if (getStudent(student.getStudentID()) != nullptr) {
        throw invalid_argument("Студент з таким ID вже існує: " + student.getStudentID());
    }
    students.push_back(student);
}

bool DatabaseManager::editStudent(const string& studentId, const Student& newData) {
    if (!newData.isValid()) {
        throw invalid_argument("Некоректні нові дані студента");
    }
    for (auto& student : students) {
        if (student.getStudentID() == studentId) {
            student = newData;
            return true;
        }
    }
    return false;
}

bool DatabaseManager::deleteStudent(const string& studentId) {
    auto it = remove_if(students.begin(), students.end(),
        [&](const Student& s) { return s.getStudentID() == studentId; });
    if (it != students.end()) {
        students.erase(it, students.end());
        return true;
    }
    return false;
}

Student* DatabaseManager::getStudent(const string& studentId) {
    for (auto& student : students) {
        if (student.getStudentID() == studentId) {
            return &student;
        }
    }
    return nullptr;
}

vector<Student> DatabaseManager::getAllStudents() const {
    return students;
}

vector<Student> DatabaseManager::searchStudentsByName(const string& name) const {
    vector<Student> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& student : students) {
        string fullName = student.getFullName();
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        if (fullName.find(lowerName) != string::npos) {
            result.push_back(student);
        }
    }
    return result;
}

vector<Student> DatabaseManager::searchStudentsByProgram(const string& program) const {
    vector<Student> result;
    string lowerProgram = program;
    transform(lowerProgram.begin(), lowerProgram.end(), lowerProgram.begin(), ::tolower);

    for (const auto& student : students) {
        string studentProgram = student.getEducationalProgram();
        transform(studentProgram.begin(), studentProgram.end(), studentProgram.begin(), ::tolower);
        if (studentProgram.find(lowerProgram) != string::npos) {
            result.push_back(student);
        }
    }
    return result;
}

void DatabaseManager::sortStudentsByName(bool ascending) {
    sort(students.begin(), students.end(),
        [ascending](const Student& a, const Student& b) {
            if (ascending) {
                return a.getFullName() < b.getFullName();
            } else {
                return a.getFullName() > b.getFullName();
            }
        });
}

void DatabaseManager::sortStudentsById(bool ascending) {
    sort(students.begin(), students.end(),
        [ascending](const Student& a, const Student& b) {
            if (ascending) {
                return a.getStudentID() < b.getStudentID();
            } else {
                return a.getStudentID() > b.getStudentID();
            }
        });
}

void DatabaseManager::addTeacher(const Teacher& teacher) {
    if (!teacher.isValid()) {
        throw invalid_argument("Некоректні дані викладача");
    }
    if (getTeacher(teacher.getTeacherID()) != nullptr) {
        throw invalid_argument("Викладач з таким ID вже існує: " + teacher.getTeacherID());
    }
    teachers.push_back(teacher);
}

bool DatabaseManager::editTeacher(const string& teacherId, const Teacher& newData) {
    if (!newData.isValid()) {
        throw invalid_argument("Некоректні нові дані викладача");
    }
    for (auto& teacher : teachers) {
        if (teacher.getTeacherID() == teacherId) {
            teacher = newData;
            return true;
        }
    }
    return false;
}

bool DatabaseManager::deleteTeacher(const string& teacherId) {
    // Перевіряємо, чи викладач не викладає якийсь предмет
    for (const auto& subject : subjects) {
        if (subject.getTeacherId() == teacherId) {
            throw invalid_argument("Не можна видалити викладача, який викладає предмет: " + subject.getSubjectName());
        }
    }

    auto it = remove_if(teachers.begin(), teachers.end(),
        [&](const Teacher& t) { return t.getTeacherID() == teacherId; });
    if (it != teachers.end()) {
        teachers.erase(it, teachers.end());
        return true;
    }
    return false;
}

Teacher* DatabaseManager::getTeacher(const string& teacherId) {
    for (auto& teacher : teachers) {
        if (teacher.getTeacherID() == teacherId) {
            return &teacher;
        }
    }
    return nullptr;
}

vector<Teacher> DatabaseManager::getAllTeachers() const {
    return teachers;
}

vector<Teacher> DatabaseManager::searchTeachersByName(const string& name) const {
    vector<Teacher> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& teacher : teachers) {
        string fullName = teacher.getFullName();
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        if (fullName.find(lowerName) != string::npos) {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Teacher> DatabaseManager::searchTeachersByDepartment(const string& department) const {
    vector<Teacher> result;
    string lowerDepartment = department;
    transform(lowerDepartment.begin(), lowerDepartment.end(), lowerDepartment.begin(), ::tolower);

    for (const auto& teacher : teachers) {
        string teacherDepartment = teacher.getDepartment();
        transform(teacherDepartment.begin(), teacherDepartment.end(), teacherDepartment.begin(), ::tolower);
        if (teacherDepartment.find(lowerDepartment) != string::npos) {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Teacher> DatabaseManager::filterTeachersByDegree(const string& degree) const {
    vector<Teacher> result;
    string lowerDegree = degree;
    transform(lowerDegree.begin(), lowerDegree.end(), lowerDegree.begin(), ::tolower);

    for (const auto& teacher : teachers) {
        string teacherDegree = teacher.getAcademicDegree();
        transform(teacherDegree.begin(), teacherDegree.end(), teacherDegree.begin(), ::tolower);
        if (teacherDegree.find(lowerDegree) != string::npos) {
            result.push_back(teacher);
        }
    }
    return result;
}

void DatabaseManager::sortTeachersByName(bool ascending) {
    sort(teachers.begin(), teachers.end(),
        [ascending](const Teacher& a, const Teacher& b) {
            if (ascending) {
                return a.getFullName() < b.getFullName();
            } else {
                return a.getFullName() > b.getFullName();
            }
        });
}

void DatabaseManager::sortTeachersById(bool ascending) {
    sort(teachers.begin(), teachers.end(),
        [ascending](const Teacher& a, const Teacher& b) {
            if (ascending) {
                return a.getTeacherID() < b.getTeacherID();
            } else {
                return a.getTeacherID() > b.getTeacherID();
            }
        });
}

void DatabaseManager::addSubject(const Subject& subject) {
    if (!subject.isValid()) {
        throw invalid_argument("Некоректні дані предмета");
    }
    if (getSubject(subject.getSubjectId()) != nullptr) {
        throw invalid_argument("Предмет з таким ID вже існує: " + subject.getSubjectId());
    }
    subjects.push_back(subject);
}

bool DatabaseManager::editSubject(const string& subjectId, const Subject& newData) {
    if (!newData.isValid()) {
        throw invalid_argument("Некоректні нові дані предмета");
    }
    for (auto& subject : subjects) {
        if (subject.getSubjectId() == subjectId) {
            subject = newData;
            return true;
        }
    }
    return false;
}

bool DatabaseManager::deleteSubject(const string& subjectId) {
    auto it = remove_if(subjects.begin(), subjects.end(),
        [&](const Subject& s) { return s.getSubjectId() == subjectId; });
    if (it != subjects.end()) {
        subjects.erase(it, subjects.end());
        return true;
    }
    return false;
}

Subject* DatabaseManager::getSubject(const string& subjectId) {
    for (auto& subject : subjects) {
        if (subject.getSubjectId() == subjectId) {
            return &subject;
        }
    }
    return nullptr;
}

vector<Subject> DatabaseManager::getAllSubjects() const {
    return subjects;
}

vector<Subject> DatabaseManager::searchSubjectsByName(const string& name) const {
    vector<Subject> result;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& subject : subjects) {
        string subjectName = subject.getSubjectName();
        transform(subjectName.begin(), subjectName.end(), subjectName.begin(), ::tolower);
        if (subjectName.find(lowerName) != string::npos) {
            result.push_back(subject);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::filterSubjectsByCredits(int minCredits, int maxCredits) const {
    vector<Subject> result;
    for (const auto& subject : subjects) {
        int credits = subject.getEctsCredits();
        if (credits >= minCredits && credits <= maxCredits) {
            result.push_back(subject);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::filterSubjectsBySemester(int semester) const {
    vector<Subject> result;
    for (const auto& subject : subjects) {
        if (subject.getSemester() == semester) {
            result.push_back(subject);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::filterSubjectsByTeacher(const string& teacherId) const {
    vector<Subject> result;
    for (const auto& subject : subjects) {
        if (subject.getTeacherId() == teacherId) {
            result.push_back(subject);
        }
    }
    return result;
}

void DatabaseManager::sortSubjectsByName(bool ascending) {
    sort(subjects.begin(), subjects.end(),
        [ascending](const Subject& a, const Subject& b) {
            if (ascending) {
                return a.getSubjectName() < b.getSubjectName();
            } else {
                return a.getSubjectName() > b.getSubjectName();
            }
        });
}

void DatabaseManager::sortSubjectsByCredits(bool ascending) {
    sort(subjects.begin(), subjects.end(),
        [ascending](const Subject& a, const Subject& b) {
            if (ascending) {
                return a.getEctsCredits() < b.getEctsCredits();
            } else {
                return a.getEctsCredits() > b.getEctsCredits();
            }
        });
}

bool DatabaseManager::loadFromFile(const string& studentsFile, const string& teachersFile, const string& subjectsFile) {
    return loadStudentsFromFile(studentsFile) &&
           loadTeachersFromFile(teachersFile) &&
           loadSubjectsFromFile(subjectsFile);
}

bool DatabaseManager::saveToFile(const string& studentsFile, const string& teachersFile, const string& subjectsFile) const {
    return saveStudentsToFile(studentsFile) &&
           saveTeachersToFile(teachersFile) &&
           saveSubjectsToFile(subjectsFile);
}

void DatabaseManager::clear() {
    students.clear();
    teachers.clear();
    subjects.clear();
}

int DatabaseManager::getStudentCount() const {
    return students.size();
}

int DatabaseManager::getTeacherCount() const {
    return teachers.size();
}

int DatabaseManager::getSubjectCount() const {
    return subjects.size();
}

vector<Teacher> DatabaseManager::findTeachersWithoutSubjects() const {
    vector<Teacher> result;
    for (const auto& teacher : teachers) {
        if (!teacher.hasAssignedSubject()) {
            result.push_back(teacher);
        }
    }
    return result;
}

vector<Subject> DatabaseManager::findSubjectsWithoutTeacher() const {
    vector<Subject> result;
    for (const auto& subject : subjects) {
        if (!subject.hasAssignedTeacher()) {
            result.push_back(subject);
        }
    }
    return result;
}

bool DatabaseManager::loadStudentsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    students.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, lastName, email, studentID, educationalProgram;

        getline(ss, name, ',');
        getline(ss, lastName, ',');
        getline(ss, email, ',');
        getline(ss, studentID, ',');
        getline(ss, educationalProgram, ',');

        try {
            Student student(name, lastName, email, studentID, educationalProgram);
            students.push_back(student);
        } catch (const exception& e) {
            cerr << "Помилка завантаження студента: " << e.what() << endl;
        }
    }

    file.close();
    return true;
}

bool DatabaseManager::loadTeachersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    teachers.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, lastName, email, teacherID, department, academicDegree;

        getline(ss, name, ',');
        getline(ss, lastName, ',');
        getline(ss, email, ',');
        getline(ss, teacherID, ',');
        getline(ss, department, ',');
        getline(ss, academicDegree, ',');

        try {
            Teacher teacher(name, lastName, email, teacherID, department, academicDegree);
            teachers.push_back(teacher);
        } catch (const exception& e) {
            cerr << "Помилка завантаження викладача: " << e.what() << endl;
        }
    }

    file.close();
    return true;
}bool DatabaseManager::loadSubjectsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    subjects.clear();
    string line;
    int loadedCount = 0;
    int skippedCount = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string subjectId, subjectName, teacherId, creditsStr, semesterStr;

        getline(ss, subjectId, ',');
        getline(ss, subjectName, ',');
        getline(ss, creditsStr, ',');
        getline(ss, teacherId, ',');
        getline(ss, semesterStr, ',');

        // Перевіряємо формат ID предмета - має бути SJ + 3 цифри
        if (subjectId.length() != 5 ||
            subjectId.substr(0, 2) != "SJ" ||
            !all_of(subjectId.begin() + 2, subjectId.end(), ::isdigit)) {
            skippedCount++;
            cerr << "Пропущено предмет з некоректним ID: " << subjectId << endl;
            continue;
        }

        // Перевіряємо формат ID викладача - має бути PR + 3 цифри
        if (teacherId.length() != 5 ||
            teacherId.substr(0, 2) != "PR" ||
            !all_of(teacherId.begin() + 2, teacherId.end(), ::isdigit)) {
            skippedCount++;
            cerr << "Пропущено предмет з некоректним ID викладача: " << teacherId << endl;
            continue;
        }

        try {
            int credits = stoi(creditsStr);
            int semester = stoi(semesterStr);
            Subject subject(subjectId, subjectName, credits, teacherId, semester);
            subjects.push_back(subject);
            loadedCount++;
        } catch (const exception& e) {
            skippedCount++;
            cerr << "Помилка завантаження предмета: " << e.what() << endl;
        }
    }

    file.close();

    if (skippedCount > 0) {
        cout << "Завантажено " << loadedCount << " предметів. Пропущено " << skippedCount << " записів з некоректними даними." << endl;
    } else {
        cout << "Успішно завантажено " << loadedCount << " предметів." << endl;
    }

    return loadedCount > 0;
}

bool DatabaseManager::saveStudentsToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& student : students) {
        file << student.getName() << ","
             << student.getLastName() << ","
             << student.getEmail() << ","
             << student.getStudentID() << ","
             << student.getEducationalProgram() << endl;
    }

    file.close();
    cout << "Збережено " << students.size() << " студентів у файл: " << filename << endl;
    return true;
}

bool DatabaseManager::saveTeachersToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& teacher : teachers) {
        file << teacher.getName() << ","
             << teacher.getLastName() << ","
             << teacher.getEmail() << ","
             << teacher.getTeacherID() << ","
             << teacher.getDepartment() << ","
             << teacher.getAcademicDegree() << endl;
    }

    file.close();
    cout << "Збережено " << teachers.size() << " викладачів у файл: " << filename << endl;
    return true;
}

bool DatabaseManager::saveSubjectsToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& subject : subjects) {
        file << subject.getSubjectId() << ","
             << subject.getSubjectName() << ","
             << subject.getEctsCredits() << ","
             << subject.getTeacherId() << ","
             << subject.getSemester() << endl;
    }

    file.close();
    cout << "Збережено " << subjects.size() << " предметів у файл: " << filename << endl;
    return true;
}