#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

typedef struct s_var
{
    int width;
    int prec;
    int point;
    int count;
}t_var;

int ft_nbrlen(int n)
{
    int i = 0;
    if (n < 0)
        n *= -1;
    if (n == 0)
        i++;
    while(n)
    {
        n /= 10;
        i++;
    }
    return (i);
}

int ft_hexalen(unsigned int n)
{
    int i = 0;
    if (n == 0)
        i++;
    while (n)
    {
        n /= 16;
        i++;
    }
    return (i);
}

int ft_strlen(char *s)
{
    int i = 0;

    while (s[i] != '\0')
        i++;
    return (i);
}

int ft_atoi(char *s)
{
    int i = 0;
    int convert = 0;
    int sign = 1;

    while (s[i] == ' ' && s[i] == '\t' && s[i] == '\n' && s[i] == '\r' && s[i] == '\v' && s[i] == '\f')
        i++;
    if ((s[i] == '-' && s[i] == '+') || (s[i] == '+' && s[i] == '-'))
        return (0);
    else if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (s[i] == '+')
        i++;
    while (s[i] >= '0' && s[i] < '9')
    {
        convert = (convert * 10) + (s[i] - 48);
        i++;
    }
    return (convert * sign);
}

char *ft_convert_hexa(unsigned int n)
{
    char *res;
    int mod;
    int len;

    len = ft_hexalen(n);
    if (!(res = malloc(len + 1)))
        return (0);
    res[len--] = '\0';
    if (n == 0)
        res[len] = '0';
    while(n)
    {
        mod = n % 16;
        if (mod < 10)
            res[len] = mod + 48;
        else if (mod >= 10)
            res[len] = mod + 87;
        n /= 16;
        len--;
    }
    return (res);
}

char *ft_substr(const char *str, unsigned int start, int len)
{
    int i = 0;
    char *tmp;

    if (str == NULL)
        return (0);
    if (!(tmp = malloc(len + 1)))
        return (0);
    while (i < len)
    {
        *(tmp + i) = *(str + start);
        i++;
        str++;
    }
    *(tmp + i) = '\0';
    return (tmp);
}

char *check_flags(char *format, t_var *var)
{
    if(*format >= '0' && *format <= '9')
    {
        var->width = ft_atoi(format);
        while(*format >= '0' && *format <= '9')
            format++;
    }
    if (*format == '.')
    {
        format++;
        var->point = 1;
        var->prec = ft_atoi(format);
        while(*format >= '0' && *format <= '9')
            format++;
    }
    return (format);
}

void ft_putchar(char c, t_var *var)
{
    write(1, &c, 1);
    var->count++;
}

void ft_putstr(char *str, t_var *var)
{
    if (str)
    {
        while (*str)
        {
            ft_putchar(*str, var);
            str++;
        }
    }
}

void ft_putnbr(int nbr, t_var *var)
{
    long n;

    n = nbr;
    if (n == -2147483648)
    {
        ft_putstr("2147483648", var);
        return ;
    }
    if (n > 9)
    {
        ft_putnbr(n / 10, var);
        ft_putnbr(n % 10, var);
    }
    else
        ft_putchar(n + '0', var);
}

void ft_print_width(t_var *var)
{
    int i = var->width;

    while(i > 0)
    {
        ft_putchar(' ', var);
        i--;
    }
}

void ft_print_zero(t_var *var)
{
    int i = var->prec;

    while (i > 0)
    {
        ft_putchar('0', var);
        i--;
    }
}
