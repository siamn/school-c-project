#include <stdio.h>
#include <string.h>
#include "userinput.h"
#include "userfunctions.h"

void userAddSubject2(StudentsList *list, char *studentName)
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
        float grade = 0.0;

        printf("Please enter the subject name (%d out of %d subjects): ", (i + 1), numOfSubjects);
        char *subjectName = getLimitedLine(20);

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

        addSubject2(list, studentName, subjectName, grade);
    }
    printf("Successfully added all %d subjects for student '%s' \n", numOfSubjects, studentName);
}

int userAddNewStudents2(StudentsList *list)
{
    int numOfStudents = -1;

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
        // char *studentName = (char *)malloc(sizeof(char) * 20);
        printf("Please enter each student name, pressing the Enter key for each: \n");
        char *studentName = getLimitedLine(20);

        if (studentExists2(list, studentName) >= 0)
        {
            printf("\nThe student '%s' exists in the system already!  Exiting back to main menu ... \n", studentName);
            return 1;
        }

        addStudent2(list, studentName);

        userAddSubject2(list, studentName);
    }

    return 1;
}

void userAddSubjectToExistingStudent2(StudentsList *list)
{
    printf("Please enter an existing student to add a subject and/or grade \n");
    char *studentName = getLimitedLine(20);

    if (studentExists2(list, studentName) == -1)
    {
        printf("The student '%s' does not exist in the system. Exiting back to main menu ... \n", studentName);
        return;
    }

    printf("Student %s has been found! \n", studentName);

    userAddSubject2(list, studentName);
}

void userFindStudentsForSubject2(StudentsList *list)
{
    printf("Please enter the name of the subject you want to find a list of students for: \n");
    char *subject = getLimitedLine(20);
    if (list->currentSize < 1)
    {
        printf("No students registered.");
        return;
    }
    printf("Students studying %s:\n", subject);
    int studentsStudyingSubject = 0;
    for (int i = 0; i < list->currentSize; i++)
    {
        Student *student = list->students[i];
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

void userFindGradesForStudent2(StudentsList *list)
{
    printf("Please enter the name of the student you want to find grades for: \n");
    char *name = getLimitedLine(20);
    printf("Please enter the name of the subject you want to find the student's grades for: \n");
    char *subject = getLimitedLine(20);
    int studentIndex = studentExists2(list, name);
    if (studentIndex >= 0)
    {
        Student *student = list->students[studentIndex];
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

int userAddNewTeachers2(TeachersList *list)
{
    int numOfTeachers = 0;

    printf("Please enter how many teachers you would like to add \n");
    numOfTeachers = getPositiveInt(); // returns -1 if invalid input given

    // invalid number of teachers entered so return to main menu
    if (numOfTeachers < 0)
    {
        return -1;
    }

    for (int i = 0; i < numOfTeachers; i++)
    {
        printf("Please enter the teacher name (%d out of %d teachers): \n", (i + 1), numOfTeachers);
        char *teacherName = getLimitedLine(20);

        printf("Please enter the subject name (1 subject allowed): \n");
        char *subjectName = getLimitedLine(20);

        if (teacherExists2(list, teacherName) >= 0)
        {
            printf("\nThe teacher '%s' exists in the system already!  Exiting back to main menu ... \n", teacherName);
            return -1;
        }
        else if (teacherExistsForSubject2(list, subjectName) >= 0)
        {
            printf("\nA teacher already exists in the system for the subject '%s'.\nExiting back to main menu ... \n", subjectName);
            return -1;
        }

        addTeacher2(list, teacherName, subjectName);
    }

    return 1;
}

void userFindTeacherForSubject2(TeachersList *list)
{
    printf("Please enter the name of the subject you want to find the teacher for: \n");
    char *subject = getLimitedLine(20);

    printf("Teacher teaching subject %s:\n", subject);
    int count = 0;
    // added room for displaying multiple teachers if they teach the same subject in the future
    // even though current design supports 1 teacher per subject
    for (int i = 0; i < list->currentSize; i++)
    {
        Teacher *teacher = list->teachers[i];
        if (strcmp(subject, teacher->subject.name) == 0)
        {
            printf("%s\n", teacher->name);
            count++;
            // add return here if this behaviour is unwanted
        }
    }
    if (count < 1)
    {
        printf("No teacher is currently teacher this subject.\n");
    }
}

void userFindTeachersForStudent2(StudentsList *studentsList, TeachersList *teachersList)
{
    printf("Please enter the name of the student you want to find teachers for: \n");
    char *name = getLimitedLine(20);
    int studentIndex = studentExists2(studentsList, name);
    if (studentIndex >= 0)
    {
        Student *student = studentsList->students[studentIndex];
        printf("Teachers teaching %s:\n", student->name);
        for (int i = 0; i < student->subjectCount; i++)
        {
            int teacherIndex = teacherExistsForSubject2(teachersList, student->subjects[i].name);
            if (teacherIndex >= 0)
            {
                Teacher *teacher = teachersList->teachers[teacherIndex];
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

void userFindStudentsForTeacher2(StudentsList *studentsList, TeachersList *teachersList)
{
    printf("Please enter the name of the teacher you want to find students for: \n");
    char *name = getLimitedLine(20);
    int teacherIndex = teacherExists2(teachersList, name);
    int count = 0;
    if (teacherIndex >= 0)
    {
        Teacher *teacher = teachersList->teachers[teacherIndex];
        printf("Students taught by teacher %s:\n", teacher->name);
        char *subject = teacher->subject.name;
        for (int i = 0; i < studentsList->currentSize; i++)
        {
            Student *student = studentsList->students[i];
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
