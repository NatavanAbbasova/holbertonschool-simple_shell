#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

/* Trim leading and trailing whitespace */
char *trim(char *str)
{
	char *end;

	/* Trim leading space */
	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0)  /* All spaces? */
		return str;

	/* Trim trailing space */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;

	*(end + 1) = '\0';

	return str;
}

/* Display prompt and execute commands */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&line, &len, stdin);
		if (nread == -1)  /* EOF or error */
		{
			free(line);
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}

		line[nread - 1] = '\0';  /* remove newline */
		line = trim(line);

		if (line[0] == '\0')  /* skip empty lines */
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)  /* child */
		{
			char *argv[] = {line, NULL};
			execve(line, argv, environ);
			perror(line);  /* execve failed */
			_exit(EXIT_FAILURE);
		}
		else  /* parent */
		{
			waitpid(pid, &status, 0);
		}
	}
}

