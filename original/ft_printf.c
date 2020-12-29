#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct  s_var
{
	int width;
	int prec;
	int point;
	int count;
}               t_var;

int ft_nbrlen(int n)
{
	int i = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int ft_unslen(unsigned int n)
{
	int i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int ft_strlen(const char *s)
{
	int i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

int ft_atoi(const char *str)
{
	int convert;
	int index;
	int sign;

	convert = 0;
	index = 0;
	sign = 1;
	while (str[index] == '\t' || str[index] == '\r' || str[index]  == '\n' || str[index] == '\v' || str[index] == '\f' || str[index] == ' ')
		index++;
	if (str[index] == '+' && str[index + 1] == '-')
		return (0);
	if (str[index] == '+')
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	while (str[index] && str[index] >= '0' && str[index] <= '9')
	{
		convert = (convert * 10) + (str[index] - '0');
		index++; 
	}
	return (convert * sign);
}

char    *ft_convert_hexa(unsigned int n)
{
	char *res;
	int mod;
	int len;

	len = ft_unslen(n);
	if (!(res = malloc(len + 1)))
		return (NULL);
	res[len--] = '\0';
	if (n == 0)
		res[len] = '0';
	while (n)
	{
		mod = n % 16;
		if (mod < 10)
			res[len] = mod + 48;
		if (mod >= 10)
			res[len] = mod + 87;
		n = n / 16;
		len--;
	}
	return (res);
}



char    *check_flags(const char *format, t_var *var)
{
	if (*format >= '0' && *format <= '9')
	{
		var->width = ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format++;
	}
	if (*format == '.')
	{
		var->point = 1;
		format++;
		var->prec = ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format++;
	}
	return ((char *)format);
}

void    ft_putchar(char c, t_var *var)
{
	write(1, &c, 1);
	var->count++;
}

void    ft_putstr(char *str, t_var *var)
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
void    ft_putnbr(int nbr, t_var *var)
{
	long n;

	n = nbr;
	if (n == -2147483648)
    {
	ft_putstr("2147483648",var);
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
void	print_dec(t_var *var, va_list lst)
{
	int dec = 0;
	int len = 0;
	dec = va_arg(lst, int);
	len = ft_nbrlen(dec);
	if (var->point && dec == 0 && var->prec == 0)
		len = 0;
	if (dec < 0 && var->point == 0)
		len++;
	var->prec = (var->prec > len) ? var->prec - len : 0;
	if (dec < 0 && var->point)
		len++;
	var->width = (var->width > len + var->prec) ? var->width - len - var->prec : 0;
	if (var->width)
		print_width(var);
	if (dec < 0)
	{
		dec *= -1;
		ft_putchar('-', var);
	}
	if (var->prec)
		print_zero(var);
	if (len > 0)
		ft_putnbr(dec, var);
}
void    print_hexa(t_var *var, va_list lst)
{
	unsigned int hexa = 0;
	int len = 0;
	hexa = va_arg(lst, unsigned int);
	len = ft_unslen(hexa);
	if (var->point && hexa == 0 && var->prec == 0)
		len = 0;
	var->prec = (var->prec > len) ? var->prec - len : 0;
	var->width = (var->width > len + var->prec) ? var->width - len - var->prec : 0;
	if (var->width)
		print_width(var);
	if (var->prec)
		print_zero(var);
	if (len > 0)
	{
		char *tmp;
		tmp = ft_convert_hexa(hexa);
		ft_putstr(tmp, var);
		free(tmp);
	}
}
void    print_str(t_var *var, va_list lst)
{
	char *str;
	int len;
	str = va_arg(lst, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (var->point && var->prec < len)
		str = ft_substr(str, 0, var->prec);
	var->width = (var->width > ft_strlen(str)) ? var->width - ft_strlen(str) : 0;
	if (var->width)
		print_width(var);
	if (len > 0)
		ft_putstr(str, var);
	if (var->point && var->prec < len)
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

/* int main()
{
	int i =0, j = 0;

	i = printf("format|%6.5d|\n", 252);
	j = ft_printf("format|%6.5d|\n", 252);
	printf("|%d|                      |%d|\n", i , j);

} */