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
 * @line: ligne saisie
 */
void handle_line(char *line)
{
	char *argv[1024], *full_path;
	int i = 0;
	int ret;

	/* Supprime le '\n' final si présent */
	if (_strlen(line) > 0 && line[_strlen(line) - 1] == '\n')
		line[_strlen(line) - 1] = '\0';

	/* Découpage en arguments */
	argv[i] = strtok(line, " \t");
	while (argv[i])
		argv[++i] = strtok(NULL, " \t");

	/* Built-ins */
	ret = handle_builtins(argv);
	if (ret == 1) /* env exécuté */
		return;
	if (ret == 2) /* exit demandé */
	{
		free(line);
		exit(0);
	}

	/* Résolution du chemin et exécution */
	full_path = _resolve_path(argv[0]);
	if (!full_path)
		return;

	execute_command(full_path, argv);
	if (full_path != argv[0])
		free(full_path);
}
