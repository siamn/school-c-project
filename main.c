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
#define DEFAULT_TEACHERS_ARRAY_SIZE 10
#define DEFAULT_SUBJECTS_ARRAY_SIZE 20

const int QUIT = 0;

Student **students;
Teacher **teachers;

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

int studentExists(char *studentName, int numOfStudents)
{
    for (int i = 0; i < numOfStudents; i++)
    {
        if (strcmp(students[i]->name, studentName) == 0)
        {
            return i;
        }
    }
    return -1;
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

int teacherExists(int numOfTeachers, char *teacher)
{
    for (int i = 0; i < numOfTeachers; i++)
    {
        if (strcmp(teachers[i]->name, teacher) == 0)
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

int teacherExistsForSubject(int numOfTeachers, char *subject)
{
    for (int i = 0; i < numOfTeachers; i++)
    {
        Teacher *teacher = teachers[i];
        if (strcmp(subject, teacher->subject.name) == 0)
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

int addStudent(char *studentName, int numOfStudents)
{
    static int maxArraySize = DEFAULT_STUDENTS_ARRAY_SIZE;
    int index = numOfStudents;
    printf("Adding student %s \n", studentName);
    maxArraySize = expandStudentsStruct(&students, numOfStudents, maxArraySize);

    students[index]->name = studentName;

    students[index]->subjects = (Subject *)malloc(sizeof(Subject) * DEFAULT_SUBJECTS_ARRAY_SIZE); // allocate space using malloc() for student subjects;
    if (students[index]->subjects == NULL)
    {
        perror("Error allocating memory for subject pointer");
        return -1;
    }
    // initialise the subjects that this particular student studies to 0
    students[index]->subjectCount = 0;

    index++;

    printf("\nSuccessfully added student '%s' to the school database system.  \n\n", studentName);

    return index;
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

void displayStudents2(StudentsList *list)
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

void addSubject(char *studentName, char *subjectName, float gradeInput)
{
    printf("Inside addSubject,  student name: %s \n", studentName);
    for (int i = 0; i < sizeof(students); i++)
    {
        if (strcasecmp(students[i]->name, studentName) == 0)
        {
            int subjectCount = (*(students + i))->subjectCount;

            Subject *subjects = (Subject *)malloc(sizeof(Subject) * 10);
            subjects->name = subjectName;
            subjects->grade = gradeInput;

            Student *currentStudent = students[i];
            Subject *student_subjects = currentStudent->subjects;
            student_subjects[subjectCount] = *subjects;

            (*(students + i))->subjectCount++;
            break;
        }
    }

    printf("\nSuccessfully added subject %s with grade %0.2f for student '%s' to the school database system 😄  \n\n", subjectName, gradeInput, studentName);
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

int addTeacher(char *teacherName, char *subjectName, int numOfTeachers)
{
    static int maxArraySize = DEFAULT_TEACHERS_ARRAY_SIZE;
    int index = numOfTeachers;
    printf("Adding teacher %s \n", teacherName);
    maxArraySize = expandTeachersStruct(&teachers, numOfTeachers, maxArraySize);

    teachers[index]->name = teacherName;
    teachers[index]->subject.name = subjectName;

    printf("\nSuccessfully added teacher '%s' teaching %s to the school database system.  \n\n", teachers[index]->name,
           teachers[index]->subject.name);

    index++;

    return index;
}

void printStudents(int numOfStudents)
{
    if (numOfStudents == 0)
    {
        printf("No students found.");
        return;
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        printf("%d) STUDENT: %s ", i, students[i]->name);
        printf("studies ");

        for (int j = 0; j < students[i]->subjectCount; j++)
        {
            printf("%s (%0.2f)", students[i]->subjects[j].name, students[i]->subjects[j].grade);

            if (j < students[i]->subjectCount - 1)
            {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void printTeachers(int numOfTeachers)
{
    if (numOfTeachers == 0)
    {
        printf("No teachers found.");
        return;
    }

    for (int i = 0; i < numOfTeachers; i++)
    {
        printf("\n%d) Teacher '%s' teaches %s \n", (i + 1), teachers[i]->name, teachers[i]->subject.name);
    }
}

void displayMenuOptions()
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
    printf("10). List the students taught at this school and optionally their subjects and grades. \n");
    printf("0). EXIT \n");
    printf("------------------------------------ \n");
}

void userAddSubject(char *studentName)
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

        addSubject(studentName, subjectName, grade);
    }
    printf("Successfully added all %d subjects for student '%s' \n", numOfSubjects, studentName);
}

int userAddNewStudents(int totalStudents)
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

        if (studentExists(studentName, totalStudents) >= 0)
        {
            printf("\nThe student '%s' exists in the system already!  Exiting back to main menu ... \n", studentName);
            return totalStudents;
        }

        totalStudents = addStudent(studentName, totalStudents);

        userAddSubject(studentName);
    }

    return totalStudents;
}

void userAddSubjectToExistingStudent(int numOfStudents)
{
    char *studentName = (char *)malloc(sizeof(char) * 20);
    printf("Please enter an existing student to add a subject and/or grade \n");
    char *name = getLimitedLine(20);
    strcpy(studentName, name);

    if (studentExists(studentName, numOfStudents) == -1)
    {
        printf("The student '%s' does not exist in the system. Exiting back to main menu ... \n", studentName);
        return;
    }

    printf("Student %s has been found! \n", studentName);

    userAddSubject(studentName);
}

int userAddNewTeachers(int totalTeachers)
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

        if (teacherExists(totalTeachers, teacherName) >= 0)
        {
            printf("\nThe teacher '%s' exists in the system already!  Exiting back to main menu ... \n", teacherName);
            return totalTeachers;
        }
        else if (teacherExistsForSubject(totalTeachers, subjectName) >= 0)
        {
            printf("\nA teacher already exists in the system for the subject '%s'.\nExiting back to main menu ... \n", subjectName);
            return totalTeachers;
        }

        totalTeachers = addTeacher(teacherName, subjectName, totalTeachers);
    }

    return totalTeachers;
}

void userFindStudentsForSubject(int numOfStudents)
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
        if (subjectExistsForStudent(student, subject) >= 0)
        {
            printf("%s\n", student->name);
            studentsStudyingSubject += 1;
        }
    }
    if (studentsStudyingSubject < 1)
    {
        printf("No registered student is currently studying this subject.\n");
    }
}

void userFindTeacherForSubject(int numOfTeachers)
{
    printf("Please enter the name of the subject you want to find the teacher for: \n");
    char *subject = getLimitedLine(20);

    printf("Teacher teaching subject %s:\n", subject);
    int count = 0;
    for (int i = 0; i < numOfTeachers; i++)
    {
        Teacher *teacher = teachers[i];
        if (strcmp(subject, teacher->subject.name) == 0)
        {
            printf("%s\n", teacher->name);
            count++;
        }
    }
    if (count < 1)
    {
        printf("No teacher is currently teacher this subject.\n");
    }
}

void userFindGradesForStudent(int numOfStudents)
{
    printf("Please enter the name of the student you want to find grades for: \n");
    char *name = getLimitedLine(20);
    printf("Please enter the name of the subject you want to find the student's grades for: \n");
    char *subject = getLimitedLine(20);
    int studentIndex = studentExists(name, numOfStudents);
    if (studentIndex >= 0)
    {
        Student *student = students[studentIndex];
        int subjectIndex = subjectExistsForStudent(student, subject);
        if (subjectIndex >= 0)
        {
            printf("%s's grade for subject %s: %0.2f\n", student->name,
                   student->subjects[subjectIndex].name,
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

void userFindTeachersForStudent(int numOfStudents, int numOfTeachers)
{
    printf("Please enter the name of the student you want to find teachers for: \n");
    char *name = getLimitedLine(20);
    int studentIndex = studentExists(name, numOfStudents);
    if (studentIndex >= 0)
    {
        Student *student = students[studentIndex];
        printf("Teachers teaching %s:\n", student->name);
        for (int i = 0; i < student->subjectCount; i++)
        {
            int teacherIndex = teacherExistsForSubject(numOfTeachers, student->subjects[i].name);
            if (teacherIndex >= 0)
            {
                Teacher *teacher = teachers[teacherIndex];
                printf("%s teaches %s\n", teacher->name, student->subjects[i].name);
            }
            else
            {
                printf("No teacher found for subject %s\n", student->subjects[i].name);
            }
        }
    }
    else
    {
        printf("Could not find this student %s in our database.\n", name);
    }
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

void displayStudents(int numOfStudents)
{
    int response = getYesNoResponse("Would you like to also display the students' subjects and grades? (y/n): \n");
    printf("Students: \n");
    if (numOfStudents < 1)
    {
        printf("No registed students.\n");
        return;
    }
    for (int i = 0; i < numOfStudents; i++)
    {
        if (response > 0)
        {
            displaySubject(students[i]);
        }
        else
        {
            printf("%s\n", students[i]->name);
        }
    }
}

void displayStudents3(StudentsList *list)
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

void userFindStudentsForTeacher(int numOfStudents, int numOfTeachers)
{
    printf("Please enter the name of the teacher you want to find students for: \n");
    char *name = getLimitedLine(20);
    int teacherIndex = teacherExists(numOfTeachers, name);
    int count = 0;
    if (teacherIndex >= 0)
    {
        Teacher *teacher = teachers[teacherIndex];
        printf("Students taught by teacher %s:\n", teacher->name);
        char *subject = teacher->subject.name;
        for (int i = 0; i < numOfStudents; i++)
        {
            Student *student = students[i];
            int studentIndex = subjectExistsForStudent(student, subject);
            if (studentIndex >= 0)
            {
                printf("%s\n", student->name);
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
    // initialize requried variables
    int totalStudents = 0;
    int totalTeachers = 0;
    int maxStudentsArraySize = DEFAULT_STUDENTS_ARRAY_SIZE;
    int option = -1;

    // allocate initial arrays of pointers to student/teachers structs
    students = allocateStudentsStructs();
    teachers = allocateTeachersStructs();

    // load teachers from file
    // totalTeachers = readTeachers();
    printf("Number of teachers read from file: %d\n", totalTeachers);

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

    addStudent2(studentsList, "Siam");
    displayStudents2(studentsList);
    addStudent2(studentsList, "Tom");
    displayStudents2(studentsList);
    addStudent2(studentsList, "Smith");
    displayStudents2(studentsList);
    addStudent2(studentsList, "Smithx");
    displayStudents2(studentsList);
    addSubject2(studentsList, "Siam", "Science", 100.00);
    displayStudents3(studentsList);

    userFindGradesForStudent2(studentsList);

    userAddNewTeachers2(teachersList);
    displayTeachers(teachersList);

    userFindTeacherForSubject2(teachersList);

    userFindTeachersForStudent2(studentsList, teachersList);
    userFindStudentsForTeacher2(studentsList, teachersList);

    save(studentsList, teachersList);
    // userAddNewStudents2(list);
    // displayStudents3(list);

    // userAddSubjectToExistingStudent2(list);
    // displayStudents3(list);

    // userFindStudentsForSubject2(list);

    // while (option != QUIT)
    // {
    //     displayMenuOptions();

    //     option = getPositiveInt();

    //     if (option < 0)
    //     {
    //         printf("Your provided input is not valid. Please try again.");
    //         continue;
    //     }

    //     switch (option)
    //     {
    //     case 1:
    //         totalStudents = userAddNewStudents(totalStudents);
    //         if (totalStudents == -1)
    //         {
    //             return -1;
    //         }
    //         break;
    //     case 2:
    //         userAddSubjectToExistingStudent(totalStudents);
    //         break;
    //     case 3:
    //         totalTeachers = userAddNewTeachers(totalTeachers);
    //         break;
    //     case 4:
    //         printf("Not implemented. Sorry.\n");
    //         break;
    //     case 5:
    //         printf("Total number of students: %d \n", totalStudents);
    //         printStudents(totalStudents);
    //         printf("Actual: \n\n");
    //         userFindStudentsForSubject(totalStudents);
    //         break;
    //     case 6:
    //         printTeachers(totalTeachers);
    //         printf("Actual: \n\n");
    //         userFindTeacherForSubject(totalTeachers);
    //         break;
    //     case 7:
    //         userFindGradesForStudent(totalStudents);
    //         break;
    //     case 8:
    //         userFindTeachersForStudent(totalStudents, totalTeachers);
    //         break;
    //     case 9:
    //         userFindStudentsForTeacher(totalStudents, totalTeachers);
    //         break;
    //     case 10:
    //         displayStudents(totalStudents);
    //         break;
    //     case 0:
    //         printf("Attempting save...\n");
    //         if (save(students, totalStudents, teachers, totalTeachers) == 1)
    //         {
    //             printf("Saved successfully.\n");
    //         }
    //         printf("Exiting program.\n");
    //         break;
    //     default:
    //         printf("Please enter a valid number from 0 - 10!");
    //         break;
    //     }
    // }

    // TODO: FREE MEMORY HERE

    return 0;
}
