#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

/*
    Continuation of James Tam's School C Project by Siam Islam
*/

const int QUIT = 0;

typedef struct
{
    char *subj_name;
    float grade;
} Subject;

typedef struct
{
    char teacher_name[50];
    Subject subject;
} Teacher;

typedef struct
{
    char stud_name[50];
    int subject_count;
    Subject *subjects;
} Student;

// check if you can still access unallocated memory when adding students
// e.g. if num students set to 1, can still add more students and print them out.

Student **allocate_structs_stud(void)
{
    printf("Allocating memory for struct array. \n");

    const int NUM_OF_STUDENTS = 100;

    Student **students = (Student **)malloc(sizeof(*students) * NUM_OF_STUDENTS);

    if (students == NULL)
    {
        perror("Error allocating memory for struct array. \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_OF_STUDENTS; i++)
    {
        *(students + i) = (Student *)malloc(sizeof(Student));
        (*(students + i))->subjects = (Subject *)malloc(sizeof(Subject) * 10); // allocate space using malloc() for student subjects;

        if (*(students + i) == NULL)
        {
            perror("Error allocating memory for single struct");
            exit(EXIT_FAILURE);
        }
        if ((*(students + i))->subjects == NULL)
        {
            perror("Error allocating memory for subject pointer");
            exit(EXIT_FAILURE);
        }
    }

    return (students);
}

Teacher **allocate_structs_teach(void)
{
    printf("Allocating memory for teacher struct array. \n");

    const int NUM_OF_TEACHERS = 20;

    Teacher **teachers = (Teacher **)malloc(sizeof(*teachers) * NUM_OF_TEACHERS);

    if (teachers == NULL)
    {
        perror("Error allocating memory for struct array. \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_OF_TEACHERS; i++)
    {
        *(teachers + i) = (Teacher *)malloc(sizeof(Teacher));

        if (*(teachers + i) == NULL)
        {
            perror("Error allocating memory for single struct");
            exit(EXIT_FAILURE);
        }
    }

    return (teachers);
}

int exists(Student **students, char *studentName, int numOfStudents)
{
    for (int i = 0; i < numOfStudents; i++)
    {
        if (strcmp(students[i]->stud_name, studentName) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int add_student(Student **students, char *studentName)
{
    static int index = 0;
    printf("Adding student %s \n", studentName);

    char *ptr = (char *)malloc(sizeof(char) * 20);
    ptr = studentName;
    strcpy((*(students + index))->stud_name, studentName);

    for (int i = 0; i < sizeof(students); i++)
    {
        printf("The students array now looks like: %s \n", students[i]->stud_name);
    }

    // initialise the subjects that this particular student studies to 0
    (*(students + index))->subject_count = 0;

    index++;

    printf("\nSuccessfully added student '%s' to the school database system.  \n\n", studentName);

    return index;
}

void add_subject(Student **students, char *studentName, char *subjectName, float gradeInput)
{
    printf("Inside add_subject,  student name: %s \n", studentName);
    for (int i = 0; i < sizeof(students); i++)
    {
        if (strcasecmp(students[i]->stud_name, studentName) == 0)
        {
            int subject_count = (*(students + i))->subject_count;

            Subject *subjects = (Subject *)malloc(sizeof(Subject) * 10);
            subjects->subj_name = subjectName;
            subjects->grade = gradeInput;

            Student *currentStudent = students[i];
            Subject *student_subjects = currentStudent->subjects;
            student_subjects[subject_count] = *subjects;

            (*(students + i))->subject_count++;
            break;
        }
    }

    printf("\nSuccessfully added subject %s with grade %0.2f for student '%s' to the school database system 😄  \n\n", subjectName, gradeInput, studentName);
    // for (int i = 0; i < sizeof(students); i++) {
    //     printf("The students array now looks like: %s \n", students[i]->stud_name);
    // }
}

int add_teacher(Teacher **teachers, char *teacherName, char *subjectName)
{
    static int index = 0;
    printf("Adding teacher %s \n", teacherName);

    char *ptr = (char *)malloc(sizeof(char) * 20);
    ptr = teacherName;

    strcpy((*(teachers + index))->teacher_name, teacherName);
    (*(teachers + index))->subject.subj_name = subjectName;

    for (int i = 0; i < sizeof(teachers); i++)
    {
        printf("The teachers array now looks like: %s \n", teachers[i]->teacher_name);
    }

    index++;

    printf("\nSuccessfully added teacher '%s' teaching %s to the school database system.  \n\n", teacherName, subjectName);

    return index;
}

void print_students(Student **students, int numOfStudents)
{
    if (numOfStudents == 0)
    {
        printf("No students found.");
        return;
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        printf("%d) STUDENT: %s ", i, students[i]->stud_name);
        printf("studies ");

        for (int j = 0; j < students[i]->subject_count; j++)
        {
            printf("%s (%0.2f)", students[i]->subjects[j].subj_name, students[i]->subjects[j].grade);

            if (j < students[i]->subject_count - 1)
            {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void print_teachers(Teacher **teachers, int numOfTeachers)
{
    if (numOfTeachers == 0)
    {
        printf("No teachers found.");
        return;
    }

    for (int i = 0; i < numOfTeachers; i++)
    {
        printf("\n%d) Teacher '%s' teaches %s \n", (i + 1), teachers[i]->teacher_name, teachers[i]->subject.subj_name);
    }
}

void main_menu()
{
    printf("\n ------------------------------------ \n");
    printf("Welcome to the School Management system \n");
    printf("Please enter an option from the list shown below: \n");
    printf("1). Add a new student, subject and grade \n");
    printf("2). Add subject and/or grade to an existing student \n");
    printf("3). Add a teacher and subject taught \n");
    printf("4). Add a grade for an existing student \n");
    printf("5). List students studying a particular subject \n");
    printf("6). List the teacher teaching a particular subject \n");
    printf("7). List the grades a particular student has achieved in a subject \n");
    printf("0). EXIT \n");
    printf("------------------------------------ \n");
}

int option_1(Student **students, int totalStudents)
{
    long numOfStudents = -1;
    int numOfSubjects;

    char students_buf[10] = {0};
    char subjects_buf[4] = {0};

    int response;
    while (numOfStudents < 0)
    {
        printf("Please enter how many students you would like to register: \n");
        numOfStudents = getPositiveInt();
        if (numOfStudents == -1)
        {
            printf("Encountered an error. Try again.\n");
        }
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        char studentName[20];
        char *namePtr = studentName;
        printf("Please enter each student name, pressing the Enter key for each: \n");
        char *name = getLimitedLine(20);
        strcpy(namePtr, name);
        // fgets(studentName, 20, stdin);

        // printf("Entered studentName: %s \n", studentName);

        // studentName[strcspn(studentName, "\n")] = 0; // removing the new line here

        if (exists(students, studentName, totalStudents))
        {
            printf("\nThe student '%s' exists in the system already!  Exiting back to main menu ... \n", studentName);
            return totalStudents;
        }

        totalStudents = add_student(students, studentName);

        printf("Please enter how many subjects you would like to register for '%s'\n", studentName);
        numOfSubjects = getPositiveInt();

        for (int i = 0; i < numOfSubjects; i++)
        {
            char subjectName[20];
            char *subjectPtr = subjectName;
            float grade = 0.0;

            printf("Please enter the subject name (%d out of %d subjects): ", (i + 1), numOfSubjects);
            char *name = getLimitedLine(20);
            strcpy(subjectPtr, name);

            int response = getYesNoResponse("Would you like to enter a grade? (Y/N): \n");

            if (response > 0)
            {
                printf("\nPlease enter the grade for student %s (studying %s) \n", studentName, subjectName);
                grade = getFloat();
            }
            else
            {
                // printf("You have entered %s. No grade to be entered. \n", grade_option);
            }

            add_subject(students, studentName, subjectName, grade);
        }
    }

    return totalStudents;
}

void option_2(Student **students, int numOfStudents)
{
    int numOfSubjects;

    char *studentName = (char *)malloc(sizeof(char) * 20);
    printf("Please enter an existing student to add a subject and/or grade \n");
    scanf("%s", studentName);

    if (!exists(students, studentName, numOfStudents))
    {
        printf("The student '%s' does not exist in the system. Exiting back to main menu ... \n", studentName);
        return;
    }

    printf("Student %s has been found! \n", studentName);

    printf("Please enter how many subjects you would like to add for student '%s' \n", studentName);
    scanf("%d", &numOfSubjects);
    for (int i = 0; i < numOfSubjects; i++)
    {
        char *subjectName = (char *)malloc(sizeof(char) * 20);
        char *grade_option = (char *)malloc(sizeof(char) * 20);

        float grade = 0.0;

        printf("Please enter the subject name: ");
        scanf("%s", subjectName);

        printf("Would you like to enter a grade? (Y/N): ");
        scanf("%s", grade_option);

        if (strcasecmp(grade_option, "Y") == 0)
        {
            printf("Please enter the grade for student %s (studying %s) \n", studentName, subjectName);
            scanf("%f", &grade);
        }
        else
        {
            // printf("You have entered %s. No grade to be entered. \n", grade_option);
        }

        add_subject(students, studentName, subjectName, grade);
    }

    printf("Successfully added all %d subjects for student '%s' \n", numOfSubjects, studentName);
}

int option_3(Teacher **teachers, int totalTeachers)
{
    int numOfTeachers;

    printf("Please enter how many teachers you would like to add \n");
    scanf("%d", &numOfTeachers);

    for (int i = 0; i < numOfTeachers; i++)
    {
        char *teacherName = (char *)malloc(sizeof(char) * 20);
        char *subjectName = (char *)malloc(sizeof(char) * 20);

        printf("Please enter the teacher name (%d out of %d teachers): \n", (i + 1), numOfTeachers);
        scanf("%s", teacherName);

        printf("Please enter the subject name (1 subject allowed): \n");
        scanf("%s", subjectName);

        totalTeachers = add_teacher(teachers, teacherName, subjectName);
    }

    return totalTeachers;
}

int main(void)
{
    int numOfStudents;
    int numOfSubjects;

    Student **students = allocate_structs_stud();
    Teacher **teachers = allocate_structs_teach();

    int totalStudents = 0;
    int totalTeachers = 0;

    int option;

    while (option != QUIT)
    {
        main_menu();

        option = getPositiveInt();

        if (option < 0)
        {
            printf("Your provided input is not valid. Please try again.");
            continue;
        }

        switch (option)
        {
        case 1:
            totalStudents = option_1(students, totalStudents);
            ;
            break;
        case 2:
            option_2(students, totalStudents);
            break;
        case 3:
            totalTeachers = option_3(teachers, totalTeachers);
            break;
        case 4:
            printf("Not implemented. Sorry.\n");
            break;
        case 5:
            printf("Total number of students: %d \n", totalStudents);
            print_students(students, totalStudents);
            break;
        case 6:
            print_teachers(teachers, totalTeachers);
            break;
        case 7:
            printf("Not implemented. Sorry.\n");
            break;
        case 8:
            printf("Not implemented. Sorry.\n");
            break;
        default:
            printf("Please enter a valid number from 0 - 9!");
            break;
        }
    }

    return 0;
}

// add_subject(students, "James", "Chemistry", 95.0);
// free(students);
// free(studentNames);