#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char   *line = NULL;  
    size_t  cap  = 0;
    ssize_t len;

    while (1)
    {
        printf("minishell> ");
        fflush(stdout);
        len = getline(&line, &cap, stdin);

        if(len==-1){
            putchar('\n');
            break;
        }
        printf("%s", line);
    }


    free(line);
    return (0);
}