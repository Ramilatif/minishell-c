#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Split a line into an argv-like array.
 *
 * Tokens are separated by spaces, tabs, and newlines. They point into
 * @p line, which is modified in place. The array is grown when needed
 * and always terminated by NULL.
 *
 * @param line Input line to split.
 * @param argv Address of the argv array, may be reallocated.
 * @param size Address of the array capacity, updated on growth.
 * @return Number of tokens, or -1 on allocation failure.
 */
int parse_line(char *line, char ***argv, int *size)
{
    char *saveptr;
    char *token = strtok_r(line, " \t\n", &saveptr);
    int i = 0;

    while (token != NULL)
    {
        /* Resize the array when more arguments are needed. */
        if (i + 1 >= *size)
        {
            char **new_argv = realloc(*argv, *size * 2 * sizeof(char *));
            if (new_argv == NULL)
            {
                perror("realloc");
                return (-1);
            }
            *argv = new_argv;
            *size *= 2;
        }

        (*argv)[i] = token;
        i++;
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    /* Terminate the token list with NULL for compatibility with exec-style APIs. */
    (*argv)[i] = NULL;
    return (i);
}
