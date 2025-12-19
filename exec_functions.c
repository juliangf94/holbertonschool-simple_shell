#include "shell.h"

/**
 * execute_command - Exécute une commande donnée avec ses arguments
 * @full_path: Chemin complet de la commande
 * @argv: Tableau des arguments
 */
void execute_command(char *full_path, char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0) /* Processus enfant */
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else /* Processus parent */
	{
		wait(&status);
	}
}
