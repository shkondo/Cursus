#include <stdio.h>
#include <stdlib.h>

void	solve(int *arr, int n, int target, int idx, int *sub, int len, int sum)
{
	if (idx == n)
	{
		if (sum == target)
		{
			for (int i = 0; i < len; i++)
			{
				printf("%d", sub[i]);
				if (i < len - 1)
					printf(" ");
			}
			printf("\n");
		}
		return ;
	}
	solve(arr, n, target, idx + 1, sub, len, sum);
	sub[len] = arr[idx];
	solve(arr, n, target, idx + 1, sub, len + 1, sum + arr[idx]);
}

int	main(int argc, char **argv)
{
	int	target;
	int	n;
	int	*arr;
	int	*sub;

	if (argc < 3)
		return (1);
	target = atoi(argv[1]);
	n = argc - 2;
	arr = malloc(sizeof(int) * n);
	sub = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		arr[i] = atoi(argv[i + 2]);
	solve(arr, n, target, 0, sub, 0, 0);
	free(arr);
	free(sub);
	return (0);
}
