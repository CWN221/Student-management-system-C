#ifndef STUDENT_H
#define STUDENT_H


#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char admission_no[20];
    char name[MAX_NAME_LENGTH];
    char gender; // 'M' or 'F'      
    int age;
    char course[100];
    float gpa;
    char address[100];
} Student;


void addStudent(Student* student);
void deleteStudent(Student* student, int* studentCount, const char* admissionNo);
void updateStudent();
void displayStudent(Student* student);
void viewAllStudents(Student* student);
void searchStudentByAdmissionNo(Student* student, int studentCount, const char* admissionNo);

#endif