#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct s_var
{
    int width;
    int prec;
    int point;
    int count;
} t_var;

int ft_nbrlen(int n)
{
    int i = 0;

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
    while(n)
    {
        n /= 16;
        i++;
    }
    return (i);
}

int ft_strlen(char *s)
{
    int i = 0;

    while(s[i] != '\0')
        i++;
    return (i);
}

int ft_atoi(char *s)
{
    int i = 0;
    int convert = 0;
    int sign = 1;

    while(s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
        i++;
    if (s[i] == '+' && s[i + 1] == '-')
        return (0);
    if (s[i] == '+')
        i++;
    else if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        convert = (convert * 10) + (s[i] + '0');
        i++;
    }
    return (convert);
}

char *ft_convert_hexa(unsigned int n)
{
    int mod;
    int len;
    char *res;

    len = ft_hexalen(n);
    if(!(res = malloc(len + 1)))
        return (0);
    res[len--] = '\0';
    if (n == 0)
        res[len] == '0';
    while (n)
    {
        mod = n % 16;
        if (mod < 10)
            res[len] = mod + 48;
        else if (mod >= 10)
            res[len] = mod + 87;
        len--;
        n /= 16;
    }
    return (res);   
}

char *ft_substr(const char *str, unsigned int start, int len)
{
    int i = 0;
    char *tmp;

    if(!(tmp = malloc(len + 1)))
        return (NULL);
    if (str == NULL)
        return (NULL);
    while (i < len)
    {
        *(tmp + i) = *(str + start);
        i++;
        str++;
    }
    *(tmp + i) = '\0';
    return (tmp);
}

char *check_flag(char *format, t_var *var)
{
    if(*format >= '0' && *format <= '9')
    {
        var->width = ft_atoi(format);
        while (*format >= '0' && *format <= '9')
            format++;
    }
    if(*format == '.')
    {
        format++;
        var->point = 1;
        var->prec = ft_atoi(format);
        while (*format >= '0' && *format <= '9')
            format++;
    }
    return ((char *)format);
}

void ft_putchar(char c, t_var *var)
{
    write(1,&c,1);
    var->count++;
}

void ft_putstr(char *s, t_var *var)
{
    if(s)
    {
        while(*s)
        {
            ft_putchar(*s, var);
            s++;
        }
    }
}

void ft_putnbr(int n, t_var *var)
{
    long nbr;

    nbr = n;
    if (nbr = -2147483648)
    {
        ft_putstr("2147483648", var);
        return ;
    }
    if (nbr > 9)
    {
        ft_putnbr(n / 10, var);
        ft_putnbr(n % 10, var);
    }
    else
        ft_putchar(nbr + '0', var);
}

void    print_width(t_var *var)
{
    int i;

    i = var->width;
    while (i > 0)
    {
        ft_putchar(' ', var);
        i--;
    }
}

void    print_zero(t_var *var)
{
    int i;

    i = var->prec;
    while (i > 0)
    {
        ft_putchar('0', var);
        i--;
    }
}

void    print_dec(t_var *var, va_list lst)
{
    int dec = 0;
    int len = 0;

    // initilizing the variables
    dec = va_arg(lst, int);
    len = ft_nbrlen(dec);
    if(var->point && dec == 0 && var->prec == 0)
        len = 0;
    if (var->point == 0 && dec < 0)
        len++;
    // checking the new width and prec
    var->prec = (var->prec > len) ? var->prec - len : 0;
    var->width = (var->width > len + var->prec) ? var->width - len - var->prec : 0;
    // printing
    if (var->width)
        print_width(var);
    if (dec < 0)
        ft_putchar('-', var);
    if (var->prec)
        print_zero(var);
    if (len > 0)
        ft_putnbr(dec, var);
}

void print_hexa(t_var *var, va_list lst)
{
    unsigned int hexa = 0;
    int len = 0;

    hexa = va_arg(lst, unsigned int);
    len = ft_nbrlen(hexa);
    if (var->point && hexa == 0 && var->prec == 0)
        len = 0;
    var->prec = (var->prec > len) ? var->prec - len : 0;
    var->width = (var->width > var->prec + len) ? var->width - len - var->prec : 0;
    if(var->width)
        print_width(var);
    if (var->prec)
        print_zero(var);
    if(len > 0)
    {
        char *tmp;
        tmp = ft_convert_hexa(hexa);
        ft_putstr(tmp, var);
        free(tmp);
    }
}