#include <stdlib.h>
#include <unistd.h>

int	count_to_replace(char *s)
{
	int	opened;
	int	closed;

	opened = 0;
	closed = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == ' ')
			continue ;
		if (s[i] == '(')
			opened++;
		if (s[i] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
	}
	return (opened + closed);
}

int	is_valid(char *s)
{
	int	balance;

	balance = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == ' ')
			continue ;
		if (s[i] == '(')
			balance++;
		else if (s[i] == ')')
		{
			balance--;
			if (balance < 0)
				return (0);
		}
	}
	return (1);
}

void	rip(char *s, int to_replace, int replaced, int len)
{
	char	c;

	if (to_replace == replaced)
	{
		if (is_valid(s))
		{
			write(1, s, len);
			write(1, "\n", 1);
		}
		return ;
	}
	for (int i = 0; i < len; i++)
	{
		if (s[i] == ' ')
			continue ;
		if (s[i] == '(' || s[i] == ')')
		{
			c = s[i];
			s[i] = ' ';
			rip(s, to_replace, replaced + 1, len);
			s[i] = c;
		}
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	int		len;
	int		count;

	if (argc != 2 || !argv[1][0])
		return (0);
	for (int i = 0; argv[1][i]; i++)
		len++;
	s = malloc(len + 1);
	for (int i = 0; i < len; i++)
		s[i] = argv[1][i];
	s[len] = '\0';
	count = count_to_replace(s);
	rip(s, count, 0, len);
	free(s);
	return (0);
}

// permutation

#include <stdlib.h>
#include <unistd.h>;

void	sort(char *s, int len)
{
	char	tmp;

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (s[j] > s[i])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}
}

void	perm(char *s, char *ret, int *used, int dep, int len)
{
	if (dep == len)
	{
		write(1, ret, len);
		write(1, "\n", 1);
		return ;
	}
	for (int i = 0; i < len; i++)
	{
		if (used[i])
			continue ;
		used[i] = 1;
		ret[dep] = s[i];
		perm(s, ret, used, dep + 1, len);
		used[i] = 0;
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	char	*ret;
	int		*used;
	int		len;

	if (argc != 2)
		return (0);
	len = 0;
	while (argv[1][len])
		len++;
	s = malloc(len + 1);
	ret = malloc(len + 1);
	used = calloc(len, sizeof(int));
	if (!s || !ret || !used)
	{
		free(s);
		free(ret);
		free(used);
		return (1);
	}
	for (int i = 0; i < len; i++)
		s[i] = argv[1][i];
	s[len] = '\0';
	sort(s, len);
	perm(s, ret, used, 0, len);
	free(s);
	free(ret);
	free(used);
	return (0);
}
