#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"
#include <string>

namespace University {

enum class AcademicDegree {
    BACHELOR,
    MASTER,
    DOCTOR
};

class Teacher : public Person {
private:
    std::string teacherID;
    std::string department;
    AcademicDegree academicDegree;


    static bool ukrainianSupportInitialized;
    static const double DEFAULT_WORKLOAD_HOURS;

    void initializeUkrainianSupport();
    bool validateTeacherID(const std::string& id) const;

public:
    Teacher();
    Teacher(const std::string& name, const std::string& lastName,
            const std::string& email, const std::string& teacherID,
            const std::string& department, AcademicDegree degree);
    Teacher(const Teacher& other);
    Teacher(Teacher&& other) noexcept;
    ~Teacher();

    // Getters
    std::string getTeacherID() const;
    std::string getDepartment() const;
    AcademicDegree getAcademicDegree() const;
    std::string getSubjectId() const;
   void setTeacherID(const std::string& id);
    void setDepartment(const std::string& dep);
    void setAcademicDegree(AcademicDegree deg);
    void setSubjectId(const std::string& subId);

    // Methods

    void promote(AcademicDegree newDegree);
    void changeDepartment(const std::string& newDep);
    std::string getTeachingStatus() const;
    double calculateWorkload() const;
    bool isAvailableForNewSubject() const;
    void updateAcademicProfile(AcademicDegree deg, const std::string& dep); std::string getAcademicDegreeString() const;

    // Setters


    // Overridden methods
    void print() const override;
    std::string toString() const override;
    bool isValid() const override;

    // Operators
    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;
    bool operator==(const Teacher& other) const;
    bool operator!=(const Teacher& other) const;
};

} // namespace University

#endif