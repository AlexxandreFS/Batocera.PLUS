# Quick makefile 

# Compiler flags
CFLAGS  = -Wall

CC      = gcc

all: conv.exe dasm.exe

%.exe: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
