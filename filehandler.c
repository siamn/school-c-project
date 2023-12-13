#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

/*
    (Bonus feature - persiting data)
    Code in this file needs to be tested more
    and requires additional error checking.
*/

const char *teachersFileName = "teachers.csv";
const char *studentsFileName = "students.csv";

int saveStudent(FILE *file, Student *student);
int saveTeacher(FILE *file, Teacher *teacher);

// Returns total number of teachers added after reading from file.
int readTeachers(TeachersList *list)
{
    // printf("here in read\n");
    const int teacherFields = 2;
    int numOfTeachers = 0;
    FILE *file = fopen(teachersFileName, "r");
    // printf("here in read2\n");
    if (file == NULL)
    {
        perror("Unable to open teachers file.\n");
        return -1;
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
        char *teacherName = malloc(MAX_NAME_LENGTH);
        char *subjectName = malloc(MAX_SUBJECT_LENGTH);
        // use STRINGIFY HERE TO TURN MAGIC NUMBER 19 -> MAX_NAME_LENGTH - 1, and
        // MAX_SUBJECT_LENGTH -1
        int parsedFields = sscanf(line, "\"%19[^\"]\",\"%19[^\"]\"", teacherName, subjectName);
        // printf("Loop 2\n");
        if (parsedFields == teacherFields)
        {
            addTeacher(list, teacherName, subjectName);
            // numOfTeachers = addTeacher(teacherName, subjectName, numOfTeachers);
        }
        else
        {
            perror("Failed to parse line successfully");
            return -1;
        }
    }

    free(line);
    fclose(file);

    return 1;
}

int save(StudentsList *studentsList, TeachersList *teachersList)
{
    FILE *studentsFile = fopen(studentsFileName, "w"); // open file in write mode (creates new file if it doesn't already exist)
    FILE *teachersFile = fopen(teachersFileName, "w");
    if (studentsFile == NULL || teachersFile == NULL)
    {
        perror("Unable to open a required file\n");
        return -1;
    }

    for (int i = 0; i < studentsList->currentSize; i++)
    {
        if (saveStudent(studentsFile, studentsList->students[i]) == -1)
        {
            return -1;
        }
    }

    for (int i = 0; i < teachersList->currentSize; i++)
    {
        if (saveTeacher(teachersFile, teachersList->teachers[i]) == -1)
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
    fprintf(file, "\"%s\",%d,", student->name, student->subjectCount);
    for (int i = 0; i < student->subjectCount; i++)
    {
        // print each subject for the student at the end
        // (after the first two fields, name and subject count) consecutively
        Subject subject = student->subjects[i];
        fprintf(file, "\"%s\",%0.2f", subject.name, subject.grade);

        if (i < student->subjectCount - 1)
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
    return fprintf(file, "\"%s\",\"%s\"\n", teacher->name, teacher->subject.name);
}