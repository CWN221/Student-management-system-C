// File handles student operations
#include<stdio.h>
#include <string.h>

#include "../include/file_handler.h"


int getLastStudentId()
{
    FILE* fileptr = fopen(FILE_NAME, "r");
    if (fileptr == NULL) {
        return 0;  // Return 0 if no students are present in the file
    }

    int lastId = 0;
    Student student;

    // Read until the end of the file, storing the last student ID
    while (fscanf(fileptr, "%d,%19[^,],%99[^,],%c,%d,%99[^,],%f,%199[^\n]\n",
                  &student.id, student.admission_no, student.name, &student.gender, 
                  &student.age, student.course, &student.gpa, student.address) == 8) {
        lastId = student.id;  
    }

    fclose(fileptr);
    return lastId;  
}


void addStudent(Student* student)
{
    printf("===== NEW STUDENT ENTRY =====\n");

    student->id = getLastStudentId() + 1;
    printf("Student ID: %03d\n", student->id);

    printf("Enter Admission No. : ");
    fgets(student->admission_no, sizeof(student->admission_no), stdin);
    student->admission_no[strcspn(student->admission_no, "\n")] = '\0';

    printf("Student's name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = '\0';

    printf("Gender ('M' or 'F'): ");
    scanf(" %c", &student->gender);

    printf("Age: ");
    scanf("%d", &student->age);
    while (getchar() != '\n');

    printf("Course: ");
    fgets(student->course, sizeof(student->course), stdin);
    student->course[strcspn(student->course, "\n")] = '\0';

    printf("GPA: ");
    scanf("%f", &student->gpa);
    while (getchar() != '\n');

    printf("Address: ");    
    fgets(student->address, sizeof(student->address), stdin);   
    student->address[strcspn(student->address, "\n")] = '\0';    


    // Display entered information for confirmation
    printf("\n===== ENTERED STUDENT INFORMATION =====\n");
    printf("Admission No: %s\n", student->admission_no);
    printf("Name: %s\n", student->name);
    printf("Gender: %c\n", student->gender);
    printf("Age: %d\n", student->age);
    printf("Course: %s\n", student->course);
    printf("GPA: %.2f\n", student->gpa);
    printf("Address: %s\n", student->address);

    char saveChoice;
    printf("\nDo you want to save this student data? (Y/N): ");
    scanf(" %c", &saveChoice);

    switch(saveChoice) {
        case 'Y':
        case 'y':
            saveToFile(student);
            break;

        case 'N':
        case 'n':
            printf("Student data not saved.\n");
            break;

        default:
            printf("Invalid input. Enter 'Y' for Yes or 'N' for No.\n");
            break;
    }        

}


/*
    Method to delete a student
*/
void deleteStudent(Student* student, int* studentCount, const char* admissionNo)
{
    int found = 0;
    int i, j;

    // search for student using admission no.
    for (i = 0; i < *studentCount; i++) {
        if(strcmp(student[i].admission_no, admissionNo) == 0) {
            found = 1;

            for (j = i; j < (*studentCount) - 1; j++) {
                student[j] = student[j + 1];
            }

            (*studentCount)--;
            printf("Student with Admission Number %s has been deleted.\n", admissionNo);
            break;
        }
    }

    if (!found) {
        printf("No Student found with Admission Number: %s\n", admissionNo);        
        return;
    }

    FILE* file;
    file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        errorLog("Failed to open file to delete.");
        perror("Failed to open file to delete.");
        return;
    }

    for (i = 0; i < *studentCount; i++)
    {
        fprintf(file, "%d,%s,%s,%c,%d,%s,%.2f,%s\n",
        student[i].id, student[i].admission_no, student[i].name, student[i].gender,
        student[i].age, student[i].course, student[i].gpa, student[i].address);
    }
    fclose(file);
}



void displayStudent(Student* student)
{
    printf("\n===== STUDENT DETAILS =====\n");

    printf("Admission No: %s\n", student->admission_no);
    printf("Name: %s\n", student->name);
    printf("Gender: %c\n", student->gender);
    printf("Age: %d\n", student->age);
    printf("Course: %s\n", student->course);
    printf("GPA: %.2f\n", student->gpa);
    printf("Address: %s\n", student->address);

}


/*
    Method to search for student using Admission No
*/
void searchStudentByAdmissionNo(Student* student, int studentCount, const char* admissionNo)
{
    int found = 0;
    int i;

    for (i = 0; i < studentCount; i++)
    {
        if (strcmp(student[i].admission_no, admissionNo) == 0)
        {
            printf("\n===== STUDENT FOUND =====\n");
            printf("ID: %d\n", student[i].id);
            printf("Admission No: %s\n", student[i].admission_no);
            printf("Name: %s\n", student[i].name);
            printf("Gender: %c\n", student[i].gender);
            printf("Course: %s\n", student[i].course);
            printf("Address: %s\n", student[i].address);
            found = 1;
            break;
        }
    }

    if(!found)
    {
        printf("No student found with admission number: %s\n", admissionNo);       
    }
}


/*
    Method to view all students in data file
*/
void viewAllStudents(Student* students)
{   

    int studentCount = 0;
    int i;

    loadFromFile(students, &studentCount);

    printf("\n========== ALL STUDENT RECORDS ==========\n");
    printf("ID   |  Admission No.       |  Student Name                | Gender  | Age | Course                                   | GPA  | Address            \n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    for (i = 0; i <studentCount; i++)
    {
        printf("%-4d | %-20s | %-28s | %-7c | %-3d | %-40s | %-4.2f | %s\n",
        students[i].id, students[i].admission_no, students[i].name, students[i].gender,
        students[i].age, students[i].course, students[i].gpa, students[i].address);
    }        
}
