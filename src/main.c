#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

enum exit_code
{
    EXIT_CMD_NOT_EXECUTABLE = 126,
    EXIT_CMD_NOT_FOUND      = 127,
};

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

        if (argv[0] == NULL)
        {
            continue; /* No command entered, prompt again. */
        }

        /* Flush pending output so the child does not inherit a copy of it. */
        fflush(stdout);

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(argv);
            free(line);
            return (1);
        }

        if (pid == 0)
        {
            /* Child process: execute the command. */
            execvp(argv[0], argv);
            perror(argv[0]); /* If execvp returns, an error occurred. */
            _exit(EXIT_CMD_NOT_FOUND);
        }
        else
        {
            /* Parent process: wait for the child to finish. */
            int status;
            waitpid(pid, &status, 0);
        }

    }

    free(argv);
    free(line);
    return (0);
}