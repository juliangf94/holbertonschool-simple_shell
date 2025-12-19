#include "shell.h"

/**
 * main - Simple shell with PATH resolution
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL, *full_path = NULL;
	size_t len = 0;
	ssize_t read;
	char *argv[1024];
	int i;
	/* Gestion du signal Ctrl+C */
	handle_sigint(0);
	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisboring$ ");
			fflush(stdout); /* Ajoute ceci pour garantir l'affichage immédiat */
		}

		read = getline(&line, &len, stdin);
		if (read == -1) /* Gestion de Ctrl+D */
		{
			if (isatty(STDIN_FILENO)) printf("\n");
			break;
		}

		if (line[read - 1] == '\n') line[read - 1] = '\0';

		/* Tokenization (découpage) */
		i = 0;
		argv[i] = strtok(line, " \t");
		while (argv[i])
			argv[++i] = strtok(NULL, " \t");

		if (argv[0] == NULL)
			continue;

		/*GESTION DU BUILT-IN 'exit' */
		if (_strcmp(argv[0], "exit") == 0)
		{
			free(line);
			exit(0);
		}
		if (_strcmp(argv[0], "env") == 0)
		{
			print_env();
			continue; /* On revient au prompt sans fork */
		}
		/* Recherche de la commande dans le PATH */
		full_path = _which(argv[0]);

		if (full_path == NULL)
		{
			fprintf(stderr, "./shell: %s: not found\n", argv[0]);
			continue;
		}

		/* Exécution (fork se fait ici) */
		execute_command(full_path, argv);

		/* On libère la mémoire de full_path si c'était un malloc de _which */
		if (full_path != argv[0])
			free(full_path);
	}
	free(line);
	return (0);
}
