/**
 * @file DatabaseManager.h
 * @brief Заголовний файл для менеджеру бази даних університету
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Student.h"
#include "Teacher.h"
#include "Subject.h"
#include <vector>
#include <string>

namespace University {

/**
 * @class DatabaseManager
 * @brief Менеджер бази даних університету
 *
 * Відповідає за управління студентами, викладачами та предметами,
 * включаючи операції додавання, редагування, видалення, пошуку,
 * фільтрації та сортування даних.
 */
class DatabaseManager {
public:
    std::vector<Student> m_students;      ///< Список студентів
    std::vector<Teacher> m_teachers;      ///< Список викладачів
    std::vector<Subject> m_subjects;      ///< Список предметів

public:
    // === КОНСТРУКТОРИ ТА ДЕСТРУКТОР ===

    /**
     * @brief Конструктор за замовчуванням
     * @details Завантажує дані з файлів за замовчуванням
     */
    DatabaseManager();

    /**
     * @brief Конструктор з вказанням файлів
     * @param studentsFile Шлях до файлу студентів
     * @param teachersFile Шлях до файлу викладачів
     * @param subjectsFile Шлях до файлу предметів
     */
    DatabaseManager(const std::string& studentsFile,
                   const std::string& teachersFile,
                   const std::string& subjectsFile);

    /**
     * @brief Конструктор копіювання
     * @param other Об'єкт для копіювання
     */
    DatabaseManager(const DatabaseManager& other);

    /**
     * @brief Конструктор переміщення
     * @param other Об'єкт для переміщення
     */
    DatabaseManager(DatabaseManager&& other) noexcept;

    /**
     * @brief Деструктор
     */
    ~DatabaseManager();

    // === МЕТОДИ ДЛЯ СТУДЕНТІВ ===

    /**
     * @brief Отримує всіх студентів
     * @return Вектор студентів
     */
    std::vector<Student> GetAllStudents() const;

    /**
     * @brief Знаходить студента за ID
     * @param id ID студента
     * @return Вказівник на студента або nullptr, якщо не знайдено
     */
    Student* GetStudent(const std::string& id);

    /**
     * @brief Додає нового студента
     * @param student Студент для додавання
     * @return true якщо успішно, false в іншому випадку
     */
    bool AddStudent(const Student& student);

    /**
     * @brief Редагує дані студента
     * @param id ID студента для редагування
     * @param updatedStudent Оновлені дані студента
     * @return true якщо успішно, false в іншому випадку
     */
    bool EditStudent(const std::string& id, const Student& updatedStudent);

    /**
     * @brief Видаляє студента
     * @param id ID студента для видалення
     * @return true якщо успішно, false в іншому випадку
     */
    bool DeleteStudent(const std::string& id);

    // === МЕТОДИ ДЛЯ ВИКЛАДАЧІВ ===

    /**
     * @brief Отримує всіх викладачів
     * @return Вектор викладачів
     */
    std::vector<Teacher> GetAllTeachers() const;

    /**
     * @brief Знаходить викладача за ID
     * @param id ID викладача
     * @return Вказівник на викладача або nullptr, якщо не знайдено
     */
    Teacher* GetTeacher(const std::string& id);

    /**
     * @brief Додає нового викладача
     * @param teacher Викладач для додавання
     * @return true якщо успішно, false в іншому випадку
     */
    bool AddTeacher(const Teacher& teacher);

    /**
     * @brief Редагує дані викладача
     * @param id ID викладача для редагування
     * @param updatedTeacher Оновлені дані викладача
     * @return true якщо успішно, false в іншому випадку
     */
    bool EditTeacher(const std::string& id, const Teacher& updatedTeacher);

    /**
     * @brief Видаляє викладача
     * @param id ID викладача для видалення
     * @return true якщо успішно, false в іншому випадку
     */
    bool DeleteTeacher(const std::string& id);

    // === МЕТОДИ ДЛЯ ПРЕДМЕТІВ ===

    /**
     * @brief Отримує всі предмети
     * @return Вектор предметів
     */
    std::vector<Subject> GetAllSubjects() const;

    /**
     * @brief Знаходить предмет за ID
     * @param id ID предмета
     * @return Вказівник на предмет або nullptr, якщо не знайдено
     */
    Subject* GetSubject(const std::string& id);

    /**
     * @brief Додає новий предмет
     * @param subject Предмет для додавання
     * @return true якщо успішно, false в іншому випадку
     */
    bool AddSubject(const Subject& subject);

    /**
     * @brief Редагує дані предмета
     * @param id ID предмета для редагування
     * @param updatedSubject Оновлені дані предмета
     * @return true якщо успішно, false в іншому випадку
     */
    bool EditSubject(const std::string& id, const Subject& updatedSubject);

    /**
     * @brief Видаляє предмет
     * @param id ID предмета для видалення
     * @return true якщо успішно, false в іншому випадку
     */
    bool DeleteSubject(const std::string& id);

    // === ПОШУК ===

    /**
     * @brief Пошук студентів за іменем (нечутливий до регістру)
     * @param name Ім'я для пошуку
     * @return Вектор знайдених студентів
     */
    std::vector<Student> SearchStudentsByName(const std::string& name) const;

    /**
     * @brief Пошук викладачів за іменем (нечутливий до регістру)
     * @param name Ім'я для пошуку
     * @return Вектор знайдених викладачів
     */
    std::vector<Teacher> SearchTeachersByName(const std::string& name) const;

    /**
     * @brief Пошук предметів за назвою (нечутливий до регістру)
     * @param name Назва для пошуку
     * @return Вектор знайдених предметів
     */
    std::vector<Subject> SearchSubjectsByName(const std::string& name) const;

    // === ФІЛЬТРАЦІЯ ===

    /**
     * @brief Фільтрація студентів за освітньою програмою
     * @param program Освітня програма для фільтрації
     * @return Вектор відфільтрованих студентів
     */
    std::vector<Student> FilterStudentsByProgram(const std::string& program) const;

    /**
     * @brief Фільтрація викладачів за кафедрою
     * @param department Кафедра для фільтрації
     * @return Вектор відфільтрованих викладачів
     */
    std::vector<Teacher> FilterTeachersByDepartment(const std::string& department) const;

    /**
     * @brief Фільтрація предметів за семестром
     * @param semester Семестр для фільтрації
     * @return Вектор відфільтрованих предметів
     */
    std::vector<Subject> FilterSubjectsBySemester(int semester) const;

    // === СОРТУВАННЯ ===

    /**
     * @brief Сортування студентів за іменем
     * @param ascending true - за зростанням, false - за спаданням
     */
    void SortStudentsByName(bool ascending = true);

    /**
     * @brief Сортування викладачів за іменем
     * @param ascending true - за зростанням, false - за спаданням
     */
    void SortTeachersByName(bool ascending = true);

    /**
     * @brief Сортування предметів за назвою
     * @param ascending true - за зростанням, false - за спаданням
     */
    void SortSubjectsByName(bool ascending = true);

    // === ВІДОБРАЖЕННЯ ===

    /**
     * @brief Вивід відсортованих студентів у консоль
     * @param ascending true - за зростанням, false - за спаданням
     */
    void DisplaySortedStudents(bool ascending);

    /**
     * @brief Вивід відсортованих викладачів у консоль
     * @param ascending true - за зростанням, false - за спаданням
     */
    void DisplaySortedTeachers(bool ascending);

    /**
     * @brief Вивід відсортованих предметів у консоль
     * @param ascending true - за зростанням, false - за спаданням
     */
    void DisplaySortedSubjects(bool ascending);

    // === ОТРИМАННЯ ДАНИХ ===

    /**
     * @brief Отримує відсортованих студентів за іменем
     * @param ascending true - за зростанням, false - за спаданням
     * @return Вектор відсортованих студентів
     */
    std::vector<Student> GetSortedStudentsByName(bool ascending);

    /**
     * @brief Отримує відсортованих викладачів за іменем
     * @param ascending true - за зростанням, false - за спаданням
     * @return Вектор відсортованих викладачів
     */
    std::vector<Teacher> GetSortedTeachersByName(bool ascending);

    /**
     * @brief Отримує відсортованих предметів за назвою
     * @param ascending true - за зростанням, false - за спаданням
     * @return Вектор відсортованих предметів
     */
    std::vector<Subject> GetSortedSubjectsByName(bool ascending);

    // === ФАЙЛОВІ ОПЕРАЦІЇ ===

    /**
     * @brief Завантажує дані з файлів
     * @param studentsFile Файл студентів
     * @param teachersFile Файл викладачів
     * @param subjectsFile Файл предметів
     * @return true якщо успішно, false в іншому випадку
     */
    bool LoadFromFile(const std::string& studentsFile,
                     const std::string& teachersFile,
                     const std::string& subjectsFile);

    /**
     * @brief Зберігає дані у файли
     * @param studentsFile Файл студентів
     * @param teachersFile Файл викладачів
     * @param subjectsFile Файл предметів
     * @return true якщо успішно, false в іншому випадку
     */
    bool SaveToFile(const std::string& studentsFile,
                   const std::string& teachersFile,
                   const std::string& subjectsFile) const;

    // === УТІЛІТИ ===

    /**
     * @brief Очищає всі дані
     */
    void Clear();

private:
    // === ПРИВАТНІ ФАЙЛОВІ МЕТОДИ ===

    bool LoadStudentsFromFile(const std::string& filename);
    bool LoadTeachersFromFile(const std::string& filename);
    bool LoadSubjectsFromFile(const std::string& filename);
    bool SaveStudentsToFile(const std::string& filename) const;
    bool SaveTeachersToFile(const std::string& filename) const;
    bool SaveSubjectsToFile(const std::string& filename) const;
};

} // namespace University

#endif // DATABASEMANAGER_H