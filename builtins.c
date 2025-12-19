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
