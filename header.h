#define MAX_NAME_LENGTH 20
#define MAX_SUBJECT_LENGTH 20

typedef struct
{
    char *name;
    float grade;
} Subject;

typedef struct
{
    char *name;
    Subject subject;
} Teacher;

typedef struct
{
    Teacher **teachers;
    int currentSize;
    int maxSize;
} TeachersList;

typedef struct
{
    char *name;
    int subjectCount;
    Subject *subjects;
} Student;

typedef struct
{
    Student **students;
    int currentSize;
    int maxSize;
} StudentsList;

extern Student **students;
extern Teacher **teachers;

int studentExists2(StudentsList *list, char *studentName);

int subjectExistsForStudent(Student *student, char *subject);

void addSubject2(StudentsList *list, char *studentName, char *subjectName, float gradeInput);

int addStudent2(StudentsList *studentsList, char *studentName);

int addTeacher(char *teacherName, char *subjectName, int numOfTeachers);

int save(Student **students, int numOfStudents, Teacher **teachers, int numOfTeachers);

int readTeachers();