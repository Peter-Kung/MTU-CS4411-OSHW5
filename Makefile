CC := gcc
CFLAG := -g -o
SOURCE := main.c
LIB    := funct5.c
TARGET := ./prog5

all: main
	$(TARGET)

main:
	$(CC) $(LIB) $(SOURCE) $(CFLAG) $(TARGET)
