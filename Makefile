
TARGET = main.exe
LIB = libcnet.a
# 当前文件夹和lib文件夹下的所有.c文件
OBJ = $(patsubst %.c,%.o,  $(wildcard *.c))
LIBOBJ = $(patsubst %.c,%.o,  $(wildcard lib/*.c))

CC = gcc
CFLAGS = -Wall -I.


all: $(TARGET)

start: all
	./main.exe

lib: $(TARGET)

$(TARGET): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -lws2_32 -o $@

$(LIB): $(LIBOBJ)
	ar rcs $@ $^

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBOBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(LIB) $(OBJ) $(LIBOBJ) $(TARGET) main.exe