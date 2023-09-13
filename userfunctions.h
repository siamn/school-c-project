#include "header.h"

/**
 * @brief Asks user for the number of subjects they wish to add,
 * each of their names and optionally whether they want to specify their
 * grades. Duplicate subjects (i.e. those which share the same name) cannot
 * be added to the same student.
 * The new data is stored in the list passed as argument.
 *
 * @param list
 * @param studentName
 */
void userAddSubject(StudentsList *list, char *studentName);

/**
 * @brief Asks user for the number of new students they wish to add and
 * their names. For each student, they are asked the number of subjects
 * they wish to add and optionally include their grades. Students
 * that share the same name cannot be added.
 * The new data is stored in the list passed as argument.
 *
 * @param list
 * @return int
 */
int userAddNewStudents(StudentsList *list);

/**
 * @brief Asks user if they wish to add a subject and a grade to an
 * existing student. The new data is stored in the list passed as argument.
 *
 * @param list
 */
void userAddSubjectToExistingStudent(StudentsList *list);

/**
 * @brief Asks user for the number of new teachers they wish to add.
 * For each new user, their name is asked and the subject they teach.
 * The new data is stored in the list passed as argument.
 *
 * @param list
 * @return int
 */
int userAddNewTeachers(TeachersList *list);

/**
 * @brief Asks user for the name of a subject they wish to find a list
 * of students for. The students registed on this subject are displayed to the user.
 *
 * @param list
 */
void userFindStudentsForSubject(StudentsList *list);

/**
 * @brief Asks user for the name of a subject they wish to the corresponding
 * teacher for. The teacher registered on this subject is displayed to the user.
 *
 * @param list
 */
void userFindTeacherForSubject(TeachersList *list);

/**
 * @brief Asks user for the name of the student and a subject which the student studies
 * to find their grades in that subject. The subject name and their corresponding grade is displayed
 * to the user if the student exists and is registered to be studying this subject.
 *
 * @param list
 */
void userFindGradesForStudent(StudentsList *list);

/**
 * @brief Asks user for the name of the student they wish to find a list of teachers for.
 * The list of teachers teaching this student is displayed to the user if the student is registered.
 *
 * @param studentsList
 * @param teachersList
 */
void userFindTeachersForStudent(StudentsList *studentsList, TeachersList *teachersList);

/**
 * @brief Asks user for the name of the teacher they wish to find a list of students for.
 * The list of students taught by this teacher is displayed to the user if the teacher is registered.
 *
 * @param studentsList
 * @param teachersList
 */
void userFindStudentsForTeacher(StudentsList *studentsList, TeachersList *teachersList);

/**
 * @brief Asks user if they wish to display the list of students registered in the school
 * along with their grades. If yes, for each student, their names along with each of the subjects
 * they study and their corresponding grades is displayed to the user. Otherwise, only their names
 * are displayed.
 *
 * @param list
 */
void userDisplayStudents(StudentsList *list);