
TARGET = libcnet.a
# ��ǰ�ļ����µ�����.c�ļ�������main.c
OBJ = $(patsubst %.c, %.o, $(filter-out main.c, $(wildcard *.c)))

CC = gcc
CFLAGS = -Wall

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