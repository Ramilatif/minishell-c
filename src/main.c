#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Minimal interactive shell entry point.
 *
 * This program reads a line from stdin, splits it into arguments,
 * and stores them in an argv-like array until the user exits.
 *
 * @return 0 on clean exit, 1 on allocation failure.
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

        /* Echo the input line for the current minimal shell behavior. */
        printf("%s", line);

        /* Split the input into tokens separated by spaces, tabs, and newlines. */
        char *saveptr;
        char *token = strtok_r(line, " \t\n", &saveptr);
        int i = 0;

        while (token != NULL)
        {
            /* Resize the array when more arguments are needed. */
            if (i + 1 >= size)
            {
                size *= 2;
                char **new_argv = realloc(argv, size * sizeof(char *));
                if (new_argv == NULL)
                {
                    perror("realloc");
                    free(argv);
                    free(line);
                    return (1);
                }
                argv = new_argv;
            }

            argv[i] = token;
            i++;
            token = strtok_r(NULL, " \t\n", &saveptr);
        }

        /* Terminate the token list with NULL for compatibility with exec-style APIs. */
        argv[i] = NULL;
    }

    free(argv);
    free(line);
    return (0);
}