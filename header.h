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

int studentExists(StudentsList *list, char *studentName);

int subjectExistsForStudent(Student *student, char *subject);

void addSubject(StudentsList *list, char *studentName, char *subjectName, float gradeInput);

int addStudent(StudentsList *studentsList, char *studentName);

void addTeacher(TeachersList *list, char *teacherName, char *subjectName);

int teacherExists(TeachersList *list, char *teacher);

int teacherExistsForSubject(TeachersList *list, char *subject);

void displaySubject(Student *student);

int save(StudentsList *studentsList, TeachersList *teachersList);

int readTeachers(TeachersList *list);
