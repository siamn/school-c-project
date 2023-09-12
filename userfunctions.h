#include "header.h"

void userAddSubject(StudentsList *list, char *studentName);

int userAddNewStudents(StudentsList *list);

void userAddSubjectToExistingStudent(StudentsList *list);

int userAddNewTeachers(TeachersList *list);

void userFindStudentsForSubject(StudentsList *list);

void userFindTeacherForSubject(TeachersList *list);

void userFindGradesForStudent(StudentsList *list);

void userFindTeachersForStudent(StudentsList *studentsList, TeachersList *teachersList);

void userFindStudentsForTeacher(StudentsList *studentsList, TeachersList *teachersList);

void userDisplayStudents(StudentsList *list);