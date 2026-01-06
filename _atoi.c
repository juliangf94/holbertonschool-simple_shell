#include "shell.h"

/**
 * _atoi - Convertit une chaîne en entier
 * @s: Chaîne à convertir
 * Return: Entier converti, ou -1 en cas d'erreur
 */

int _atoi(char *s)
{
    int i = 0, result = 0, sign = 1;
    int has_digit = 0;
    
    if (!s || !s[0])
        return (-1);
    
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (s[i] == '+')
        i++;
    
    while (s[i] >= '0' && s[i] <= '9')
    {
        has_digit = 1;
        result = result * 10 + (s[i] - '0');
        i++;
    }
    
    if (!has_digit)
        return (-1);
    
    return (result * sign);
}