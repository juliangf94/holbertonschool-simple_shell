int _atoi(char *s)
{
    int i = 0, result = 0, sign = 1;
    
    if (!s)
        return (-1);
    
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (s[i] == '+')
        i++;
    
    if (!s[i])
        return (-1);
    
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (-1);
        result = result * 10 + (s[i] - '0');
        i++;
    }
    
    return (result * sign);
}