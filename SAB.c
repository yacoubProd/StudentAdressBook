#include <stdio.h>
#include <string.h>

#define MAX_ARR           64
#define MAX_STR           32
#define MAX_PROMPT_STR    256

#define MAX_GRADE         100
#define MIN_GRADE         0

#define RETURN_VALUE_NOK                -1
#define RETURN_VALUE_OK_NOT_DONE        0
#define RETURN_VALUE_OK_DONE            1

typedef struct {
  char  code[MAX_STR];
  int   grade;
} CourseType;

typedef struct {
  CourseType elements[MAX_ARR];
  int size;
} CourseArrType;

typedef struct {
  char name[MAX_STR];
  char id[MAX_STR];
  CourseArrType courses;
  float gpa;
} StudentType;



void promptForStudent(StudentType *newStu);

void promptForStudents(StudentType *stuArr, int *lenArr);

void initStudent(StudentType *student, const char *name, const char *id, CourseArrType *courses);

void addStudent(StudentType *arr, int *length, const StudentType *student); 

void printStudent(const StudentType *student);

void printStudentArray(const StudentType *arr, const int length);

void readString(char*);

void readInt(int*);

void printCourse(const CourseType *course);

void printCourseArray(const CourseArrType *arr);

void initCourse(CourseType *course, char *code, int grade);

void addCourse(CourseArrType *courseArr, const CourseType *course);

void initCourseArr(CourseArrType *courseArr, CourseType *actualArrOfCourses, int length);

void computeGpa(CourseArrType *courses, float *pStudentsGpa);

void nameGet(char *name);

void idGet(char *id);

void promptForCode(char *code);

void promptForGrade(int *grade);

void promptForCourse(CourseType *course);

void promptForCourses(CourseArrType *pCourseArr);


int main() {
  int studentsLength = 0;
  StudentType students[MAX_ARR];
  promptForStudents(students, &studentsLength);
  printStudentArray(students, studentsLength);
  return 0;
}


/*
    Function:  readString
    Purpose:   reads a string from standard input
        out:   string read in from the user
               (must be allocated in calling function)
*/
void readString(char *str)
{
  char tmpStr[MAX_STR];
  fgets(tmpStr, sizeof(tmpStr), stdin);
  tmpStr[strlen(tmpStr)-1] = '\0';
  strcpy(str, tmpStr);
}

/*
    Function:  readInt
    Purpose:   reads an integer from standard input
        out:   integer read in from the user
               (must be allocated in calling function)
*/
void readInt(int *x)
{
  char str[MAX_STR];
  readString(str);
  sscanf(str, "%d", x);
}

/*
    Function:  printStudent
    Purpose:   Prints the student type and all of its feilds
         in:   student
*/
void printStudent(const StudentType *student) {
  printf("Student name: \t\t%s\n", student->name);
  printf("Student id: \t\t%s\n", student->id);
  printf("%s's courses: \n", student->name);
  printCourseArray(&(student->courses));
  printf("Student gpa: \t\t%f\n\n\n", student->gpa);
}


/*
Function:  printCourse
Purpose:   prints a course
     in:   a course
*/
void printCourse(const CourseType *course) {
  printf("\tCourse code: \t\t\t\t%s\n", course->code);
  printf("\tStudent's grade in %s: \t\t%d%%\n", course->code, course->grade);
}

/*
Function:  printStudentArray
Purpose:   prints an array of student types
     in:   array of students
     in:   length of that specific aRRAY
*/
void printStudentArray(const StudentType* arr, const int length) {
  for (int i = 0; i < length; i++) {
    printf("Student: \t%d\n", i);
    printStudent(arr + i); //iterates through the array 
  }
}


/*
Function:  printCourseArray
Purpose:   prints an array of CourseArrType
     in:   An array of CourseArrType 
*/
void printCourseArray(const CourseArrType *arr) {
  for (int i = 0; i < arr->size; i++) {
    printCourse(arr->elements + i);
  }
}
/////MOGO NOTES: GOOD UNTIL HERE///////


/*
Function:  initStudent
Purpose:   assign the output parameter student with values passed as parameters 
    out:   The student types that are being assigned values in their feilds
           (must be allocated in calling function)
     in:   student name,ID,Courses

*/
void initStudent(StudentType *student, const char *n, const char *id, CourseArrType *courses) {
  strcpy(student->name, n);
  strcpy(student->id, id);
  student->courses = *courses; 
  computeGpa(courses, &(student->gpa));
}

/*
Function:  addStudent
Purpose:   adds a student type to an array of student types
 in/out:   the array of students
 in/out:   length of the array added
     in:   student that is being added to the array
*/
void addStudent(StudentType *arr, int *length, const StudentType *student) {
  if (*length < MAX_ARR) {
    arr[*length] = *student;
    (*length)++;
  }
  else {
    printf("Student can't be added. The array capacity has been reached\n");
  }
}


/*
Function:  addCourse
Purpose:   adds a course to a CourseArrType
 in/out:   CourseArrType to be added to
     in:   course that is being added to CourseArrType
*/
void addCourse(CourseArrType *courseArr, const CourseType *course) {
  if (courseArr->size < MAX_ARR) {
    courseArr->elements[courseArr->size] = *course;
    (courseArr->size)++;
  }
  else {
    printf("Cannot add student to array because length is exceeded otherwise.\n");
  }
}


/*
Function:  initCourse
Purpose:   assign the output parameter course with values passed as parameters 
    out:   course that fields will be assigned to
           (must be allocated in calling function)
     in:   course code
     in:   grade
*/
void initCourse(CourseType *course, char *code, int grade) {
  strcpy(course->code, code);
  course->grade = grade;
}

////MOGO NOTES DONE HERE SO FAR/////

/*
Function:  initCourseArr
Purpose:   initializes a CourseArrType (assigns values to it)
    out:   CourseArrType pointer of CourseArrType to be intialized
           (must be allocated in calling function)
     in:   array of courses
     in:   length of array
*/
void initCourseArr(CourseArrType *courseArr, CourseType *actualArrOfCourses, int length) {
  for (int i = 0; i < length; i++) {
    courseArr->elements[i] = actualArrOfCourses[i];
  }
  courseArr->size = length;
}

/*
Function:  computeGpa
Purpose:   computes the gpa of a list of courses
     in:   STlist of courses to calculate gpa 
    out:   student's gpa
           (must be allocated in calling function)
*/
void computeGpa(CourseArrType *courses, float *pStudentsGpa) {
  float sum = 0;
  float numberOfCourses = courses->size;
  if (numberOfCourses == 0) {
    printf("\nThere are no courses.\n");
    *pStudentsGpa = 0;
    return;
  }
  float gpa = -1;
  for (int i = 0; i < numberOfCourses; i++) {
    sum = sum + (*(courses->elements + i)).grade;
  }
  gpa = sum / numberOfCourses;
  *pStudentsGpa = gpa;
}


/*
Function:  promptForId
Purpose:   promps user for id of student
    out:   id of student
           (must be allocated in calling function)
*/
void idGet(char *id) {
  printf("\n");
  char userInputID[MAX_STR];
  while (1) {
    printf("Please enter this student's id: ");
    userInputID[0] = '\0';
    readString(userInputID);

    if (userInputID[0] == '\0') {
      printf("Unfortunately, you cannot enter an empty string. Please try again.\n");
      }
    else {
      break;
    	}
  	}
  strcpy(id, userInputID);
	}
	
	
	
	/*
Function:  promptForName
Purpose:   prompts the user for a students names
    out:   name of student
           (must be allocated in calling function)
*/
void nameGet(char *name) {
  printf("\n");
  char userInputName[MAX_STR];
  while (1) {
    printf("Please enter the student name: ");
    userInputName[0] = '\0';
    readString(userInputName);

    if (userInputName[0] == '\0') {
      printf("You cannot enter an empty string. Please try again.\n");
    }
    else {
      break;
    }
  }
  strcpy(name, userInputName);
}

	
	
	
	
	
	
/*
Function:  promptForCode
Purpose:   prompts user for code of course
    out:   code of course
           (must be allocated in calling function)
*/
void promptForCode(char *code) {
  printf("\n");
  char userInputCode[MAX_STR];
  while (1) {
    printf("Please enter this course's code: ");
    userInputCode[0] = '\0';
    readString(userInputCode);

    if (userInputCode[0] == '\0') {
      printf("You cannot enter an empty string. Please try again.\n");
    }
    else{
      break;
    }
  }
  strcpy(code, userInputCode);
}

/*
Function:  promptForGrade
Purpose:   prompts user for grade of course
    out:   grade of student in course
           (must be allocated in calling function)
*/
void promptForGrade(int *grade) {
  int userInputGrade;
  while (userInputGrade < 0 || userInputGrade > 100) {
    printf("Please enter the student's grade in this course: ");
    userInputGrade = -1;
    readInt(&userInputGrade);

    if (userInputGrade < 0 || userInputGrade > 100) {
      printf("You must enter a value between 0 and 100. Please try again.\n");
    }
  }
  *grade = userInputGrade;
}

/*
Function:  promptForCourse
Purpose:   prompts user to enter information for course
    out:   course of student
           (must be allocated in calling function)
*/
void promptForCourse(CourseType *pCourse) {
  char code[MAX_STR];
  int grade;
  promptForCode(code);
  promptForGrade(&grade);
  strcpy(pCourse->code,code);
  pCourse->grade = grade;
}

/*
Function:  promptForCourses
Purpose:   prompts user for all the courses that student has taken
    out:   CourseArrType of all the courses student has taken
           (must be allocated in calling function)
*/
void promptForCourses(CourseArrType *pCourseArr) {
  pCourseArr->size = 0;
  int userInput =  -1;
  while (1) {
    printf("\nCourses added: %d \n You have room to add %d more.\n", pCourseArr->size, MAX_ARR - pCourseArr->size);
    if (!(pCourseArr->size < MAX_ARR)) {
      printf("You cannot add any more courses for this student.\n");
      break;
    }
    userInput = -1;
    while (1) {
      printf("Enter 0 if you'd like to enter another course. enter 1 to exit and print.\n");
      readInt(&userInput);

      if (userInput == 0 || userInput == 1) {
        break;
      }
      printf("You must enter either 0 or 1.\n");
    }
    if (userInput == 1) {
      break;
    }
    CourseType newCourse;
    promptForCourse(&newCourse);
    pCourseArr->elements[pCourseArr->size] = newCourse;
    (pCourseArr->size)++;
  }
}

/*
Function:  promptForStudent
Purpose:   prompts the user to enter all the fields of a student
    out:   new student
           (must be allocated in calling function)
*/
void promptForStudent(StudentType *newStu) {
  char name[MAX_STR];
  char id[MAX_STR];
  //CourseArrType newStusCourses;
  //float gpa;
  nameGet(name);
  strcpy(newStu->name, name);
  idGet(id);
  strcpy(newStu->id, id);
  promptForCourses(&(newStu->courses));
  computeGpa(&(newStu->courses), &(newStu->gpa));
}

/*
Function:  promptForStudents
Purpose:   prompts user to enter fields of all the students
    out:   student array to be added to
           (must be allocated in calling function)
 in/out:   length of student array
           (must be allocated in calling function)
*/
void promptForStudents(StudentType *stuArr, int *lenArr) {
  int userInput = -1;
  *lenArr = 0;
  while (1) {
    printf("\n Students added: %d \n You have room to add %d more students.\n", *lenArr, MAX_ARR - *lenArr);


    if (!(*lenArr < MAX_ARR)) {
      printf("You have no more room to add students to this group of students.\n");
      break;
    }
    userInput = -1;
    while (1) {
      printf("Enter 0 if you'd like to enter another student. Enter 1 if you would like to exit.\n");
      readInt(&userInput);

      if (userInput == 0 || userInput == 1) {
        break;
      }
      printf("Unfortunately, you must enter either 0 or 1.\n");
    }
    if (userInput == 1) {
      break;
    }
    StudentType newStu;
    promptForStudent(&newStu);
    
    addStudent(stuArr, lenArr, &newStu);
  }
}
