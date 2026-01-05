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
 * Return:* Retour:
 *   2 si exit,
 *   1 si env,
 *   0 sinon
 */
int handle_builtins(char **argv)
{
	if (!argv[0])
		return (0);

	if (_strcmp(argv[0], "exit") == 0)
		return (2);

	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}
