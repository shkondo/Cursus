#include <stdlib.h>
#include <unistd.h>

void	ft_putnum(int n)
{
	char	c;

	c = n + '0';
	write(1, &c, 1);
}

int	is_valid(int *arr, int col, int row)
{
	for (int i = 0; i < col; i++)
	{
		if (arr[i] == row)
			return (0);
		else if (arr[i] - i == row - col)
			return (0);
		else if (arr[i] + i == row + col)
			return (0);
	}
	return (1);
}

void	solve(int n, int *arr, int col)
{
	if (col == n)
	{
		for (int i = 0; i < n; i++)
		{
			if (i > 0)
				write(1, " ", 1);
			ft_putnum(arr[i]);
		}
		write(1, "\n", 1);
		return ;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_valid(arr, col, row))
		{
			arr[col] = row;
			solve(n, arr, col + 1);
		}
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	*arr;

	if (argc != 2 || argv[1][0] == '-')
		return (0);
	n = atoi(argv[1]);
	arr = malloc(n * sizeof(int));
	if (!arr)
		return (1);
	solve(n, arr, 0);
	free(arr);
	return (0);
}
