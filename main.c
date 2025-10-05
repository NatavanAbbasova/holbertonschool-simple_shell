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
	(void)envp;

	while (1)
	{
		print_prompt();

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		line[strcspn(line, "\n")] = '\0'; /* remove trailing newline */
		if (line[0] == '\0')
			continue;

		execute_command(line);
	}

	free(line);
	return (0);
}

