CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g -D_POSIX_C_SOURCE=200809L -MMD -MP
TARGET  = minishell
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
DEP     = $(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

.PHONY: clean

-include $(DEP)
