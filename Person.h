#pragma once
#include <string>
#include <regex>
#include <stdexcept>
#include <iostream>
#include "IPrint.h"

class Person : public IPrint {
private:
    std::string name;
    std::string lastName;
    std::string email;

public:
    // Конструктори
    Person();
    Person(const std::string& name, const std::string& lastName,
           const std::string& email);
    Person(const Person& other);
    Person(Person&& other) noexcept;
    virtual ~Person();

    // Getter методи
    std::string getName() const { return name; }
    std::string getLastName() const { return lastName; }
    std::string getEmail() const { return email; }

    // Setter методи з валідацією
    void setName(const std::string& name);
    void setLastName(const std::string& lastName);
    void setEmail(const std::string& email);

    // Власні методи
    virtual void print() const override = 0;
    virtual std::string toString() const override = 0;
    virtual bool isValid() const;
    virtual std::string getFullName() const;
    static bool validateEmail(const std::string& email);
    static bool validateName(const std::string& name);
    void updateContactInfo(const std::string& newEmail);

    // Оператори
    Person& operator=(const Person& other);
    Person& operator=(Person&& other) noexcept;
    bool operator==(const Person& other) const;

protected:
    void validateData() const;
    void setupUkrainianSupport() const;
};