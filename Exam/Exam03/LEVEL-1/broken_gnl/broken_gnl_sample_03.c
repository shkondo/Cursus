#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*ft_realloc_concat(char *old_str, char c)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	len = 0;
	if (old_str)
		len = ft_strlen(old_str);
	new_str = (char *)malloc(sizeof(char) * (len + 2));
	if (!new_str)
	{
		free(old_str);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_str[i] = old_str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(old_str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	b_read = 0;
	static int	b_pos = 0;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (b_pos >= b_read) //
		{
			b_read = read(fd, buffer, BUFFER_SIZE);
			b_pos = 0;
			if (b_read <= 0)
				break ;
		}
		line = ft_realloc_concat(line, buffer[b_pos]);
		if (!line)
			return (NULL);
		b_pos++;
		if (buffer[b_pos - 1] == '\n')
			break ;
	}
	if (!line || ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
