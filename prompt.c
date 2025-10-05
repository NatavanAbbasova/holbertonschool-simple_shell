#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Shell main loop */
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
		if (nread == -1)  /* EOF */
		{
			free(line);
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0'; /* remove newline */

		if (line[0] == '\0') /* skip empty input */
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
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], argv[0]);
			_exit(127);
		}
		else  /* parent */
			waitpid(pid, &status, 0);
	}
}
