#include "shell.h"

/**
 * execute_command - Exécute une commande et renvoie son statut
 * @full_path: Chemin complet de la commande
 * @argv: Tableau des arguments
 * Return: Le statut de sortie de la commande
 */
int execute_command(char *full_path, char **argv)
{
	pid_t pid;
	int status;
	int exit_status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0) /* Processus enfant */
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror("execve");
			exit(126);
		}
	}
	else /* Processus parent */
	{
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}
