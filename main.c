#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "userinput.h"
#include "userfunctions.h"

/*
    Continuation of James Tam's School C Project by Siam Islam
*/

#define DEFAULT_STUDENTS_ARRAY_SIZE 2
#define DEFAULT_TEACHERS_ARRAY_SIZE 2
#define DEFAULT_SUBJECTS_ARRAY_SIZE 20

const int QUIT = 0;

// check if you can still access unallocated memory when adding students
// e.g. if num students set to 1, can still add more students and print them out.

/* TODO: Can currently add duplicate subjects
e.g. add student with subject Math with no grade using option 1
then use option 2 to add grade for same subject by typing Math for same student
another math subject is added rather than replacing the existing math subject */

Student **allocateStudentsStructs(void)
{
    printf("Allocating memory for struct array. \n");
    int size = DEFAULT_STUDENTS_ARRAY_SIZE;

    Student **students = (Student **)malloc(sizeof(Student *) * size);

    if (students == NULL)
    {
        perror("Error allocating memory for struct array. \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        students[i] = (Student *)malloc(sizeof(Student));

        if (students[i] == NULL)
        {
            perror("Error allocating memory for single struct");
            exit(EXIT_FAILURE);
        }
    }

    return (students);
}

Teacher **allocateTeachersStructs(void)
{
    printf("Allocating memory for teacher struct array. \n");

    const int size = DEFAULT_TEACHERS_ARRAY_SIZE;

    Teacher **teachers = (Teacher **)malloc(sizeof(Teacher *) * size);

    if (teachers == NULL)
    {
        perror("Error allocating memory for struct array. \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        teachers[i] = (Teacher *)malloc(sizeof(Teacher));

        if (teachers[i] == NULL)
        {
            perror("Error allocating memory for single struct");
            exit(EXIT_FAILURE);
        }
    }

    return (teachers);
}

int studentExists2(StudentsList *list, char *studentName)
{
    for (int i = 0; i < list->currentSize; i++)
    {
        if (strcmp(list->students[i]->name, studentName) == 0)
        {
            return i;
        }
    }
    return -1;
}

int subjectExistsForStudent(Student *student, char *subject)
{
    for (int i = 0; i < student->subjectCount; i++)
    {
        if (strcmp(subject, student->subjects[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int teacherExists2(TeachersList *list, char *teacher)
{
    for (int i = 0; i < list->currentSize; i++)
    {
        if (strcmp(list->teachers[i]->name, teacher) == 0)
        {
            return i;
        }
    }
    return -1;
}

int teacherExistsForSubject2(TeachersList *list, char *subject)
{
    for (int i = 0; i < list->currentSize; i++)
    {
        Teacher *teacher = list->teachers[i];
        if (strcmp(subject, teacher->subject.name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int expandStudentsStruct(Student ***students, int currentSize, int maxSize)
{
    int newMaxSize = maxSize;
    if (currentSize >= 0.5 * maxSize)
    {
        newMaxSize = maxSize * 2;
        printf("Before realloc: %p\n", students);
        Student **newStudents = realloc(*students, newMaxSize * sizeof(Student *));
        if (newStudents == NULL)
        {
            perror("Unable to realloc memory.\n");
            return -1;
        }
        *students = newStudents;
        printf("After realloc: %p\n", students);
        for (int i = currentSize; i < newMaxSize; i++)
        {
            (*students)[i] = (Student *)malloc(sizeof(Student));

            if ((*students)[i] == NULL)
            {
                perror("Error allocating memory for single struct");
                return -1;
            }
        }
        return newMaxSize;
    }
    return maxSize;
}

int expandTeachersStruct(Teacher ***teachers, int currentSize, int maxSize)
{
    int newMaxSize = maxSize;
    if (currentSize >= 0.5 * maxSize)
    {
        newMaxSize = maxSize * 2;

        printf("Before realloc: %p\n", teachers);

        Teacher **newTeachers = realloc(*teachers, newMaxSize * sizeof(Teacher *));
        if (newTeachers == NULL)
        {
            perror("Unable to reallocate memory.\n");
            return -1;
        }
        *teachers = newTeachers;

        printf("After realloc: %p\n", teachers);

        for (int i = currentSize; i < newMaxSize; i++)
        {
            (*teachers)[i] = malloc(sizeof(Teacher));

            if ((*teachers)[i] == NULL)
            {
                perror("Error allocating memory for single struct");
                return -1;
            }
        }
        return newMaxSize;
    }
    return maxSize;
}

int addStudent2(StudentsList *studentsList, char *studentName)
{
    int index = studentsList->currentSize;
    printf("Adding student %s \n", studentName);
    studentsList->maxSize = expandStudentsStruct(&studentsList->students, studentsList->currentSize, studentsList->maxSize);
    Student **students = studentsList->students;
    students[index]->name = studentName;

    students[index]->subjects = (Subject *)malloc(sizeof(Subject) * DEFAULT_SUBJECTS_ARRAY_SIZE); // allocate space using malloc() for student subjects;
    if (students[index]->subjects == NULL)
    {
        perror("Error allocating memory for subject pointer");
        return -1;
    }
    // initialise the subjects that this particular student studies to 0
    students[index]->subjectCount = 0;

    studentsList->currentSize++;

    printf("\nSuccessfully added student '%s' to the school database system.  \n\n", studentName);

    return 1;
}

void addTeacher2(TeachersList *list, char *teacherName, char *subjectName)
{
    int index = list->currentSize;
    printf("Adding teacher %s \n", teacherName);
    list->maxSize = expandTeachersStruct(&list->teachers, index, list->maxSize);

    list->teachers[index]->name = teacherName;
    list->teachers[index]->subject.name = subjectName;

    printf("\nSuccessfully added teacher '%s' teaching %s to the school database system.  \n\n", list->teachers[index]->name,
           list->teachers[index]->subject.name);

    list->currentSize++;
}

void displayStudentNames(StudentsList *list)
{
    printf("Students:\n");
    Student **students = list->students;
    for (int i = 0; i < list->currentSize; i++)
    {
        printf("%s\n", students[i]->name);
    }
}

void displayTeachers(TeachersList *list)
{
    printf("Teachers:\n");
    Teacher **teachers = list->teachers;
    for (int i = 0; i < list->currentSize; i++)
    {
        printf("%s teaches %s\n", teachers[i]->name, teachers[i]->subject.name);
    }
    printf("\n");
}

void addSubject2(StudentsList *list, char *studentName, char *subjectName, float gradeInput)
{
    printf("Inside addSubject,  student name: %s \n", studentName);

    int studentIndex = studentExists2(list, studentName);
    if (studentIndex >= 0)
    {
        int subjectIndex = subjectExistsForStudent(list->students[studentIndex], subjectName);
        if (subjectIndex == -1) // subject does not already exist, so add a new subject
        {
            int count = list->students[studentIndex]->subjectCount;
            if (count < DEFAULT_SUBJECTS_ARRAY_SIZE)
            {
                Subject *subjects = list->students[studentIndex]->subjects;
                subjects[count].name = subjectName;
                subjects[count].grade = gradeInput;
                list->students[studentIndex]->subjectCount++;
            }
            else
            {
                printf("Max amount of subjects for this student has been reached.\n");
                return;
            }
        }
        else
        {
            printf("Subject already exists for this student.\n");
        }
    }

    printf("\nSuccessfully added subject %s with grade %0.2f for student '%s' to the school database system 😄  \n\n", subjectName, gradeInput, studentName);
}

void displayMenuOptions()
{
    printf("\n ------------------------------------ \n");
    printf("Welcome to the School Management system \n");
    printf("Please enter an option from the list shown below: \n");
    printf("1). Add a new student, subject and grade \n");
    printf("2). Add subject and/or grade to an existing student \n");
    printf("3). Add a teacher and subject taught \n");
    printf("4). List all teachers and the subjects they teach  \n");
    printf("5). List students studying a particular subject \n");
    printf("6). List the teacher teaching a particular subject \n");
    printf("7). List the grades a particular student has achieved in a subject \n");
    printf("8). List the teachers teaching a particular student \n");
    printf("9). List the students taught by a particular teacher \n");
    printf("10). List the students taught at this school and optionally their subjects and grades \n");
    printf("0). EXIT \n");
    printf("------------------------------------ \n");
}

void displaySubject(Student *student)
{
    printf("Student: %s\n", student->name);
    if (student->subjectCount < 1)
    {
        printf("No registered subject for this student.\n\n");
        return;
    }
    for (int i = 0; i < student->subjectCount; i++)
    {
        Subject subject = student->subjects[i];
        printf("Studies %s with grade: %0.2f\n", subject.name, subject.grade);
    }
    printf("\n");
}

void userDisplayStudents(StudentsList *list)
{
    int response = getYesNoResponse("Would you like to also display the students' subjects and grades? (y/n): \n");
    printf("Students: \n");
    if (list->currentSize < 1)
    {
        printf("No registed students.\n");
        return;
    }
    for (int i = 0; i < list->currentSize; i++)
    {
        if (response > 0)
        {
            displaySubject(list->students[i]);
        }
        else
        {
            printf("%s\n", list->students[i]->name);
        }
    }
}

int main(void)
{

    int option = -1;

    // allocate initial arrays of pointers to student/teachers structs
    Student **students = allocateStudentsStructs();
    Teacher **teachers = allocateTeachersStructs();

    StudentsList *studentsList = malloc(sizeof(StudentsList) * 1);
    if (studentsList == NULL)
    {
        perror("Couldn't allocate students list.");
        return -1;
    }

    TeachersList *teachersList = malloc(sizeof(StudentsList) * 1);
    if (teachersList == NULL)
    {
        perror("Couldn't allocate teachers list.");
        return -1;
    }

    studentsList->students = students;
    studentsList->currentSize = 0;
    studentsList->maxSize = DEFAULT_STUDENTS_ARRAY_SIZE;

    teachersList->teachers = teachers;
    teachersList->currentSize = 0;
    teachersList->maxSize = DEFAULT_TEACHERS_ARRAY_SIZE;

    readTeachers(teachersList);
    printf("Number of teachers read from file: %d\n", teachersList->currentSize);

    while (option != QUIT)
    {
        displayMenuOptions();

        option = getPositiveInt();

        if (option < 0)
        {
            printf("Your provided input is not valid. Please try again.");
            continue;
        }

        switch (option)
        {
        case 1:
            if (userAddNewStudents2(studentsList) == -1)
            {
                return -1;
            }
            break;
        case 2:
            userAddSubjectToExistingStudent2(studentsList);
            break;
        case 3:
            if (userAddNewTeachers2(teachersList) == -1)
            {
                return -1;
            }
            break;
        case 4:
            printf("Not implemented. Sorry.\n");
            printf("Printing teachers instead.\n");
            displayTeachers(teachersList);
            break;
        case 5:
            userFindStudentsForSubject2(studentsList);
            break;
        case 6:
            userFindTeacherForSubject2(teachersList);
            break;
        case 7:
            userFindGradesForStudent2(studentsList);
            break;
        case 8:
            userFindTeachersForStudent2(studentsList, teachersList);
            break;
        case 9:
            userFindStudentsForTeacher2(studentsList, teachersList);
            break;
        case 10:
            userDisplayStudents(studentsList);
            break;
        case 0:
            printf("Saving...\n");
            if (save(studentsList, teachersList) == 1)
            {
                printf("Saved successfully.\n");
            }
            else
            {
                printf("Unable to save data.");
            }
            printf("Exiting program.\n");
            break;
        default:
            printf("Please enter a valid number from 0 - 10!");
            break;
        }
    }

    // TODO: FREE MEMORY HERE

    return 0;

    // addStudent2(studentsList, "Siam");
    // displayStudentNames(studentsList);
    // addStudent2(studentsList, "Tom");
    // displayStudentNames(studentsList);
    // addStudent2(studentsList, "Smith");
    // displayStudentNames(studentsList);
    // addStudent2(studentsList, "Smithx");
    // displayStudentNames(studentsList);
    // addSubject2(studentsList, "Siam", "Science", 100.00);
    // userDisplayStudents(studentsList);

    // userFindGradesForStudent2(studentsList);

    // userAddNewTeachers2(teachersList);
    // displayTeachers(teachersList);

    // userFindTeacherForSubject2(teachersList);

    // userFindTeachersForStudent2(studentsList, teachersList);
    // userFindStudentsForTeacher2(studentsList, teachersList);

    // save(studentsList, teachersList);
    // userAddNewStudents2(list);
    // userDisplayStudents(list);

    // userAddSubjectToExistingStudent2(list);
    // userDisplayStudents(list);

    // userFindStudentsForSubject2(list);

    // return 0;
}
