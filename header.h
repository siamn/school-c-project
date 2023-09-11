#define MAX_NAME_LENGTH 20
#define MAX_SUBJECT_LENGTH 20

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

int add_teacher(Teacher **teachers, char *teacherName, char *subjectName);

char *getLine();

char *getLimitedLine(int limit);

int getYesNoResponse(char *prompt);

int getPositiveInt();

float getFloat();

int save(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers);

int readTeachers(Teacher **teachers);