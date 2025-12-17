/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:56:02 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/21 00:00:54 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	*ft_range(int start, int end)
{
	int	*range;
	int	i;
	int	size;
	int	current;

	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;
	range = (int *)malloc(size * sizeof(int));
	if (!range)
		return (NULL);
	i = 0;
	current = start;
	if (start == end)
	{
		range[0] = start;
		return (range);
	}
	while (current != end)
	{
		range[i] = current;
		if (start < end)
			current++;
		else
			current--;
		i++;
	}
	range[i] = end;
	return (range);
}

int	main(void)
{
	int	*range;
	int	i;
	int	start;
	int	end;
	int	size;

	// テストケース1: start < end
	start = 2;
	end = 8;
	size = end - start + 1;
	range = ft_range(start, end);
	printf("ft_range(%d, %d): ", start, end);
	i = 0;
	while (i < size)
	{
		printf("%d ", range[i]);
		i++;
	}
	printf("\n");
	free(range);
	// テストケース2: start > end
	start = 8;
	end = 2;
	size = start - end + 1;
	range = ft_range(start, end);
	printf("ft_range(%d, %d): ", start, end);
	i = 0;
	while (i < size)
	{
		printf("%d ", range[i]);
		i++;
	}
	printf("\n");
	free(range);
	// テストケース3: start == end
	start = 5;
	end = 5;
	size = 1;
	range = ft_range(start, end);
	printf("ft_range(%d, %d): ", start, end);
	i = 0;
	while (i < size)
	{
		printf("%d ", range[i]);
		i++;
	}
	printf("\n");
	free(range);
	return (0);
}
