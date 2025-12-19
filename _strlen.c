#include "shell.h"

/**
 *_strlen - longueur de la chaine de caractere
 *@s: pointeur vers la chaine
 *
 *Return: la longueur de la chaine
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}
