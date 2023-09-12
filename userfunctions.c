#include <stdio.h>
#include <string.h>
#include "userinput.h"
#include "userfunctions.h"

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

        // userAddSubject(studentName);
    }

    return 1;
}