# Student Management System (C)

A console-based student management system built using C.

## Features
- Add Student
- Delete Student
- Search Student by Admission Number
- View All Students
- File-based storage (CSV)
- Error logging e.g. "[03/03/26 22:03:47] ERROR: Failed to open file for loading"

## How to Compile

```bash
gcc src/main.c src/student.c src/file_handler.c -o main
./main