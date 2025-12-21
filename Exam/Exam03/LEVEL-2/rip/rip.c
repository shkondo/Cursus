#include <stdio.h>

int	count_to_replace(char *str)
{
	int	opened;
	int	closed;

	opened = 0;
	closed = 0;
	if (!str)
		return (1);
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] == '(')
			opened++;
		else if (str[i] == ')')
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
	if (!str)
		return (1);
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
	return (balance == 0);
}

void	rip(char *str, int to_replace, int replaced, size_t pos)
{
	char	c;

	if (!str)
		return ;
	if (to_replace == replaced)
	{
		if (is_valid(str) == 0)
			puts(str);
		return ;
	}
	for (size_t i = pos; str[i]; i++)
	{
		if (str[i] == ' ')
			continue ;
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
	int	count;

	if (argc != 2 || !argv[1])
		return (1);
	count = count_to_replace(argv[1]);
	rip(argv[1], count, 0, 0);
	return (0);
}
