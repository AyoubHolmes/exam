#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *s)
{
    int i = 0;
    if(s)
    {
        while(s[i])
            i++;
    }
    return (i);
}

char *ft_strdup(const char *s)
{
    char *tmp;
    int len = 0;
    int i = 0;

    while (s[len])
        len++;
    if(!(tmp = malloc(len + 1)))
        return (NULL);
    while (i < len)
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char *ft_strjoin(const char *s1, const char *s2)
{
    char *tmp;
    int i = 0;
    int j = 0;

    if (s1 == NULL)
        return (ft_strdup(s2));
    if (s2 == NULL)
        return (ft_strdup(s1));
    if(!(tmp = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
        return(NULL);
    while (s1[i])
    {
        tmp[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        tmp[i + j] = s1[j];
        j++;
    }
    tmp[i + j] = '\0';
    return (tmp);
}

char *ft_substr(char const *s, unsigned int start, int len)
{
    int i = 0;
    char *tmp;

    if(s == NULL)
        return (NULL);
    if (!(tmp = malloc(len + 1)))
        return (NULL);
    while (i < len)
    {
        *(tmp + i) = *(s + start);
        s++;
        i++;
    }
    *(tmp + i) = '\0';
    return (tmp);
}

char *ft_strchr(const char *s, int c)
{
    int i = 0;
    char ch = c;

    while(s[i] && s[i] != ch)
        i++;
    if (s[i] == ch)
        return ((char *)&s[i]);
    else
        return (NULL);
}