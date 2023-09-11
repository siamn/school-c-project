#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int saveStudent(FILE *file, Student *student);
int saveTeacher(FILE *file, Teacher *teacher);

int save(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers)
{
    FILE *studentsFile = fopen("students.csv", "w"); // open file in write mode (creates new file if it doesn't already exist)
    FILE *teachersFile = fopen("teachers.csv", "w");
    if (studentsFile == NULL || teachersFile == NULL)
    {
        perror("Unable to open a required file\n");
        return -1;
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        if (saveStudent(studentsFile, students[i]) == -1)
        {
            return -1;
        }
    }

    for (int i = 0; i < numOfTeachers; i++)
    {
        if (saveTeacher(teachersFile, teachers[i]) == -1)
        {
            return -1;
        }
    }

    fclose(studentsFile);
    fclose(teachersFile);
    return 1;
}

// TODO: Maybe add check for return value of fprintf (same as in saveTeacher)
int saveStudent(FILE *file, Student *student)
{
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

int saveTeacher(FILE *file, Teacher *teacher)
{
    // fprintf returns a negative value if an error occurs
    return fprintf(file, "\"%s\",\"%s\"\n", teacher->teacher_name, teacher->subject.subj_name);
}