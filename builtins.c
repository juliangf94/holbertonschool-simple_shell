#include "shell.h"

/**
 * print_env - Affiche toutes les variables d'environnement
 *
 * Return: void
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
 * @line: La ligne de commande lue
 * @last_status: Le dernier statut de sortie
 *
 * Return: 0 si env, -1 si non trouvé, ou exit le shell
 */
int handle_builtins(char **argv, char *line, int last_status)
{
	int exit_code = last_status;

	if (!argv[0])
		return (-1);

	if (_strcmp(argv[0], "exit") == 0)
	{
		if (argv[1])
		{
			exit_code = _atoi(argv[1]);
			if (exit_code < 0)
				exit_code = 2;
		}
		free(line);
		exit(exit_code);
	}

	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (0);
	}

	return (-1);
}
