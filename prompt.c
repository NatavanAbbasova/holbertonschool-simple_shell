#include "shell.h"

/**
 * print_prompt - Displays the shell prompt only if input is interactive
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}
