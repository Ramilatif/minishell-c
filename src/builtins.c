#include "builtins.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Run argv[0] if it is a builtin command.
 *
 * Builtins run in the shell process itself, without fork, so that
 * commands like cd can change the shell's own state.
 *
 * @param argv NULL-terminated argument array, argv[0] is the command.
 * @return What the main loop should do next.
 */
enum builtin_status run_builtin(char **argv)
{
    if (strcmp(argv[0], "exit") == 0)
    {
        return (BUILTIN_EXIT);
    }

    if (strcmp(argv[0], "cd") == 0)
    {
        if (argv[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else if (chdir(argv[1]) != 0)
        {
            perror("cd");
        }
        return (BUILTIN_DONE);
    }

    if (strcmp(argv[0], "help") == 0)
    {
        printf("Minimal interactive shell\n");
        printf("Built-in commands:\n");
        printf("  cd <dir>   Change the current directory to <dir>\n");
        printf("  exit       Exit the shell\n");
        printf("  help       Display this help message\n");
        return (BUILTIN_DONE);
    }

    return (BUILTIN_NOT_FOUND);
}
