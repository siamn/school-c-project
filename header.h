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

char *getLine();

char *getLimitedLine(int limit);

int getYesNoResponse(char *prompt);

int getPositiveInt();

float getFloat();

int save(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers);