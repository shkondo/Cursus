#include <stdlib.h>
#include <unistd.h>

void	sorted(char *str)
{
	char	tmp;

	for (size_t i = 0; str[i]; i++)
	{
		for (size_t j = i + 1; str[j]; j++)
		{
			if (str[i] > str[j])
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
		}
	}
}

void	perm(char *str, char *res, int *used, size_t dep, size_t len)
{
	if (dep == len)
	{
		write(1, res, len);
		write(1, "\n", 1);
		return ;
	}
	for (size_t i = 0; i < len; i++)
	{
		if (used[i])
			continue ;
		used[i] = 1;
		res[dep] = str[i];
		perm(str, res, used, dep + 1, len);
		used[i] = 0;
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	char	*res;
	int		*used;
	int		len;

	if (argc != 2)
		return (1);
	len = 0;
	while (argv[1][len])
		len++;
	str = malloc(len + 1);
	res = malloc(len + 1);
	used = calloc(len, sizeof(int));
	if (!str || !res || !used)
	{
		free(str);
		free(res);
		free(used);
		return (1);
	}
	for (size_t i = 0; i < len; i++)
		str[i] = argv[1][i];
	str[len] = '\0';
	sorted(str);
	perm(str, res, used, 0, len);
	free(str);
	free(res);
	free(used);
	return (0);
}
