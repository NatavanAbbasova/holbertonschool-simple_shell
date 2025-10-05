#include "shell.h"

/**
 * main - simple shell entry point
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		print_prompt();

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

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
			execute_command(line);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return (0);
}
