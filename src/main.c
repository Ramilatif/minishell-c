#include "builtins.h"
#include "exec.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Minimal interactive shell entry point.
 *
 * This program reads a line from stdin, splits it into arguments,
 * and runs it as a builtin or an external command until the user exits.
 *
 * @return 0 on clean exit, 1 on allocation or fork failure.
 */
int main(void)
{
    char *line = NULL;
    size_t cap = 0;
    ssize_t len;
    int size = 8;
    char **argv = malloc(size * sizeof(char *));

    if (argv == NULL)
    {
        perror("malloc");
        return (1);
    }

    while (1)
    {
        /* Display the prompt to the user. */
        printf("minishell> ");
        fflush(stdout);

        /* Read one command line from standard input. */
        len = getline(&line, &cap, stdin);

        if (len == -1)
        {
            putchar('\n');
            break;
        }

        if (parse_line(line, &argv, &size) == -1)
        {
            free(argv);
            free(line);
            return (1);
        }

        if (argv[0] == NULL)
        {
            continue; /* No command entered, prompt again. */
        }

        enum builtin_status status = run_builtin(argv);
        if (status == BUILTIN_EXIT)
        {
            break; /* Exit the shell loop. */
        }
        if (status == BUILTIN_DONE)
        {
            continue; /* Prompt again after the builtin. */
        }

        if (exec_command(argv) == -1)
        {
            free(argv);
            free(line);
            return (1);
        }
    }

    free(argv);
    free(line);
    return (0);
}
