#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

/*
    Continuation of James Tam's School C Project by Siam Islam
*/

#define DEFAULT_STUDENTS_ARRAY_SIZE 2
#define DEFAULT_TEACHERS_ARRAY_SIZE 20
#define DEFAULT_SUBJECTS_ARRAY_SIZE 20

const int QUIT = 0;

// check if you can still access unallocated memory when adding students
// e.g. if num students set to 1, can still add more students and print them out.

/* TODO: Can currently add duplicate subjects
e.g. add student with subject Math with no grade using option 1
then use option 2 to add grade for same subject by typing Math for same student
another math subject is added rather than replacing the existing math subject */

Student **allocate_structs_stud(void)
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

Teacher **allocate_structs_teach(void)
{
    printf("Allocating memory for teacher struct array. \n");

    const int NUM_OF_TEACHERS = 20;

    Teacher **teachers = (Teacher **)malloc(sizeof(Teacher *) * NUM_OF_TEACHERS);

    if (teachers == NULL)
    {
        perror("Error allocating memory for struct array. \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_OF_TEACHERS; i++)
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

int exists(Student **students, char *studentName, int numOfStudents)
{
    for (int i = 0; i < numOfStudents; i++)
    {
        if (strcmp(students[i]->stud_name, studentName) == 0)
        {
            return i;
        }
    }
    return -1;
}

int exists_subject(Student *student, char *subject)
{
    for (int i = 0; i < student->subject_count; i++)
    {
        if (strcmp(subject, student->subjects[i].subj_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int exists_teacher(Teacher **teachers, int numOfTeachers, char *teacher)
{
    for (int i = 0; i < numOfTeachers; i++)
    {
        if (strcmp(teachers[i]->teacher_name, teacher) == 0)
        {
            return i;
        }
    }
    return -1;
}

int exists_teacher_for_subject(Teacher **teachers, int numOfTeachers, char *subject)
{
    for (int i = 0; i < numOfTeachers; i++)
    {
        Teacher *teacher = teachers[i];
        if (strcmp(subject, teacher->subject.subj_name) == 0)
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
        printf("here\n");

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

int add_student(Student **students, char *studentName, int numOfStudents)
{
    int index = numOfStudents;
    printf("Adding student %s \n", studentName);

    students[index]->stud_name = studentName;

    students[index]->subjects = (Subject *)malloc(sizeof(Subject) * DEFAULT_SUBJECTS_ARRAY_SIZE); // allocate space using malloc() for student subjects;
    if (students[index]->subjects == NULL)
    {
        perror("Error allocating memory for subject pointer");
        return -1;
    }
    // initialise the subjects that this particular student studies to 0
    students[index]->subject_count = 0;

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

int add_teacher(Teacher **teachers, char *teacherName, char *subjectName, int numOfTeachers)
{
    int index = numOfTeachers;
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
    printf("8). List the teachers teaching a particular student \n");
    printf("9). List the students taught by a particular teacher \n");
    printf("0). EXIT \n");
    printf("------------------------------------ \n");
}

void user_add_subject(Student **students, char *studentName)
{
    int numOfSubjects = -1;
    while (numOfSubjects < 0)
    {
        printf("Please enter how many subjects you would like to register for '%s'\n", studentName);
        numOfSubjects = getPositiveInt();
        if (numOfSubjects == -1)
        {
            printf("Encountered an error. Try again.\n");
        }
    }

    for (int i = 0; i < numOfSubjects; i++)
    {
        char *subjectName = (char *)malloc(sizeof(char) * 20);
        float grade = 0.0;

        printf("Please enter the subject name (%d out of %d subjects): ", (i + 1), numOfSubjects);
        char *name = getLimitedLine(20);
        strcpy(subjectName, name);

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
    printf("Successfully added all %d subjects for student '%s' \n", numOfSubjects, studentName);
}

int option_1(Student **students, int totalStudents)
{
    long numOfStudents = -1;

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
        char *studentName = (char *)malloc(sizeof(char) * 20);
        printf("Please enter each student name, pressing the Enter key for each: \n");
        char *name = getLimitedLine(20);
        strcpy(studentName, name);
        // fgets(studentName, 20, stdin);

        // printf("Entered studentName: %s \n", studentName);

        // studentName[strcspn(studentName, "\n")] = 0; // removing the new line here

        if (exists(students, studentName, totalStudents) >= 0)
        {
            printf("\nThe student '%s' exists in the system already!  Exiting back to main menu ... \n", studentName);
            return totalStudents;
        }

        totalStudents = add_student(students, studentName, totalStudents);

        user_add_subject(students, studentName);
    }

    return totalStudents;
}

void option_2(Student **students, int numOfStudents)
{
    char *studentName = (char *)malloc(sizeof(char) * 20);
    printf("Please enter an existing student to add a subject and/or grade \n");
    char *name = getLimitedLine(20);
    strcpy(studentName, name);

    if (exists(students, studentName, numOfStudents) == -1)
    {
        printf("The student '%s' does not exist in the system. Exiting back to main menu ... \n", studentName);
        return;
    }

    printf("Student %s has been found! \n", studentName);

    user_add_subject(students, studentName);
}

int option_3(Teacher **teachers, int totalTeachers)
{
    int numOfTeachers;

    printf("Please enter how many teachers you would like to add \n");
    numOfTeachers = getPositiveInt();

    for (int i = 0; i < numOfTeachers; i++)
    {
        char *teacherName = (char *)malloc(sizeof(char) * 20);
        char *subjectName = (char *)malloc(sizeof(char) * 20);

        printf("Please enter the teacher name (%d out of %d teachers): \n", (i + 1), numOfTeachers);
        teacherName = getLimitedLine(20);

        printf("Please enter the subject name (1 subject allowed): \n");
        subjectName = getLimitedLine(20);

        if (exists_teacher(teachers, totalTeachers, teacherName) >= 0)
        {
            printf("\nThe teacher '%s' exists in the system already!  Exiting back to main menu ... \n", teacherName);
            return totalTeachers;
        }
        else if (exists_teacher_for_subject(teachers, totalTeachers, subjectName) >= 0)
        {
            printf("\nA teacher already exists in the system for the subject '%s'.\nExiting back to main menu ... \n", subjectName);
            return totalTeachers;
        }

        totalTeachers = add_teacher(teachers, teacherName, subjectName, totalTeachers);
    }

    return totalTeachers;
}

void option_5(Student **students, int numOfStudents)
{
    printf("Please enter the name of the subject you want to find a list of students for: \n");
    char *subject = getLimitedLine(20);
    if (numOfStudents == 0)
    {
        printf("No students registered.");
        return;
    }
    printf("Students studying %s:\n", subject);
    int studentsStudyingSubject = 0;
    for (int i = 0; i < numOfStudents; i++)
    {
        Student *student = students[i];
        if (exists_subject(student, subject) >= 0)
        {
            printf("%s\n", student->stud_name);
            studentsStudyingSubject += 1;
        }
    }
    if (studentsStudyingSubject < 1)
    {
        printf("No registered student is currently studying this subject.\n");
    }
}

void option_6(Teacher **teachers, int numOfTeachers)
{
    printf("Please enter the name of the subject you want to find the teacher for: \n");
    char *subject = getLimitedLine(20);

    printf("Teacher studying subject %s:\n", subject);
    int count = 0;
    for (int i = 0; i < numOfTeachers; i++)
    {
        Teacher *teacher = teachers[i];
        if (strcmp(subject, teacher->subject.subj_name) == 0)
        {
            printf("%s", teacher->teacher_name);
            count++;
        }
    }
    if (count < 1)
    {
        printf("No teacher is currently teacher this subject.\n");
    }
}

void option_7(Student **students, int numOfStudents)
{
    printf("Please enter the name of the student you want to find grades for: \n");
    char *name = getLimitedLine(20);
    printf("Please enter the name of the subject you want to find the student's grades for: \n");
    char *subject = getLimitedLine(20);
    int studentIndex = exists(students, name, numOfStudents);
    if (studentIndex >= 0)
    {
        Student *student = students[studentIndex];
        int subjectIndex = exists_subject(student, subject);
        if (subjectIndex >= 0)
        {
            printf("%s's grade for subject %s: %0.2f\n", student->stud_name,
                   student->subjects[subjectIndex].subj_name,
                   student->subjects[subjectIndex].grade);
        }
        else
        {
            printf("Could not find subject %s for this student.\n", subject);
        }
    }
    else
    {
        printf("Could not find this student %s in our database.\n", name);
    }
}

void option_8(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers)
{
    printf("Please enter the name of the student you want to find teachers for: \n");
    char *name = getLimitedLine(20);
    int studentIndex = exists(students, name, numOfStudents);
    if (studentIndex >= 0)
    {
        Student *student = students[studentIndex];
        printf("Teachers teaching %s:\n", student->stud_name);
        for (int i = 0; i < student->subject_count; i++)
        {
            int teacherIndex = exists_teacher_for_subject(teachers, numOfTeachers, student->subjects[i].subj_name);
            if (teacherIndex >= 0)
            {
                Teacher *teacher = teachers[teacherIndex];
                printf("%s teaches %s\n", teacher->teacher_name, student->subjects[i].subj_name);
            }
            else
            {
                printf("No teacher found for subject %s\n", student->subjects[i].subj_name);
            }
        }
    }
    else
    {
        printf("Could not find this student %s in our database.\n", name);
    }
}

void option_9(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers)
{
    printf("Please enter the name of the teacher you want to find students for: \n");
    char *name = getLimitedLine(20);
    int teacherIndex = exists_teacher(teachers, numOfTeachers, name);
    int count = 0;
    if (teacherIndex >= 0)
    {
        Teacher *teacher = teachers[teacherIndex];
        printf("Students taught by teacher %s:\n", teacher->teacher_name);
        char *subject = teacher->subject.subj_name;
        for (int i = 0; i < numOfStudents; i++)
        {
            Student *student = students[i];
            int studentIndex = exists_subject(student, subject);
            if (studentIndex >= 0)
            {
                printf("%s\n", student->stud_name);
                count++;
            }
        }
        if (count < 1)
        {
            printf("No students found.\n");
        }
    }
    else
    {
        printf("Could not find this teacher %s in our database.\n", name);
    }
}

int main(void)
{
    int numOfStudents;
    int numOfSubjects;

    Student **students = allocate_structs_stud();
    Teacher **teachers = allocate_structs_teach();

    int totalStudents = 0;
    int totalTeachers = 0;
    int maxStudentsArraySize = DEFAULT_STUDENTS_ARRAY_SIZE;
    int option;

    totalTeachers = readTeachers(teachers);

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
            maxStudentsArraySize = expandStudentsStruct(&students, totalStudents, maxStudentsArraySize);
            totalStudents = option_1(students, totalStudents);
            if (totalStudents == -1)
            {
                return -1;
            }
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
            printf("Actual: \n\n");
            option_5(students, totalStudents);
            break;
        case 6:
            print_teachers(teachers, totalTeachers);
            printf("Actual: \n\n");
            option_6(teachers, totalTeachers);
            break;
        case 7:
            option_7(students, totalStudents);
            break;
        case 8:
            option_8(students, totalStudents, teachers, totalTeachers);
            break;
        case 9:
            option_9(students, totalStudents, teachers, totalTeachers);
            break;
        case 0:
            printf("Attempting save...\n");
            if (save(students, totalStudents, teachers, totalTeachers) == 1)
            {
                printf("Saved successfully.\n");
            }
            printf("Exiting program.\n");
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