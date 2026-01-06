#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 * Return: the integer value, or 0 if no valid conversion
 */
int _atoi(char *s)
{
    int i = 0;
    int sign = 1;
    int result = 0;
    
    if (!s)
        return (0);
    
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (s[i] == '+')
    {
        i++;
    }

    while (s[i] >= '0' && s[i] <= '9')
    {
        result = result * 10 + (s[i] - '0');
        i++;
    }
    
    return (result * sign);
}