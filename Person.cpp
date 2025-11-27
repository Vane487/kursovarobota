#include "Person.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

namespace University {

bool Person::ukrainianSupportInitialized = false;

void Person::initializeUkrainianSupport()
{
    if (ukrainianSupportInitialized)
    {
        return;
    }
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try
    {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }
    catch (...)
    {
        try
        {
            setlocale(LC_ALL, "C.UTF-8");
        }
        catch (...)
        {
            setlocale(LC_ALL, "");
        }
    }
    ukrainianSupportInitialized = true;
}

void Person::validateData() const
{
    if (!validateName(name))
    {
        throw invalid_argument("Некоректне ім'я: " + name);
    }
    if (!validateName(lastName))
    {
        throw invalid_argument("Некоректне прізвище: " + lastName);
    }
    if (!validateEmail(email))
    {
        throw invalid_argument("Некоректний email: " + email);
    }
}

Person::Person() : name(""), lastName(""), email("")
{
    initializeUkrainianSupport();
}

Person::Person(const string& name, const string& lastName, const string& email)
    : name(name), lastName(lastName), email(email)
{
    initializeUkrainianSupport();
    validateData();
}

Person::Person(const Person& other)
    : name(other.name), lastName(other.lastName), email(other.email)
{
}

Person::Person(Person&& other) noexcept
    : name(move(other.name)), lastName(move(other.lastName)), email(move(other.email))
{
}

Person::~Person()
{
    cout << "Об'єкт Person знищено: " << name << " " << lastName << endl;
}

string Person::getName() const
{
    return name;
}

string Person::getLastName() const
{
    return lastName;
}

string Person::getEmail() const
{
    return email;
}

string Person::getFullName() const
{
    return name + " " + lastName;
}

void Person::setName(const string& name)
{
    if (!validateName(name))
    {
        throw invalid_argument("Некоректне ім'я: " + name);
    }
    this->name = name;
}

void Person::setLastName(const string& lastName)
{
    if (!validateName(lastName))
    {
        throw invalid_argument("Некоректне прізвище: " + lastName);
    }
    this->lastName = lastName;
}

void Person::setEmail(const string& email)
{
    if (!validateEmail(email))
    {
        throw invalid_argument("Некоректний email: " + email);
    }
    this->email = email;
}

bool Person::isValid() const
{
    return !name.empty() && !lastName.empty() && validateEmail(email);
}

void Person::updateContactInfo(const string& newEmail)
{
    setEmail(newEmail);
}

bool Person::validateEmail(const string& email)
{
    if (email.empty() || email.length() < MIN_EMAIL_LENGTH)
    {
        return false;
    }
    regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, pattern);
}

bool Person::validateName(const string& name)
{
    if (name.empty() || name.length() < MIN_NAME_LENGTH || name.length() > MAX_NAME_LENGTH)
    {
        return false;
    }
    return all_of(name.begin(), name.end(), [](unsigned char c)
    {
        return isalpha(c) || c == ' ' || c == '-' || c > 127;
    });
}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        name = other.name;
        lastName = other.lastName;
        email = other.email;
    }
    return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
    if (this != &other)
    {
        name = move(other.name);
        lastName = move(other.lastName);
        email = move(other.email);
    }
    return *this;
}

bool Person::operator==(const Person& other) const
{
    return email == other.email;
}

} // namespace University