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
 * handle_line - traite une ligne de commande
 * @line: ligne à exécuter (doit être mallocée si free line est utilisé)
 */
void handle_line(char *line)
{
	char *argv[1024], *full_path;
	int i = 0, ret;

	if (!line)
		return;

	/* supprime '\n' final si présent */
	if (_strlen(line) > 0 && line[_strlen(line) - 1] == '\n')
		line[_strlen(line) - 1] = '\0';

	/* découpage en arguments */
	argv[i] = strtok(line, " \t");
	while (argv[i])
		argv[++i] = strtok(NULL, " \t");

	/* built-ins */
	ret = handle_builtins(argv);
	if (ret == 1) /* env */
		return;
	if (ret == 2) /* exit */
	{
		free(line);
		exit(0);
	}

	/* résolution chemin et exécution */
	full_path = _resolve_path(argv[0]);
	if (!full_path)
		return;

	execute_command(full_path, argv);

	if (full_path != argv[0])
		free(full_path);
}
