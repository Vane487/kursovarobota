#pragma once

#include "IPrint.h"
#include <string>
#include <stdexcept>

/**
 * @brief Простір імен University для компонентів управління університетом
 */
namespace University {

/**
 * @class Subject
 * @brief Клас, що представляє навчальний предмет
 *
 * Надає функціонал для управління інформацією про навчальний предмет,
 * включаючи призначення викладачів, управління кредитами та семестрами.
 */
class Subject : public IPrint
{
private:
    // Поля
    std::string subjectId;      ///< Ідентифікатор предмету
    std::string subjectName;    ///< Назва предмету
    int ectsCredits;           ///< Кількість ECTS кредитів
    std::string teacherId;     ///< Ідентифікатор викладача
    int semester;              ///< Семестр викладання

public:
    // Конструктори та деструктор

    /**
     * @brief Конструктор за замовчуванням
     */
    Subject();

    /**
     * @brief Конструктор з параметрами
     * @param subjectId Ідентифікатор предмету
     * @param subjectName Назва предмету
     * @param ectsCredits Кількість ECTS кредитів
     * @param teacherId Ідентифікатор викладача
     * @param semester Семестр викладання
     */
    Subject(const std::string& subjectId, const std::string& subjectName,
            int ectsCredits, const std::string& teacherId, int semester);

    /**
     * @brief Деструктор
     */
    ~Subject() override;

    // Властивості

    /**
     * @brief Отримує ідентифікатор предмету
     * @return Ідентифікатор предмету
     */
    std::string getSubjectId() const;

    /**
     * @brief Отримує назву предмету
     * @return Назва предмету
     */
    std::string getSubjectName() const;

    /**
     * @brief Отримує кількість ECTS кредитів
     * @return Кількість кредитів
     */
    int getEctsCredits() const;

    /**
     * @brief Отримує ідентифікатор викладача
     * @return Ідентифікатор викладача
     */
    std::string getTeacherId() const;

    /**
     * @brief Отримує семестр викладання
     * @return Семестр викладання
     */
    int getSemester() const;

    /**
     * @brief Встановлює ідентифікатор предмету
     * @param subjectId Ідентифікатор предмету
     */
    void setSubjectId(const std::string& subjectId);

    /**
     * @brief Встановлює назву предмету
     * @param subjectName Назва предмету
     */
    void setSubjectName(const std::string& subjectName);

    /**
     * @brief Встановлює кількість ECTS кредитів
     * @param ectsCredits Кількість кредитів
     */
    void setEctsCredits(int ectsCredits);

    /**
     * @brief Встановлює ідентифікатор викладача
     * @param teacherId Ідентифікатор викладача
     */
    void setTeacherId(const std::string& teacherId);

    /**
     * @brief Встановлює семестр викладання
     * @param semester Семестр викладання
     */
    void setSemester(int semester);

    // Публічні методи

    /**
     * @brief Призначає викладача до предмету
     * @param teacherId Ідентифікатор викладача
     * @return true якщо призначення успішне
     */
    bool assignTeacher(const std::string& teacherId);

    /**
     * @brief Видаляє викладача з предмету
     * @return true якщо видалення успішне
     */
    bool removeTeacher();

    /**
     * @brief Перевіряє чи має предмет призначеного викладача
     * @return true якщо викладач призначений
     */
    bool hasAssignedTeacher() const;

    /**
     * @brief Оновлює кількість кредитів
     * @param newCredits Нова кількість кредитів
     */
    void updateCredits(int newCredits);

    /**
     * @brief Змінює семестр викладання
     * @param newSemester Новий семестр
     */
    void changeSemester(int newSemester);

    /**
     * @brief Перевіряє коректність даних предмету
     * @return true якщо дані коректні
     */
    bool isValid() const;

    /**
     * @brief Отримує інформацію про предмет
     * @return Рядок з інформацією про предмет
     */
    std::string getSubjectInfo() const;

    /**
     * @brief Перевіряє відповідність критеріям пошуку
     * @param criteria Критерій пошуку
     * @return true якщо відповідає критеріям
     */
    bool matchesSearchCriteria(const std::string& criteria) const;

    /**
     * @brief Перевіряє чи може предмет бути призначений викладачу
     * @param teacherId Ідентифікатор викладача
     * @return true якщо може бути призначений
     */
    // Перевизначені методи

    /**
     * @brief Виводить інформацію про предмет
     */
    void print() const override;

    /**
     * @brief Перетворює об'єкт в рядок
     * @return Рядкове представлення об'єкта
     */
    std::string toString() const override;

    // Оператори

    /**
     * @brief Оператор порівняння
     * @param other Об'єкт для порівняння
     * @return true якщо об'єкти рівні
     */
    bool operator==(const Subject& other) const;

private:
    // Приватні методи

    /**
     * @brief Валідує ідентифікатор предмету
     * @param id Ідентифікатор для валідації
     * @return true якщо ідентифікатор коректний
     */
    bool validateSubjectID(const std::string& id) const;

    /**
     * @brief Валідує кількість кредитів
     * @param credits Кількість кредитів для валідації
     * @return true якщо кредити коректні
     */
    bool validateCredits(int credits) const;

    /**
     * @brief Валідує семестр
     * @param semester Семестр для валідації
     * @return true якщо семестр коректний
     */
    bool validateSemester(int semester) const;

    // Константи
    static constexpr int MIN_CREDITS = 1;     ///< Мінімальна кількість кредитів
    static constexpr int MAX_CREDITS = 10;    ///< Максимальна кількість кредитів
    static constexpr int MIN_SEMESTER = 1;    ///< Мінімальний семестр
    static constexpr int MAX_SEMESTER = 2;    ///< Максимальний семестр (2 семестри)
};

} // namespace University