CC = gcc
CFLAGS = -Wall -W
SRCS = 20151571.c parkunsang.c
OBJECTS=$(SRCS:.c=.o)

TARGET = 20151571.out

all: $(SRCS) $(TARGET)
	
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
		$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(OBJECTS) $(TARGET)

