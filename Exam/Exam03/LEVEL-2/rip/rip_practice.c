#include <stdio.h>
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
		else if (s[i] == ')')
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
		if (s[i] == ')')
		{
			balance--;
			if (balance < 0)
				return (0);
		}
	}
	return (balance == 0);
}

void	rip(char *s, int to_replace, int replaced, int pos)
{
	char	c;

	if (to_replace == replaced)
	{
		if (is_valid(s))
			puts(s);
		return ;
	}
	for (int i = pos; s[i]; i++)
	{
		if (s[i] == ' ')
			continue ;
		if (s[i] == '(' || s[i] == ')')
		{
			c = s[i];
			s[i] = ' ';
			rip(s, to_replace, replaced + 1, i + 1);
			s[i] = c;
		}
	}
}

int	main(int argc, char **argv)
{
	size_t	len;
	int		count;
	char	*s;

	count = 0;
	len = 0;
	if (argc != 2 || !argv[1])
		return (1);
	for (size_t i = 0; argv[1][i]; i++)
		len++;
	s = malloc(len + 1);
	for (size_t i = 0; i < len; i++)
		s[i] = argv[1][i];
	s[len] = '\0';
	count = count_to_replace(s);
	rip(s, count, 0, 0);
	free(s);
	return (0);
}
