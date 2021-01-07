#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct s_var
{
    int width;
    int point;
    int prec;
    int count;
} t_var;

int ft_nbrlen(int n)
{
    int i = 0;

    if (n < 0)
        n *= -1;
    if (n == 0)
        i++;
    while (n)
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

int ft_strlen(char *str)
{
    int i = 0;

    if (str)
    {
        while (str[i])
            i++;
    }
    return (i);
}

int ft_atoi(const char *str)
{
	int convert;
	int i;
	int sign;

	convert = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\r' || str[i]  == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' && str[i + 1] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
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

char *ft_convert_hexa(unsigned int n)
{
    char *res;
    int len;
    int mod;

    len = ft_hexalen(n);
    if(!(res = malloc(len + 1)))
        return (NULL);
    res[len--] = '\0';
    if (n == 0)
        res[len] = '0';
    while (n)
    {
        mod = n % 16;
        if (mod < 10)
            res[len] = mod + 48;
        else
            res[len] = mod + 87;
        len--;
        n /=16;
    }
    return (res);
}

char *ft_substr(char *str, unsigned int start, int len)
{
    char *tmp;
    int i;
    if (str == NULL)
        return (NULL);
    if (!(tmp = malloc(len + 1)))
        return (NULL);
    i = 0;
    while(i < len)
    {
        *(tmp + i) = *(str + start);
        i++;
        str++; 
    }
    *(tmp + i) = '\0';
    return (tmp);
}

char *check_flags(const char* format ,t_var *var)
{
    if (*format >= '0' && *format <= '9')
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
    return ((char *) format);
}

void ft_putchar(char c, t_var *var)
{
    write(1, &c, 1);
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
// -2147483648
void ft_putnbr(int nbr, t_var *var)
{
    long n = nbr;

    if (n == -2147483648)
    {
        ft_putstr("2147483648", var);
        return ;
    }
    if(n > 9)
    {
        ft_putnbr(n /10, var);
        ft_putnbr(n %10, var);
    }
    else
        ft_putchar(n + '0', var);
}

void    print_width(t_var *var)
{
	int i = 0;
	i = var->width;
	while (i > 0)
	{
		ft_putchar(' ', var);
		i--;
	}
}
void    print_zero(t_var *var)
{
	int i = 0;
	i = var->prec;
	while (i > 0)
	{
		ft_putchar('0', var);
		i--;
	}
}

void print_dec(t_var *var, va_list lst)
{
    int dec;
    int len;

    dec = va_arg(lst, int);
    len = ft_nbrlen(dec);
    if(var->point && dec == 0 && var->prec == 0)
        len = 0;
    if (var->point == 0 && dec < 0)
        len++;
    var->prec = (var->prec > len) ? var->prec - len : 0;
    var->width = (var->width > len + var->prec) ? var->width - var->prec - len : 0;
    if (var->width)
        print_width(var);
    if (dec < 0)
        ft_putchar('-', var);
    if (var->prec)
        print_zero(var);
    if(len > 0)
        ft_putnbr(dec, var);
}

void print_hexa(t_var *var, va_list lst)
{
    unsigned int hexa;
    int len;

    hexa = va_arg(lst, unsigned int);
    len = ft_hexalen(hexa);
    if(var->point && hexa == 0 && var->prec == 0)
        len = 0;
    var->prec = (var->prec > len) ? var->prec - len : 0;
    var->width = (var->width > len + var->prec) ? var->width - var->prec - len : 0;
    if (var->width)
        print_width(var);
    if (var->prec)
        print_zero(var);
    if(len > 0)
    {
        char *tmp = ft_convert_hexa(hexa);
        ft_putstr(tmp, var);
        free(tmp);
    }
}

void print_str(t_var *var, va_list lst)
{
    char *str;
    int len;

    str = va_arg(lst, char *);
    if (!str)
        str = "(null)";
    len = ft_strlen(str);
    if (var->point && len > var->prec)
        str = ft_substr(str, 0, var->prec);
    var->width = (var->width > ft_strlen(str)) ? var->width - ft_strlen(str) : 0;
    if(var->width)
        print_width(var);
    if(len > 0)
        ft_putstr(str, var);
    if (var->point && len > var->prec)
        free(str);
}

int ft_printf(const char *format, ...)
{
    va_list lst;
	t_var   var;

	va_start(lst, format);
	var.count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			var.width = 0;
			var.prec = 0;
			var.point = 0;
			format++;
			while (*format != 'd' && *format != 's' && *format != 'x')
					format = check_flags(format, &var);
			if (*format == 'd')
				print_dec(&var, lst);
			if (*format == 'x')
				print_hexa(&var, lst);
			if (*format == 's')
				print_str(&var, lst);
		}
		else
			ft_putchar(*format, &var);
		format++;
	}
	va_end(lst);
	return(var.count);
}