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

/**
 * @brief Finds the index of the student in the students list if they
 * exist.
 *
 * @param list
 * @param studentName
 * @return int Returns the (first) index of the student found by
 * studentName in the StudentsList passed as argument. Otherwise,
 * returns -1 if not found.
 */
int studentExists(StudentsList *list, char *studentName);

/**
 * @brief Finds the index of the subject within the subjects array
 * inside the student if they exist.
 *
 * @param student
 * @param subject
 * @return int int Returns the (first) index of the subject found by
 * subjectName for the Student passed as argument. Otherwise,
 * returns -1 if not found.
 */
int subjectExistsForStudent(Student *student, char *subject);

/**
 * @brief Adds a new subject with the subjectName, and grade passed in as
 * argument for the student identified by studentName.
 *
 * @param list
 * @param studentName
 * @param subjectName
 * @param gradeInput
 */
void addSubject(StudentsList *list, char *studentName, char *subjectName, float gradeInput);

/**
 * @brief Adds a new student to the StudentsList passed in as argument.
 *
 * @param studentsList
 * @param studentName
 * @return int
 */
int addStudent(StudentsList *studentsList, char *studentName);

/**
 * @brief Adds a new teacher to the TeachersList passed in as argument.
 *
 * @param list
 * @param teacherName
 * @param subjectName
 */
void addTeacher(TeachersList *list, char *teacherName, char *subjectName);

/**
 * @brief
 *
 * @param list
 * @param teacher
 * @return int Returns the (first) index of the teacher found by
 * their name in the TeachersList passed as argument. Otherwise,
 * returns -1 if not found.
 */
int teacherExists(TeachersList *list, char *teacher);

/**
 * @brief Determines if a teacher is already registered as teaching the
 * subject passed in as argument.
 *
 * @param list
 * @param subject
 * @return int
 */
int teacherExistsForSubject(TeachersList *list, char *subject);

/**
 * @brief Displays all the subjects and their corresponding grades
 * for the Student passed in as argument.
 *
 * @param student
 */
void displaySubject(Student *student);

/**
 * @brief Asks user if they wish the StudentsList and TeachersList
 * passed in as argument to their corresponding csv files.
 *
 * @param studentsList
 * @param teachersList
 * @return int Returns 1 if able to save successfully, otherwise -1.
 */
int save(StudentsList *studentsList, TeachersList *teachersList);

/**
 * @brief Reads data from the teachers' CSV file into the TeachersList
 * passed in as argument.
 *
 * @param list
 * @return int Returns 1 if able to read file data successfuly, otherwise -1.
 */
int readTeachers(TeachersList *list);
