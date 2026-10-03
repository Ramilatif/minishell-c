#include "exec.h"

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Run an external command in a child process and wait for it.
 *
 * @param argv NULL-terminated argument array, argv[0] is the command.
 * @return 0 once the child has finished, -1 if fork failed.
 */
int exec_command(char **argv)
{
    /* Flush pending output so the child does not inherit a copy of it. */
    fflush(stdout);

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }

    if (pid == 0)
    {
        /* Child process: execute the command. */
        execvp(argv[0], argv);
        perror(argv[0]); /* If execvp returns, an error occurred. */
        _exit(EXIT_CMD_NOT_FOUND);
    }

    /* Parent process: wait for the child to finish. */
    int status;
    waitpid(pid, &status, 0);
    return (0);
}
