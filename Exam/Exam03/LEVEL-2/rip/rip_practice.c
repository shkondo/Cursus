#include <stdio.h>
#include <stdlib.h>

int	count_to_replace(char *str)
{
	int	opened;
	int	closed;

	opened = 0;
	closed = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] == '(')
			opened++;
		if (str[i] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
	}
	return (opened + closed);
}

int	is_valid(char *str)
{
	int	balance;

	balance = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
		{
			balance--;
			if (balance < 0)
				return (1);
		}
	}
	return (balance);
}

void	rip(char *str, int to_replace, int replaced, int pos)
{
	char	c;

	if (to_replace == replaced)
	{
		if (is_valid(str) == 0)
			puts(str);
		return ;
	}
	for (int i = pos; str[i]; i++)
	{
		if (str[i] == '(' || str[i] == ')')
		{
			c = str[i];
			str[i] = ' ';
			rip(str, to_replace, replaced + 1, i + 1);
			str[i] = c;
		}
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	int		len;
	int		count;

	if (argc == 2 && argv[1])
	{
		len = 0;
		for (int i = 0; argv[1][i]; i++)
			len++;
		str = malloc(len + 1);
		if (!str)
			return (1);
		for (int i = 0; i < len; i++)
			str[i] = argv[1][i];
		str[len] = '\0';
		count = count_to_replace(str);
		rip(str, count, 0, 0);
	}
	return (0);
}
