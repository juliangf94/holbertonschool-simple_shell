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
 *   2 si exit,
 *   1 si env,
 *   0 sinon
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