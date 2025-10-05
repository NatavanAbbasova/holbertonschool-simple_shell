#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - executes a command using execve
 * @cmd: command string
 * @envp: environment variables
 */
void execute_command(char *cmd, char **envp)
{
    char *argv[1024];
    int i = 0;
    char *token;
    pid_t pid;
    int status;

    /* tokenize the command */
    token = strtok(cmd, " \t");
    while (token != NULL && i < 1023)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t");
    }
    argv[i] = NULL;

    if (argv[0] == NULL)
        return;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        /* child process */
        if (execve(argv[0], argv, envp) == -1)
        {
            perror(argv[0]);
            _exit(1);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

