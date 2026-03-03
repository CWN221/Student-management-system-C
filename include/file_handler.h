#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../include/student.h"

#define FILE_NAME "data/students_data.csv"
#define ERROR_LOG "error_log.txt"
#define MAX_STUDENTS 200

void saveToFile(Student* student);
void loadFromFile(Student* student, int* studentCount);

#endif