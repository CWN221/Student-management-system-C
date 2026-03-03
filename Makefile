CC = gcc
CFLAGS = -Wall -Wextra
TARGET = main
SRCS = src/main.c src/student.c src/file_handler.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
