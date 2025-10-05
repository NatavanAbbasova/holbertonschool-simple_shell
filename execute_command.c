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
	char *args[1024];
	char *token;
	int i = 0;
	pid_t pid;
	int status;

	/* tokenize input line */
	token = strtok(line, " \t");
	while (token && i < 1023)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (!args[0])
		return; /* empty input */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		/* child process */
		char *path = args[0];

		/* if not absolute path, search PATH */
		if (access(path, X_OK) == -1)
		{
			char *env_path = getenv("PATH");
			char *dir, fullpath[1024];
			if (env_path)
			{
				dir = strtok(env_path, ":");
				while (dir)
				{
					snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, args[0]);
					if (access(fullpath, X_OK) == 0)
					{
						path = fullpath;
						break;
					}
					dir = strtok(NULL, ":");
				}
			}
		}

		if (execve(path, args, envp) == -1)
		{
			dprintf(2, "./hsh: 1: %s: not found\n", args[0]);
			_exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

