#include "shell.h"

/**
 * handle_sigint - Gère le signal Ctrl+C
 * @sig: Le numéro du signal (non utilisé ici)
 */
void handle_sigint(int sig)
{
	(void)sig; /* Pour éviter l'erreur "unused parameter" */

	/* On saute une ligne et on réaffiche le prompt */
	write(STDOUT_FILENO, "\n#cisboring$ ", 13);
}
