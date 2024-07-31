#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (s);
        s++;
    }
    return (NULL);
}

size_t ft_strlen(const char *s)
{
    size_t i = 0;
    while (s[i])
        i++;
    return (i);
}

void ft_strcpy(char *dst, const char *src)
{
    while (*src)
        *dst++ = *src++;
    *dst = '\0';
}

char *ft_strdup(const char *src)
{
    size_t len = ft_strlen(src) + 1;
    char *dst = malloc(len);
    if (dst == NULL)
        return (NULL);
    ft_strcpy(dst, src);
    return (dst);
}

char *ft_strjoin(char *s1, const char *s2)
{
    size_t s1_len = ft_strlen(s1);
    size_t s2_len = ft_strlen(s2);
    char *join = malloc(s1_len + s2_len + 1);

    if (!s1 || !s2 || !join)
        return (NULL);
    ft_strcpy(join, s1);
    ft_strcpy(join + s1_len, s2);
    free(s1);
    return (join);
}

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char *line;
    char *newline;
    int countread;
    int to_copy;

    line = ft_strdup(buf);
    if (!line)
        return (NULL);
    
    while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[countread] = '\0';
        line = ft_strjoin(line, buf);
        if (!line)
            return (NULL);
    }

    if (countread == -1)
    {
        free(line);
        return (NULL);
    }

    if (ft_strlen(line) == 0)
    {
        free(line);
        return (NULL);
    }

    if (newline != NULL)
    {
        to_copy = newline - line + 1;
        ft_strcpy(buf, newline + 1);
    }
    else
    {
        to_copy = ft_strlen(line);
        buf[0] = '\0';
    }
    line[to_copy] = '\0';
    return (line);
}
/*
int main(int argc, char **argv)
{
    int fd;
    char *line;

    fd = open(argv[1], O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
	close(fd);
    return (0);
}
*/