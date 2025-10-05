#include "shell.h"

extern char **environ;

/**
 * execute_command - Executes a command using fork and execve
 * @cmd: command string
 */
void execute_command(char *cmd)
{
	pid_t pid;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("./hsh");
		return;
	}
	if (pid == 0)
	{
		/* child process */
		if (execve(argv[0], argv, environ) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* parent process waits for child */
		waitpid(pid, NULL, 0);
	}
}
