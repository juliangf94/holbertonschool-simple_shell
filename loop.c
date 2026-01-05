#include "shell.h"

/**
 * print_prompt - Affiche le prompt du shell
 * Return: Rien
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisboring$ ");
		fflush(stdout);
	}
}

/**
 * handle_line - Traite une ligne de commande
 * @line: La ligne de commande à traiter
 * Return: Rien
 */
void handle_line(char *line)
{
	char *argv[1024], *full_path;
	int i = 0;

	if (line[_strlen(line) - 1] == '\n')
		line[_strlen(line) - 1] = '\0';

	argv[0] = strtok(line, " \t");
	while (argv[i])
		argv[++i] = strtok(NULL, " \t");

	if (handle_builtins(argv, line))
		return;

	full_path = _resolve_path(argv[0]);

	if (!full_path)
	{
		fprintf(stderr, "./shell: %s: not found\n", argv[0]);
		return;
	}
	if (access(full_path, X_OK) == -1)
	{
		fprintf(stderr, "./shell: %s: Permission denied\n", argv[0]);
		if (full_path != argv[0])
			free(full_path);
		return;
	}
	execute_command(full_path, argv);

	if (full_path != argv[0])
		free(full_path);
}
