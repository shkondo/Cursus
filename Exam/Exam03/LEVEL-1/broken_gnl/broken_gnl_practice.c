#include <broken_gnl.h>

char	*ft_strchr(char *s, int c)
{
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c)
			return (s + i);
	}
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	for (size_t i = 0; s[i]; i++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!dst || !src)
		return (NULL);
	for (size_t i = 0; i < n; i++)
		((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst || !src)
		return (NULL);
	if (dst > src)
	{
		for (int i = n; i > 0; i--)
			((char *)dst)[i - 1] = ((char *)src)[i - 1];
	}
	if (dst != src)
	{
		for (int i = 0; i < n; i++)
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	char	*tmp;
	size_t	size1;
	size_t	total_size;

	if (!s1 || !s2)
		return (0);
	size1 = *s1 ? ft_strlen(*s1) : 0;
	total_size = size1 + size2;
	tmp = malloc(total_size + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[total_size] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}
int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}
char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*ret;
	char		*tmp;
	int			read_ret;

	ret = NULL;
	tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
		{
			free(ret);
			return (NULL);
		}
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret < 0)
		{
			free(ret);
			return (NULL);
		}
		if (read_ret == 0)
		{
			if (ret)
				return (ret);
			free(ret);
			return (NULL);
		}
		b[read_ret] = '\0';
		tmp = ft_strchr(b, '\n');
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return (ret);
}

int	main(void)
{
	int	fd;

	fd = open('file.txt', O_RDONLY);
	if (fd < 0)
		return (1);
	get_next_line(fd);
	return (0);
}
