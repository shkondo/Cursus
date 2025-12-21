#include <stdio.h>
#include <stdlib.h>

void	solve(int *arr, size_t arr_len, int target, int idx, int *sub,
		size_t sub_len, int sum)
{
	if (idx == arr_len)
	{
		if (sum == target)
		{
			for (size_t i = 0; i < sub_len; i++)
			{
				if (i > 0)
					printf(" ");
				printf("%d", sub[i]);
			}
			printf("\n");
		}
		return ;
	}
	solve(arr, arr_len, target, idx + 1, sub, sub_len, sum);
	sub[sub_len] = arr[idx];
	solve(arr, arr_len, target, idx + 1, sub, sub_len + 1, sum + arr[idx]);
}

int	main(int argc, char **argv)
{
	int		target;
	int		*arr;
	int		*sub;
	size_t	arr_len;

	if (argc < 3)
		return (1);
	target = atoi(argv[1]);
	arr_len = argc - 2;
	arr = malloc(arr_len * sizeof(int));
	sub = malloc(arr_len * sizeof(int));
	if (!arr || !sub)
	{
		free(arr);
		free(sub);
		return (1);
	}
	for (size_t i = 0; i < arr_len; i++)
		arr[i] = atoi(argv[i + 2]);
	solve(arr, arr_len, target, 0, sub, 0, 0);
	free(arr);
	free(sub);
	return (0);
}
