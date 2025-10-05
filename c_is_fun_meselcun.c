#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;

    while (1)
    {
        printf("#cisfun$ ");
        nread = getline(&line, &len, stdin);

        /* Handle EOF (Ctrl+D) */
        if (nread == -1)
        {
            printf("\n");
            break;
        }

        /* Remove trailing newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Ignore empty input */
        if (strcmp(line, "") == 0)
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* child process */
            char *argv[] = {line, NULL};
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}

