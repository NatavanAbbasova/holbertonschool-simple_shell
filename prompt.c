#include "shell.h"

/**
 * print_prompt - Displays the shell prompt only in interactive mode
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}
