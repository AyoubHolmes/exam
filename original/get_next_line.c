#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char    *ft_strdup(const char *s)
{
	int i = 0;
	int len = 0;
	char *tmp;

	while (s[len])
		len++;
	if (!(tmp = (char *)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
	int i = 0;
	int j = 0;
	char *tmp;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	if (!(tmp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = '\0';
	return (tmp);
}

char    *ft_substr(char const *s, unsigned int start, int len)
{
	int i = 0;
	char *tmp;

	if (!(tmp = (char *)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		*(tmp + i) = *(s + start);
		i++;
		s++;
	}
	*(tmp + i) = '\0';
	return (tmp);
}

char    *ft_strchr(const char *s, int c)
{
	int i = 0;
	char ch = c;

	while (s[i] && s[i] != ch)
		i++;
	if (s[i] == ch)
		return ((char *)&s[i]);
	else
		return (NULL);
}

int read_line(char **str, char **line)
{
	int i = 0;
	char *tmp;

	if (*str)
	{
		while ((*str)[i] && (*str)[i] != '\n')
			i++;
		if ((*str)[i] == '\n')
		{
			*line = ft_substr(*str, 0, i);
			tmp = *str;
			*str = ft_strdup(*str + i + 1);
			free(tmp);
		}
		else if (str[i] == '\0')
		{
			*line = ft_strdup(*str);
			free(*str);
			*str = NULL;
			return (0);
		}
	}
	return (1);
}

int get_next_line(char **line)
{
	char buff[1025];
	static char *str;
	char *tmp;
	int r;

	while ((r = read(0, buff, 1024)) > 0)
	{
		buff[r] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (r < 0)
		return (-1);
	else if (!r && (str == NULL || str[0] == '\0'))
	{
		*line = ft_strdup("");
		return (0);
	}
	return (read_line(&str, line));
}
int		main(int argc, char **argv)
{
	char	*line;
    int i = 0;

	while ((i = get_next_line(&line)) == 1)
	{
		printf("%s\n" ,line);
		free(line);
	}
    printf("%s" ,line);
}