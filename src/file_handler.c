/*
    file_handler.c
    File handles reading & writing of data
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/file_handler.h"

#define MAX_STUDENTS 200


void errorLog(const char* errorMessage)
{
    FILE* logfile = fopen(ERROR_LOG, "a");

    if (logfile == NULL)
    {
        perror("Error opening Log File");
        return;
    }

    // Get current time to store timestamp in log file
    struct tm* timeptr; // strucuture to store local time    
    time_t t; 
    t = time(NULL);  // get current time  
    timeptr = localtime(&t); 
    char timestamp[30];

    strftime(timestamp, sizeof(timestamp), "%c", timeptr);

    // Add timestamp & log error message to error_log.txt
    fprintf(logfile, "[%s] ERROR: %s\n", timestamp, errorMessage);
    fclose(logfile);
}

/*
    Method to save new student to file
*/
void saveToFile(Student* student)
{
    FILE* fptr;

    fptr = fopen(FILE_NAME, "a");

    if (fptr == NULL) {
        errorLog("Failed to open file for saving.");
        perror("Error opening File");     
        return;   
    } 

    // Save the data to CSV file
    fprintf(fptr, "%d,%s,%s,%c,%d,%s,%.2f,%s\n", 
        student->id, student->admission_no, student->name, student->gender, 
        student->age, student->course, student->gpa, student->address);

    fclose(fptr);
    printf("Student saved to file successfully.\n");
}



void loadFromFile(Student* student, int* studentCount)
{
    FILE* fileptr;

    fileptr = fopen(FILE_NAME, "r");
    if (fileptr == NULL)
    {
        errorLog("Failed to open file for loading");
        perror("Failed to open file for loading student data.");
        return;
    }

    *studentCount = 0;
    // Load data from CSV file
    while (fscanf(fileptr, "%d,%19[^,],%99[^,],%c,%d,%99[^,],%f,%199[^\n]\n", 
                  &student[*studentCount].id, student[*studentCount].admission_no, student[*studentCount].name, 
                  &student[*studentCount].gender, &student[*studentCount].age, student[*studentCount].course, 
                  &student[*studentCount].gpa, student[*studentCount].address) == 8) 
    {
        (*studentCount)++; 
        if (*studentCount >= MAX_STUDENTS) {
            printf("Maximum number of students reached. Some data may not have been loaded.\n");
            break;
        }
    }

    fclose(fileptr);

    if (*studentCount == 0)
    {
        printf("No student found or file is empty.\n");
    }

}