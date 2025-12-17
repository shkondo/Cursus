#include <stdlib.h>
#include <unistd.h>

void	ft_putnum(int n)
{
	int	c;

	c = n + '0';
	write(1, &c, 1);
}

void	solve(int *arr, int arg_len, int target, int idx, int *sub, int sub_len,
		int sum)
{
	if (idx == arg_len)
	{
		if (sum == target)
		{
			for (int i = 0; i < sub_len; i++)
			{
				if (i > 0)
					write(1, " ", 1);
				ft_putnum(sub[i]);
			}
			write(1, "\n", 1);
		}
		return ;
	}
	solve(arr, arg_len, target, idx + 1, sub, sub_len, sum);
	sub[sub_len] = arr[idx];
	solve(arr, arg_len, target, idx + 1, sub, sub_len + 1, sum + arr[idx]);
}

int	main(int argc, char **argv)
{
	int	target;
	int	arg_len;
	int	*arr;
	int	*sub;

	if (argc < 3)
		return (0);
	target = atoi(argv[1]);
	arg_len = argc - 2;
	arr = malloc(arg_len * sizeof(int));
	sub = malloc(arg_len * sizeof(int));
	if (!arr || !sub)
		return (1);
	for (int i = 0; i < arg_len; i++)
		arr[i] = atoi(argv[2 + i]);
	solve(arr, arg_len, target, 0, sub, 0, 0);
	free(arr);
	free(sub);
	return (0);
}
