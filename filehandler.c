#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int saveStudent(FILE *file, Student *student);

int save(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers)
{
    FILE *file = fopen("students.csv", "w"); // open file in write mode (creates new file if it doesn't already exist)

    if (file == NULL)
    {
        perror("Unable to open the file\n");
        return -1;
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        if (saveStudent(file, students[i]) == -1)
        {
            return -1;
        }
    }

    return 1;
}

int saveStudent(FILE *file, Student *student)
{
    if (file == NULL)
    {
        perror("Could not open file.\n");
        return -1;
    }

    fprintf(file, "\"%s\",%d,", student->stud_name, student->subject_count);
    for (int i = 0; i < student->subject_count; i++)
    {
        // print each subject for the student at the end
        // (after the first two fields, name and subject count) consecutively
        Subject subject = student->subjects[i];
        fprintf(file, "\"%s\",%0.2f", subject.subj_name, subject.grade);

        if (i < student->subject_count - 1)
        {
            fprintf(file, ","); // print comma if not last field in list of subjects
        }
    }
    // new line for new student
    fprintf(file, "\n");

    return 0;
}