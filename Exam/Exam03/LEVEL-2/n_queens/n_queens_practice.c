#include <stdlib.h>
#include <unistd.h>

void	ft_putnum(int num)
{
	int	c;

	c = num + '0';
	write(1, &c, 1);
}

int	is_safe(int col, int row, int *pos)
{
	for (int i = 0; i < col; i++)
	{
		if (pos[i] == row)
			return (0);
		else if (pos[i] - i == row - col)
			return (0);
		else if (pos[i] + i == row + col)
			return (0);
	}
	return (1);
}

void	solve(int n, int col, int *pos)
{
	if (n == col)
	{
		for (int i = 0; i < n; i++)
		{
			if (i > 0)
				write(1, " ", 1);
			ft_putnum(pos[i]);
		}
		write(1, "\n", 1);
		return ;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_safe(col, row, pos))
		{
			pos[col] = row;
			solve(n, col + 1, pos);
		}
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	*pos;

	if (argc == 2 && argv[1][0] != '-')
	{
		n = atoi(argv[1]);
		pos = malloc(n * sizeof(int));
		if (!pos)
			return (1);
		solve(n, 0, pos);
		free(pos);
	}
	return (0);
}
