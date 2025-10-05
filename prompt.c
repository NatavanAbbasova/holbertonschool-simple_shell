#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - executes a command using execve
 * @line: command line string
 * @envp: environment pointer
 */
void execute_command(char *line, char **envp)
{
	char *args[1024]; /* array to hold arguments */
	char *token;
	int i = 0;
	pid_t pid;
	int status;

	/* tokenize the input line into arguments */
	token = strtok(line, " \t");
	while (token != NULL && i < 1023)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return; /* empty command */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		/* child process */
		if (execve(args[0], args, envp) == -1)
		{
			perror(args[0]);
			_exit(1);
		}
	}
	else
	{
		/* parent process waits for child */
		waitpid(pid, &status, 0);
	}
}

