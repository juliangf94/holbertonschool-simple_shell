#include "shell.h"

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Nom de la variable
 * Return: Valeur de la variable ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = _strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * _which - Trouve le chemin complet d'une commande dans le PATH
 * @command: Nom de la commande
 * Return: Chemin complet ou NULL si non trouvée
 */
char *_which(char *command)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;

	/* Si c'est déjà un chemin direct (/bin/ls) */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path || !*path)
		return (NULL);

	path_copy = _strdup(path);
	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(_strlen(token) + _strlen(command) + 2);
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * _resolve_path - Résout le chemin d'une commande
 * @cmd: Commande à résoudre
 * Return: Chemin complet ou NULL si non trouvée ou non exécutable
 */
char *_resolve_path(char *cmd)
{
	char *path;

	if (!cmd)
		return (NULL);

	/* Si commande avec / */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1) /* fichier n’existe pas */
		{
			fprintf(stderr, "./shell: %s: not found\n", cmd);
			return (NULL);
		}
		if (access(cmd, X_OK) == -1) /* pas exécutable */
		{
			fprintf(stderr, "./shell: %s: Permission denied\n", cmd);
			return (NULL);
		}
		return (cmd); /* fichier existant et exécutable */
	}

	/* Sinon recherche dans PATH */
	path = _which(cmd);
	if (!path) /* non trouvé dans PATH */
		fprintf(stderr, "./shell: %s: not found\n", cmd);
	else if (access(path, X_OK) == -1) /* trouvé mais pas exécutable */
	{
		fprintf(stderr, "./shell: %s: Permission denied\n", cmd);
		free(path);
		return (NULL);
	}

	return (path); /* mallocé ou NULL */
}
