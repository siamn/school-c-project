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
#define DEFAULT_SUBJECTS_ARRAY_SIZE 2

#define MAX_STUDENTS_ARRAY_SIZE 4
#define MAX_TEACHERS_ARRAY_SIZE 4

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

int studentExists(StudentsList *list, char *studentName)
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

int teacherExists(TeachersList *list, char *teacher)
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

int teacherExistsForSubject(TeachersList *list, char *subject)
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

        if (newMaxSize > MAX_STUDENTS_ARRAY_SIZE)
        {
            if (maxSize < MAX_STUDENTS_ARRAY_SIZE)
            {
                newMaxSize = MAX_STUDENTS_ARRAY_SIZE;
            }
            else
            {
                printf("Max array size has been reached. Memory not expanded.\n");
                return maxSize;
            }
        }

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

        if (newMaxSize > MAX_TEACHERS_ARRAY_SIZE)
        {
            if (maxSize < MAX_TEACHERS_ARRAY_SIZE)
            {
                newMaxSize = MAX_TEACHERS_ARRAY_SIZE;
            }
            else
            {
                printf("Max array size has been reached. Memory not expanded.\n");
                return maxSize;
            }
        }

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

int addStudent(StudentsList *studentsList, char *studentName)
{
    int index = studentsList->currentSize;
    printf("Adding student %s \n", studentName);
    studentsList->maxSize = expandStudentsStruct(&studentsList->students, studentsList->currentSize, studentsList->maxSize);

    if (studentsList->currentSize >= studentsList->maxSize)
    {
        printf("No more space available to add students.\n");
        return -1;
    }

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

void addTeacher(TeachersList *list, char *teacherName, char *subjectName)
{
    int index = list->currentSize;
    printf("Adding teacher %s \n", teacherName);
    list->maxSize = expandTeachersStruct(&list->teachers, index, list->maxSize);

    if (list->currentSize >= list->maxSize)
    {
        printf("No more space available to add students.\n");
        return;
    }

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
    printf("\nTeachers:\n");
    Teacher **teachers = list->teachers;
    for (int i = 0; i < list->currentSize; i++)
    {
        printf("%s teaches %s\n", teachers[i]->name, teachers[i]->subject.name);
    }
    printf("\n");
}

void addSubject(StudentsList *list, char *studentName, char *subjectName, float gradeInput)
{
    printf("Inside addSubject,  student name: %s \n", studentName);

    int studentIndex = studentExists(list, studentName);
    if (studentIndex >= 0)
    {
        printf("Student found.\n");
        if (list->students[studentIndex]->subjectCount >= DEFAULT_SUBJECTS_ARRAY_SIZE)
        {
            printf("Max number of subjects already reached for this student.\n");
            return;
        }
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

void freeStudentsList(StudentsList *list)
{
    for (int i = 0; i < list->maxSize; i++)
    {
        // if not NULL, then memory for subjects was allocated successfully
        // so this must also be freed
        if (list->students[i]->subjects != NULL)
        {
            for (int j = 0; j < DEFAULT_SUBJECTS_ARRAY_SIZE; j++)
            {
                free(list->students[i]->subjects[j].name);
            }
            free(list->students[i]->subjects);
        }
        free(list->students[i]->name);
        free(list->students[i]);
    }
    free(list->students);
    free(list);
}

void freeTeachersList(TeachersList *list)
{
    for (int i = 0; i < list->maxSize; i++)
    {
        free(list->teachers[i]->name);
        free(list->teachers[i]->subject.name);
        free(list->teachers[i]);
    }
    free(list->teachers);
    free(list);
}

void freeMemory(StudentsList *studentsList, TeachersList *teachersList)
{
    freeTeachersList(teachersList);
    freeStudentsList(studentsList);
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
            userAddNewStudents(studentsList);
            break;
        case 2:
            userAddSubjectToExistingStudent(studentsList);
            break;
        case 3:
            userAddNewTeachers(teachersList);
            break;
        case 4:
            displayTeachers(teachersList);
            break;
        case 5:
            userFindStudentsForSubject(studentsList);
            break;
        case 6:
            userFindTeacherForSubject(teachersList);
            break;
        case 7:
            userFindGradesForStudent(studentsList);
            break;
        case 8:
            userFindTeachersForStudent(studentsList, teachersList);
            break;
        case 9:
            userFindStudentsForTeacher(studentsList, teachersList);
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

    // FREE MEMORY HERE
    freeMemory(studentsList, teachersList);

    return 0;

    // addStudent(studentsList, "Siam");
    // displayStudentNames(studentsList);
    // addStudent(studentsList, "Tom");
    // displayStudentNames(studentsList);
    // addStudent(studentsList, "Smith");
    // displayStudentNames(studentsList);
    // addStudent(studentsList, "Smithx");
    // displayStudentNames(studentsList);
    // addSubject(studentsList, "Siam", "Science", 100.00);
    // userDisplayStudents(studentsList);

    // userFindGradesForStudent(studentsList);

    // userAddNewTeachers(teachersList);
    // displayTeachers(teachersList);

    // userFindTeacherForSubject(teachersList);

    // userFindTeachersForStudent(studentsList, teachersList);
    // userFindStudentsForTeacher(studentsList, teachersList);

    // save(studentsList, teachersList);
    // userAddNewStudents(list);
    // userDisplayStudents(list);

    // userAddSubjectToExistingStudent(list);
    // userDisplayStudents(list);

    // userFindStudentsForSubject(list);

    // return 0;
}
