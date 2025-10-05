#include "shell.h"

/**
 * execute_command - executes a command using execve
 * @cmd: command string
 */
void execute_command(char *cmd)
{
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
}
