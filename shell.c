#include "shell.h"

/**
 * main - Simple shell
 *
 * Return: Always 0
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		print_prompt();
		if (getline(&line, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		handle_line(line, "hsh");
	}
	free(line);
	return (0);
}
