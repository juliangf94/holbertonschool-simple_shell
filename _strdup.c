#include "shell.h"

/**
* _strdup - duplique une chaîne de caractère
* @str: chaîne a dupliquer
*
* Return: pointeur vers la nouvelle chaine ou NULL si echec
*/

char *_strdup(char *str)
{
	char *copy;
	unsigned int i, len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len])
		len++;

	copy = malloc(sizeof(char) * (len + 1));

	if (copy == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		copy[i] = str[i];
	copy[i] = '\0';

	return (copy);
}
