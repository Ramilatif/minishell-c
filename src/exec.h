#ifndef EXEC_H
#define EXEC_H

enum exit_code
{
    EXIT_CMD_NOT_EXECUTABLE = 126,
    EXIT_CMD_NOT_FOUND      = 127,
};

int exec_command(char **argv);

#endif
