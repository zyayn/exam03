#include <unistd.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(const char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1 = ft_strlen(s1);
	int		len2 = ft_strlen(s2);
	char	*result = (char *)malloc(len1 + len2 + 1);
    int		i = 0;

	if (!result)
		return (NULL);
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

int	get_npos(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_theline(char **overflow, int npos)
{
	char	*theline;
    char	*temp;
	int		len = 0;

	while ((*overflow)[len] && len < npos)
		len++;
	theline = (char *)malloc(len + 2);
	if (!theline)
		return (NULL);
	len = 0;
	while ((*overflow)[len] && len < npos)
	{
		theline[len] = (*overflow)[len];
		len++;
	}
	theline[len] = (*overflow)[len];
	theline[len + 1] = '\0';
	temp = ft_strjoin(*overflow + npos + 1, "");
	free(*overflow);
	*overflow = temp;
	return (theline);
}

int	readbuf(int fd, char **overflow)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	int		count;
	int		npos;

	npos = get_npos(*overflow);
	while (npos < 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count <= 0)
			return (count);
		buf[count] = '\0';
		temp = ft_strjoin(*overflow, buf);
		free(*overflow);
		*overflow = temp;
		npos = get_npos(*overflow);
	}
	return (npos);
}

char	*get_next_line(int fd)
{
	static char	*overflow = NULL;
	int			npos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!overflow)
	{
		overflow = (char *)malloc(1);
		if (!overflow)
			return (NULL);
		overflow[0] = '\0';
	}
	npos = readbuf(fd, &overflow);
	if (npos == 0 && !overflow[0])
	{
		free(overflow);
		overflow = NULL;
		return (NULL);
	}
	return (get_theline(&overflow, npos));
}
