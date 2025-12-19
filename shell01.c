#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Simple shell 0.1
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char *argv[2];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisboring$ ");
		read = getline(&line, &len, stdin);

		if (read == -1) /* EOF (Ctrl+D) */
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		/* Supprimer le '\n' à la fin de la ligne */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0') /* Entrée vide */
			continue;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0) /* Enfant */
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./shell"); /* Message d'erreur formaté */
				exit(EXIT_FAILURE);
			}
		}
		else /* Parent */
		{
			wait(&status); /* Attendre l’enfant */
		}
	}

	free(line);
	return 0;
}
