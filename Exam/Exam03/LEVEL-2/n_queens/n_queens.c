#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_valid(int col, int row, int *pos)
{
	for (int i = 0; i < col; i++)
	{
		if (pos[i] == row)
			return (0);
		if (pos[i] - i == row - col)
			return (0);
		if (pos[i] + i == row + col)
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
				printf(" ");
			printf("%d", pos[i]);
		}
		printf("\n");
		return ;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_valid(pos, col, row))
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
