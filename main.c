#include "shell.h"

/**
 * main - entry point for the shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment pointer
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	(void)argc;
	(void)argv;

	while (1)
	{
		/* print shell prompt */
		write(1, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		/* remove trailing newline */
		line[read - 1] = '\0';

		/* ignore empty input */
		if (line[0] == '\0')
			continue;

		/* execute the command */
		execute_command(line, envp);
	}

	free(line);
	return (0);
}

