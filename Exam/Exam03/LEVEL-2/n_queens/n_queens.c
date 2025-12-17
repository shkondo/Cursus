#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_safe(int col, int row, int *pos)
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
	int	*res;

	if (argc == 2 && argv[1][0] != '-')
	{
		n = atoi(argv[1]);
		res = malloc(n * sizeof(int));
		if (!res)
			return (1);
		solve(n, 0, res);
		free(res);
	}
	return (0);
}
