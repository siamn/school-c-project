#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int saveStudent(FILE *file, Student *student);
int saveTeacher(FILE *file, Teacher *teacher);

// TODO: read teachers is fixed if I add back in a printf. There is likely something wrong with the memory allocation of
//  teachers and students arrays

// Returns total number of teachers added after reading from file.
int readTeachers(Teacher **teachers)
{
    // printf("here in read\n");
    const int teacherFields = 2;
    int numOfTeachers = 0;
    FILE *file = fopen("teachers.csv", "r");
    // printf("here in read2\n");
    if (file == NULL)
    {
        perror("Unable to open teachers file.\n");
        return numOfTeachers;
    }
    // printf("here in read3\n");
    char *line = NULL;
    size_t len = 0;
    ssize_t linelen;
    // printf("here in read4\n");
    while ((linelen = getline(&line, &len, file)) > 0)
    {
        // printf("Linelen: %zd\n", linelen);
        // printf("'%s'\n", line);
        //("Loop\n");
        char *teacherName = malloc(20);
        char *subjectName = malloc(20);
        int parsedFields = sscanf(line, "\"%19[^\"]\",\"%19[^\"]\"", teacherName, subjectName);
        // printf("Loop 2\n");
        if (parsedFields == teacherFields)
        {
            numOfTeachers = add_teacher(teachers, teacherName, subjectName, numOfTeachers);
        }
        else
        {
            perror("Failed to parse line successfully");
            return -1;
        }
    }

    free(line);
    fclose(file);

    return numOfTeachers;
}

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
    return fprintf(file, "\"%s\",\"%s\"\n", teacher->name, teacher->subject.subj_name);
}