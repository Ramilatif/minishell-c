#ifndef BUILTINS_H
#define BUILTINS_H

enum builtin_status
{
    BUILTIN_NOT_FOUND, /* argv[0] is not a builtin, run it with exec. */
    BUILTIN_DONE,      /* The builtin ran, prompt again. */
    BUILTIN_EXIT,      /* The user asked to leave the shell. */
};

enum builtin_status run_builtin(char **argv);

#endif
