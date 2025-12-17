#include <stdio.h>

void	print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("  ");
}

void	print_state(char *str, int depth)
{
	print_indent(depth);
	printf("Current: \"");
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			printf("_");
		else
			printf("%c", str[i]);
	}
	printf("\"\n");
}

int	is_valid(char *str)
{
	int	opened;

	opened = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] == '(')
			opened++;
		else if (str[i] == ')')
		{
			opened--;
			if (opened < 0)
				return (1);
		}
	}
	return (opened);
}

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

void	rip(char *str, int to_fix, int fixed, int pos, int depth)
{
	char	c;

	print_indent(depth);
	printf("[Depth %d] Removed:%d/%d, pos=%d\n", depth, fixed, to_fix, pos);
	print_state(str, depth);
	if (to_fix == fixed)
	{
		if (is_valid(str) == 0)
		{
			print_indent(depth);
			printf(">>> VALID SOLUTION: ");
			puts(str);
		}
		else
		{
			print_indent(depth);
			printf("xxx Still invalid\n");
		}
		return ;
	}
	for (int i = pos; str[i]; i++)
	{
		if (str[i] == '(' || str[i] == ')')
		{
			c = str[i];
			print_indent(depth);
			printf("-> Remove '%c' at pos %d\n", c, i);
			str[i] = ' ';
			rip(str, to_fix, fixed + 1, i + 1, depth + 1);
			str[i] = c;
			print_indent(depth);
			printf("<- Restore '%c' at pos %d (backtrack)\n", c, i);
		}
	}
}

int	main(int argc, char **argv)
{
	int		count;
	int		i;
	char	str[1000];

	if (argc != 2 || !argv[1])
		return (1);
	i = 0;
	while (argv[1][i])
	{
		str[i] = argv[1][i];
		i++;
	}
	str[i] = '\0';
	printf("===========================\n");
	printf("Input: \"%s\"\n", str);
	count = count_to_replace(str);
	printf("Need to remove: %d brackets\n", count);
	printf("===========================\n\n");
	rip(str, count, 0, 0, 0);
	printf("\n===========================\n");
	printf("Search complete\n");
	return (0);
}
