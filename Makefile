
TARGET = libcnet.a
# 当前文件夹下的所有.c文件，除了main.c
OBJ = $(patsubst %.c,%.o,  $(wildcard lib/*.c))

CC = gcc
CFLAGS = -Wall -I.

all: $(TARGET) main.c
	$(CC) $(CFLAGS) main.c $(TARGET) -lws2_32 -o main.exe

start: all
	./main.exe

lib: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.a *.exe