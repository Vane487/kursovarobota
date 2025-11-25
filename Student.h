#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <vector>
#include <string>

namespace University {

    class Student : public Person {
    private:
        std::string studentID;
        std::string educationalProgram;
        std::vector<std::string> enrolledSubjects;
        static bool ukrainianSupportInitialized;

        void initializeUkrainianSupport();
        bool validateStudentID(const std::string& id) const;

    public:
        Student();
        Student(const std::string& name, const std::string& lastName,
                const std::string& email, const std::string& studentID,
                const std::string& educationalProgram);
        Student(const Student& other);
        Student(Student&& other) noexcept;
        ~Student();

        // Getters
        std::string getStudentID() const;
        std::string getEducationalProgram() const;
        std::vector<std::string> getEnrolledSubjects() const;
        int getEnrolledSubjectsCount() const;

        // Setters
        void setStudentID(const std::string& studentID);
        void setEducationalProgram(const std::string& educationalProgram);

        // Methods
        void enrollSubject(const std::string& subjectId);
        void dropSubject(const std::string& subjectId);
        bool isEnrolled(const std::string& subjectId) const;
        void listSubjects() const;
        void clearSubjects();
        void changeEducationalProgram(const std::string& newEducationalProgram);


        // Overridden methods
        void print() const override;
        std::string toString() const override;
        bool isValid() const override;

        // Operators
        Student& operator=(const Student& other);
        Student& operator=(Student&& other) noexcept;
        bool operator==(const Student& other) const;
    };

} // namespace University

#endif