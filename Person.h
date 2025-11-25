#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <regex>

namespace University {

    class Person {
    private:
        std::string name;
        std::string lastName;
        std::string email;
        static bool ukrainianSupportInitialized;

        void initializeUkrainianSupport();
        void validateData() const;

    protected:
        static const int MIN_NAME_LENGTH = 2;
        static const int MAX_NAME_LENGTH = 50;
        static const int MIN_EMAIL_LENGTH = 5;

    public:
        Person();
        Person(const std::string& name, const std::string& lastName, const std::string& email);
        Person(const Person& other);
        Person(Person&& other) noexcept;
        virtual ~Person();

        // Getters
        std::string getName() const;
        std::string getLastName() const;
        std::string getEmail() const;
        std::string getFullName() const;

        // Setters
        void setName(const std::string& name);
        void setLastName(const std::string& lastName);
        void setEmail(const std::string& email);

        // Methods
        virtual bool isValid() const;
        void updateContactInfo(const std::string& newEmail);
        virtual void print() const = 0;
        virtual std::string toString() const = 0;

        // Static validation methods
        static bool validateEmail(const std::string& email);
        static bool validateName(const std::string& name);

        // Operators
        Person& operator=(const Person& other);
        Person& operator=(Person&& other) noexcept;
        bool operator==(const Person& other) const;
    };

} // namespace University

#endif