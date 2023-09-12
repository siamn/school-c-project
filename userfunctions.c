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