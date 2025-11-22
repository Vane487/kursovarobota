#pragma once

#include <string>
#include <regex>
#include <stdexcept>
#include <iostream>
#include "IPrint.h"

/**
 * @brief Простір імен University для компонентів управління університетом
 */
namespace University {

/**
 * @class Person
 * @brief Базовий клас, що представляє особу в університетській системі
 *
 * Надає базовий функціонал для управління особистою інформацією,
 * включаючи валідацію імені, прізвища та електронної пошти.
 */
class Person : public IPrint
{
private:
    // Поля
    std::string name;          ///< Ім'я особи
    std::string lastName;      ///< Прізвище особи
    std::string email;         ///< Електронна пошта
    static bool ukrainianSupportInitialized; ///< Статус ініціалізації української мови

public:
    // Конструктори та деструктор

    /**
     * @brief Конструктор за замовчуванням
     */
    Person();

    /**
     * @brief Конструктор з параметрами
     * @param name Ім'я особи
     * @param lastName Прізвище особи
     * @param email Електронна пошта
     */
    Person(const std::string& name, const std::string& lastName,
           const std::string& email);

    /**
     * @brief Деструктор
     */
    virtual ~Person();

    // Властивості

    /**
     * @brief Отримує ім'я особи
     * @return Ім'я особи
     */
    std::string getName() const;

    /**
     * @brief Отримує прізвище особи
     * @return Прізвище особи
     */
    std::string getLastName() const;

    /**
     * @brief Отримує електронну пошту
     * @return Електронна пошта
     */
    std::string getEmail() const;

    /**
     * @brief Встановлює ім'я особи
     * @param name Ім'я особи
     */
    void setName(const std::string& name);

    /**
     * @brief Встановлює прізвище особи
     * @param lastName Прізвище особи
     */
    void setLastName(const std::string& lastName);

    /**
     * @brief Встановлює електронну пошту
     * @param email Електронна пошта
     */
    void setEmail(const std::string& email);

    // Публічні методи

    /**
     * @brief Перевіряє коректність даних особи
     * @return true якщо дані коректні
     */
    virtual bool isValid() const;

    /**
     * @brief Отримує повне ім'я особи
     * @return Повне ім'я (ім'я + прізвище)
     */
    virtual std::string getFullName() const;

    /**
     * @brief Оновлює контактну інформацію
     * @param newEmail Нова електронна пошта
     */
    void updateContactInfo(const std::string& newEmail);

    // Статичні методи валідації

    /**
     * @brief Валідує електронну пошту
     * @param email Електронна пошта для валідації
     * @return true якщо email коректний
     */
    static bool validateEmail(const std::string& email);

    /**
     * @brief Валідує ім'я або прізвище
     * @param name Ім'я для валідації
     * @return true якщо ім'я коректне
     */
    static bool validateName(const std::string& name);

    // Чисто віртуальні методи (абстрактний клас)

    /**
     * @brief Виводить інформацію про особу
     */
    virtual void print() const override = 0;

    /**
     * @brief Перетворює об'єкт в рядок
     * @return Рядкове представлення об'єкта
     */
    virtual std::string toString() const override = 0;

    // Оператори

    /**
     * @brief Оператор присвоєння
     * @param other Об'єкт для присвоєння
     * @return Посилання на поточний об'єкт
     */
    Person& operator=(const Person& other);

    /**
     * @brief Оператор порівняння
     * @param other Об'єкт для порівняння
     * @return true якщо об'єкти рівні
     */
    bool operator==(const Person& other) const;

protected:
    // Захищені методи

    /**
     * @brief Валідує всі дані особи
     */
    void validateData() const;

    /**
     * @brief Ініціалізує підтримку української мови
     */
    void initializeUkrainianSupport();

    // Константи
    static constexpr size_t MIN_EMAIL_LENGTH = 10;      ///< Мінімальна довжина email
    static constexpr size_t MIN_NAME_LENGTH = 3;       ///< Мінімальна довжина імені
    static constexpr size_t MAX_NAME_LENGTH = 20;      ///< Максимальна довжина імені
};

} // namespace University