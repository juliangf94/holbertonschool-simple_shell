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
 * @prog_name: nom du programme shell (pour les messages d'erreur)
 * Return: Rien
 */
void handle_line(char *line, char *prog_name)
{
	char *argv[1024], *full_path;
	int i = 0;
	int ret;

	if (!line)
		return;
	/* Supprime le '\n' final si présent */
	if (_strlen(line) > 0 && line[_strlen(line) - 1] == '\n')
		line[_strlen(line) - 1] = '\0';

	/* Découpage en arguments */
	argv[i] = strtok(line, " \t");
	while (argv[i])
		argv[++i] = strtok(NULL, " \t");

	if (!argv[0])
		return; /* ligne vide */

	/* Built-ins */
	ret = handle_builtins(argv);
	if (ret == 1) /* env exécuté */
		return;
	if (ret == 2) /* exit demandé */
	{
		free(line);
		exit(0);
	}
	/* Résolution du chemin */
	full_path = _resolve_path(argv[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, argv[0]);
		return;
	}
	/* Exécution de la commande */
	execute_command(full_path, argv);
	/* Libération si _resolve_path a mallocé */
	if (full_path != argv[0])
		free(full_path);
}
