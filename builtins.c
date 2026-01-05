#include "shell.h"

/**
 * print_env - Affiche toutes les variables d'environnement
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_builtins - Gère les commandes intégrées
 * @argv: Tableau des arguments de la commande
 * @line: Ligne de commande complète
 * Return: 1 si une commande intégrée a été exécutée, 0 sinon
 */
int handle_builtins(char **argv, char *line)
{
	if (!argv[0])
		return (1);

	if (_strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(2);
	}

	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	return (0);
}
