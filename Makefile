CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
TARGET  = minishell
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
