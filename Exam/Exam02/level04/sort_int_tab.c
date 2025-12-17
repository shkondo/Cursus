/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:00:47 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/09 14:32:48 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	swap_elements(int *tab, unsigned int p1, unsigned int p2)
{
	int	tmp;

	tmp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = tmp;
}

void	bubble_sort(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				swap_elements(tab, j, j + 1);
			j++;
		}
		i++;
	}
}

void	sort_int_tab(int *tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}

int	main(void)
{
	int				tab[] = {4, 2, 42, -1, 24, 2147483647, -2147483648};
	unsigned int	size;
	unsigned int	i;

	size = 7;
	sort_int_tab(tab, size);
	i = 0;
	while (i < size)
	{
		printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
	return (0);
}
