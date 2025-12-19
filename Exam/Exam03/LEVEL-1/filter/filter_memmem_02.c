#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	for (size_t i = 0; s[i]; i++)
		len++;
	return (len);
}
int	read_input(char **buf, size_t *len)
{
	char	*tmp;
	int		read_ret;
	size_t	total_size;
	size_t	BUFFER_SIZE;

	total_size = 0;
	BUFFER_SIZE = 8192;
	*buf = NULL;
	while (1)
	{
		tmp = realloc(*buf, total_size + BUFFER_SIZE);
		if (!tmp)
		{
			perror("Error");
			return (0);
		}
		*buf = tmp;
		read_ret = read(0, *buf + total_size, BUFFER_SIZE);
		if (read_ret < 0)
		{
			perror("Error");
			return (0);
		}
		if (read_ret == 0)
			break ;
		total_size += read_ret;
	}
	*len = total_size;
	return (1);
}
void	filter(char *haystack, size_t haystack_len, char *needle,
		size_t needle_len)
{
	char	*b_end;
	char	*found;
	char	*tmp;

	tmp = haystack;
	b_end = haystack + haystack_len;
	while (tmp < b_end)
	{
		found = memmem(haystack, haystack_len, needle, needle_len);
		if (found)
		{
			write(1, tmp, found - tmp);
			for (size_t i = 0; i < needle_len; i++)
				write(1, '*', 1);
			tmp = found + needle_len;
			return ;
		}
		else
		{
			write(1, tmp, b_end - tmp);
			break ;
		}
	}
}
int	main(int argc, char **argv)
{
	char	*haystack;
	size_t	haystack_len;
	size_t	needle_len;

	if (argc != 2 || !argv[1][0])
		return (1);
	needle_len = ft_strlen(argv[1]);
	if (!read_input(&haystack, &haystack_len))
	{
		free(haystack);
		return (1);
	}
	filter(haystack, haystack_len, argv[1], needle_len);
	free(haystack);
	return (0);
}
