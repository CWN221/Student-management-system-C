#include<stdio.h>
#include<string.h>

#include "../include/file_handler.h"

void displayMenu()
{
    printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
    printf("1. Add a new student\n");
    printf("2. View all students\n");
    printf("3. Search student by Admission No.\n");
    printf("4. Delete Student Data\n");
    printf("5. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

int main()
{
    Student student[MAX_STUDENTS];
    int choice;
    int studentCount = 0;

    char admissionNo[20];

    loadFromFile(student, &studentCount);

    while(1) {
        displayMenu();

        // Get user choice
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                addStudent(student);
                break;

            case 2:
                viewAllStudents(student);
                break;
            
            case 3:                
                printf("Enter Admission Number to search: ");
                scanf("%19s", admissionNo);
                searchStudentByAdmissionNo(student, studentCount, admissionNo);  
                break;

            case 4:                
                printf("Enter Student Admission Number: ");
                scanf("%19s", admissionNo);
                deleteStudent(student, &studentCount, admissionNo);
                break;

            case 5:
                printf("Exiting program..........\n");
                return 0;            

            default:
                printf("Invalid choice. Please choos a valid option.\n");
                break;
        }
    }

    return 0;
}