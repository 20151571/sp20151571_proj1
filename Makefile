.SUFFIXES :	.c .o

OBJECTS = 20151571.o parkunsang.o
SRCS = 20151571.c parkunsang.c

CC = gcc
CFLAGS = -c -Wall -W

target = 20151571.out

$(TARGET) : $(OBJECTS)
			$(CC) -o $(TARGET) $(OBJECTS)

clean:
		rm $(OBJECTS) $(TARGET) core

parkunsang.o : 20151571.h parkunsang.c
20151571.o : 20151571.h 20151571.c
