#include "shell.h"

/**
 * main - Simple shell
 * @ac: Nombre d'arguments
 * @av: Tableau des arguments
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	int last_status = 0;
	int counter = 0;

	(void)ac;
	signal(SIGINT, handle_sigint);

	while (1)
	{
		counter++;
		print_prompt();
		if (getline(&line, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(last_status);
		}
		last_status = handle_line(line, av[0], counter, last_status);
	}
	return (last_status);
}
