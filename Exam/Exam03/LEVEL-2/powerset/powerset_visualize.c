#include <stdio.h>
#include <stdlib.h>

void	print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("  ");
}

void	print_subset(int *sub, int len)
{
	printf("{");
	for (int i = 0; i < len; i++)
	{
		printf("%d", sub[i]);
		if (i < len - 1)
			printf(", ");
	}
	printf("}");
}

void	solve(int *arr, int n, int target, int idx, int *sub, int len, int sum)
{
	// Show current state
	print_indent(idx);
	printf("[Level %d] idx=%d, sum=%d, subset=", idx, idx, sum);
	print_subset(sub, len);
	printf("\n");
	// Base case: checked all elements
	if (idx == n)
	{
		print_indent(idx);
		if (sum == target)
		{
			printf("*** FOUND! sum=%d == target=%d => ", sum, target);
			for (int i = 0; i < len; i++)
			{
				printf("%d", sub[i]);
				if (i < len - 1)
					printf(" ");
			}
			printf("\n");
		}
		else
		{
			printf("X sum=%d != target=%d\n", sum, target);
		}
		return ;
	}
	// Choice 1: exclude current element
	print_indent(idx);
	printf("-> Exclude arr[%d]=%d\n", idx, arr[idx]);
	solve(arr, n, target, idx + 1, sub, len, sum);
	// Choice 2: include current element
	print_indent(idx);
	printf("-> Include arr[%d]=%d\n", idx, arr[idx]);
	sub[len] = arr[idx];
	solve(arr, n, target, idx + 1, sub, len + 1, sum + arr[idx]);
	// Show backtrack
	print_indent(idx);
	printf("[Return] from idx=%d\n", idx);
}

int	main(int ac, char **av)
{
	int	target;
	int	n;
	int	*arr;
	int	*sub;

	if (ac < 3)
		return (0);
	target = atoi(av[1]);
	n = ac - 2;
	arr = malloc(sizeof(int) * n);
	sub = malloc(sizeof(int) * n);
	// Show input
	printf("========================================\n");
	printf("Target: %d\n", target);
	printf("Array: [");
	for (int i = 0; i < n; i++)
	{
		arr[i] = atoi(av[i + 2]);
		printf("%d", arr[i]);
		if (i < n - 1)
			printf(", ");
	}
	printf("]\n");
	printf("========================================\n\n");
	solve(arr, n, target, 0, sub, 0, 0);
	printf("\n========================================\n");
	printf("Complete\n");
	free(arr);
	free(sub);
	return (0);
}
