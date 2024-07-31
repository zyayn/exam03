#include <unistd.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1 = ft_strlen(s1);
	int		len2 = ft_strlen(s2);
	char	*s = malloc (len1 + len2 + 1);
	int		i = 0;

	if (!s)
		return (NULL);
	while (*s1)
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}

char	*get_theline(char **overflow, int npos)
{
	char	*result;
	char	*temp;
	int		i = 0;

	while ((*overflow)[i] && i < npos)
		i++;
	result = malloc(i + 2);
	if (!result)
		return (NULL);
	i = 0;
	while ((*overflow)[i] && i < npos)
	{
		result[i] = (*overflow)[i];
		i++;
	}
	result[i] = (*overflow)[i];
	result[i + 1] = '\0';
	temp = ft_strjoin(*overflow + npos + 1, "");
	free(*overflow);
	*overflow = temp;
	return (result);
}

int	get_npos(char *s)
{
	int	i = 0;

	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
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
		overflow = malloc(1);
		if (!overflow)
			return (NULL);
		overflow[0] = '\0';
	}
	npos = readbuf(fd, &overflow);
	if (!npos && !overflow[0])
	{
		free(overflow);
		overflow = NULL;
		return (NULL);
	}
	return (get_theline(&overflow, npos));
}

int	main()
{
	int i = 0;
	char	*line;

	while (i < 3)
	{
		line = get_next_line(0);
		free(line);
		i++;
	}
	return (0);
}