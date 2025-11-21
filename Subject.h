#pragma once
#include "IPrint.h"
#include <string>
#include <stdexcept>

class Subject : public IPrint {
private:
    std::string subjectId;
    std::string subjectName;
    int ectsCredits;
    std::string teacherId;
    int semester;

public:
    // Конструктори
    Subject();
    Subject(const std::string& subjectId, const std::string& subjectName,
            int ectsCredits, const std::string& teacherId, int semester);
    Subject(const Subject& other);
    Subject(Subject&& other) noexcept;
    ~Subject() override;

    // Getter методи
    std::string getSubjectId() const { return subjectId; }
    std::string getSubjectName() const { return subjectName; }
    int getEctsCredits() const { return ectsCredits; }
    std::string getTeacherId() const { return teacherId; }
    int getSemester() const { return semester; }

    // Setter методи
    void setSubjectId(const std::string& subjectId);
    void setSubjectName(const std::string& subjectName);
    void setEctsCredits(int ectsCredits);
    void setTeacherId(const std::string& teacherId);
    void setSemester(int semester);

    // ВЛАСНІ МЕТОДИ (8+ методів):
    bool assignTeacher(const std::string& teacherId);
    bool removeTeacher();
    bool hasAssignedTeacher() const;
    void updateCredits(int newCredits);
    void changeSemester(int newSemester);
    bool isValid() const;
    std::string getSubjectInfo() const;
    bool isAvailableForEnrollment() const;
    bool matchesSearchCriteria(const std::string& criteria) const;
    bool canBeAssignedToTeacher(const std::string& teacherId) const;

    // Перевизначені методи
    void print() const override;
    std::string toString() const override;

    // Оператори
    Subject& operator=(const Subject& other);
    Subject& operator=(Subject&& other) noexcept;
    bool operator==(const Subject& other) const;

private:
    bool validateSubjectID(const std::string& id) const;
    bool validateCredits(int credits) const;
    bool validateSemester(int semester) const;
};