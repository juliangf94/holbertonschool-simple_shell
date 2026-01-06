#include "shell.h"

/**
 * print_prompt - Affiche le prompt du shell
 * Return: Rien
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisboring$ ");
		fflush(stdout);
	}
}

/**
 * handle_line - traite une ligne de commande
 * @line: ligne à exécuter (doit être mallocée si free line est utilisé)
 * @prog_name: nom du programme shell (pour les messages d'erreur)
 * Return: Rien
 */
int handle_line(char *line, char *prog_name, int counter, int last_status)
{
    char *argv[1024], *full_path;
    int i = 0, ret_builtin, final_status = 0;

    if (!line) return (last_status);

    /* Nettoyage du \n */
    if (_strlen(line) > 0 && line[_strlen(line) - 1] == '\n')
        line[_strlen(line) - 1] = '\0';

    /* Tokenization */
    argv[i] = strtok(line, " \t");
    while (argv[i])
        argv[++i] = strtok(NULL, " \t");
    
    if (!argv[0]) return (last_status);

    /* 1. Test des Built-ins */
    ret_builtin = handle_builtins(argv, line, last_status);
    if (ret_builtin != -1)
        return (ret_builtin);

    /* 2. Résolution du chemin */
    full_path = _resolve_path(argv[0]);
    if (!full_path)
    {
        fprintf(stderr, "%s: %d: %s: not found\n", prog_name, counter, argv[0]);
        return (127);
    }

    /* 3. Exécution */
    final_status = execute_command(full_path, argv);

    if (full_path != argv[0])
       free(full_path);

    return (final_status);
}