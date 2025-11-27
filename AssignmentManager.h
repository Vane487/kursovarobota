/**
 * @file AssignmentManager.h
 * @brief Заголовний файл для управління призначеннями викладачів на предмети та записами студентів
 */

#ifndef ASSIGNMENTMANAGER_H
#define ASSIGNMENTMANAGER_H

#include <string>
#include <map>
#include <vector>

namespace University {

// Попереднє оголошення
class DatabaseManager;

/**
 * @class AssignmentManager
 * @brief Керує призначеннями викладачів на предмети та записами студентів
 *
 * Цей клас надає функціональність для призначення викладачів на предмети,
 * запису студентів на предмети та управління цими зв'язками зі збереженням у файлах.
 */
class AssignmentManager {
private:
    std::map<std::string, std::string> m_teacherSubjects;              ///< Мапа ID викладача до ID предмета
    std::map<std::string, std::string> m_subjectTeachers;              ///< Мапа ID предмета до ID викладача
    std::map<std::string, std::vector<std::string>> m_studentSubjects; ///< Мапа ID студента до списку ID предметів
    std::map<std::string, std::vector<std::string>> m_subjectStudents; ///< Мапа ID предмета до списку ID студентів

    // Константи повідомлень
    static const std::string MSG_ERROR_TEACHER_HAS_SUBJECT;        ///< Помилка: Викладач вже має призначений предмет
    static const std::string MSG_ERROR_SUBJECT_HAS_TEACHER;        ///< Помилка: Предмет вже має призначеного викладача
    static const std::string MSG_SUCCESS_TEACHER_ASSIGNED;         ///< Успіх: Викладача призначено на предмет
    static const std::string MSG_SUCCESS_TEACHER_REMOVED;          ///< Успіх: Призначення викладача видалено
    static const std::string MSG_STATUS_NO_SUBJECT;                ///< Статус: Предмет не призначено
    static const std::string MSG_STATUS_HAS_SUBJECT;               ///< Статус: Предмет призначено
    static const std::string MSG_ERROR_STUDENT_ALREADY_ENROLLED;   ///< Помилка: Студент вже записаний на предмет
    static const std::string MSG_SUCCESS_STUDENT_ENROLLED;         ///< Успіх: Студента записано на предмет
    static const std::string MSG_SUCCESS_STUDENT_UNENROLLED;       ///< Успіх: Студента видалено з предмету

    /**
     * @brief Завантажує дані призначень з файлу
     * @return true якщо завантаження успішне, false в іншому випадку
     */
    bool loadFromFile();

    /**
     * @brief Зберігає дані призначень у файл
     * @return true якщо збереження успішне, false в іншому випадку
     */
    bool saveToFile() const;

public:
    /**
     * @brief Конструктор за замовчуванням
     * @details Ініціалізує менеджер та завантажує існуючі дані з файлу
     */
    AssignmentManager();

    // Методи для призначення викладачів на предмети

    /**
     * @brief Призначає викладача на предмет
     * @param teacherId ID викладача
     * @param subId ID предмета
     * @return true якщо призначення успішне, false в іншому випадку
     */
    bool assignToSubject(const std::string& teacherId, const std::string& subId);

    /**
     * @brief Видаляє призначення викладача з предмету
     * @param teacherId ID викладача
     * @return true якщо видалення успішне, false в іншому випадку
     */
    bool removeFromSubject(const std::string& teacherId);

    /**
     * @brief Отримує статус призначення викладача
     * @param teacherId ID викладача
     * @return Рядок зі статусом призначення
     */
    std::string getTeachingStatus(const std::string& teacherId) const;

    /**
     * @brief Отримує предмет, призначений викладачу
     * @param teacherId ID викладача
     * @return ID предмета або порожній рядок, якщо предмет не призначено
     */
    std::string getTeacherSubject(const std::string& teacherId) const;

    /**
     * @brief Отримує всі призначення викладачів
     * @return Мапа з усіма призначеннями викладачів
     */
    std::map<std::string, std::string> getAllTeacherAssignments() const;

    /**
     * @brief Отримує детальний статус призначення викладача
     * @param teacherId ID викладача
     * @param dbManager Вказівник на менеджер бази даних
     * @return Детальний рядок зі статусом призначення
     */
    std::string getDetailedTeachingStatus(const std::string& teacherId, DatabaseManager* dbManager) const;

    // Методи для запису студентів на предмети

    /**
     * @brief Записує студента на предмет
     * @param studentId ID студента
     * @param subjectId ID предмета
     * @return true якщо запис успішний, false в іншому випадку
     */
    bool enrollStudentInSubject(const std::string& studentId, const std::string& subjectId);

    /**
     * @brief Видаляє студента з предмету
     * @param studentId ID студента
     * @param subjectId ID предмета
     * @return true якщо видалення успішне, false в іншому випадку
     */
    bool unenrollStudentFromSubject(const std::string& studentId, const std::string& subjectId);

    /**
     * @brief Перевіряє, чи записаний студент на предмет
     * @param studentId ID студента
     * @param subjectId ID предмета
     * @return true якщо студент записаний на предмет, false в іншому випадку
     */
    bool isStudentEnrolled(const std::string& studentId, const std::string& subjectId) const;

    /**
     * @brief Отримує список предметів, на які записаний студент
     * @param studentId ID студента
     * @return Вектор з ID предметів студента
     */
    std::vector<std::string> getStudentSubjects(const std::string& studentId) const;

    // Службові методи

    /**
     * @brief Виводить налагоджувальну інформацію про всі призначення
     */
    void debugPrintAllAssignments() const;
};

} // namespace University

#endif // ASSIGNMENTMANAGER_H