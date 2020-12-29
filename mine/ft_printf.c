#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct s_var
{
   int width;
   int prec;
   int point;
   int cont;
}t_var;

/* ************** basics length functions ***************** */

// ft_nbrlen

int ft_nbrlen(int n)
{
    int i = 0;

    if (n < 0)
        n *= 0;
    if (n == 0)
        i++;
    while (n)
    {
        i++;
        n /= 10;
    }
    return (i);
}

// ft_hexalen

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

// ft_strlen

int strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

/* ************** basics convertion functions ***************** */

// ft_atoi

int ft_atoi(char *str)
{
    int sign = 1;
    int convert = 0;
    int i = 0;
    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if ((str[i] == '+' && str[i + 1] == '-') || (str[i] == '-' && str[i + 1] == '+'))
        return (0);
    else if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        convert = (convert * 10) + (str[i] - '0');
        i++;
    }
    return (convert * sign);
}

// ft_convert_hexa

char * ft_convert_hexa(unsigned int n)
{
    char *res;
    int mod;
    int len;

    len = ft_hexalen(n);
    if (!(res = malloc(len + 1)))
        return 0;
    res[len--] = '\0';
    if (n == 0)
        res[len] = '0';
    while (n)
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

/* ************** basics helping functions ***************** */

// ft_substr

// check_flags

/* ************** basics printing functions ***************** */

// ft_putchar

// ft_putstr

// ft_putnbr

// print_width

// print_zero

// print_dec

// print_hexa

// print_str



// ft_printf