/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:20:06 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/20 21:29:13 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	nb;
	int	i;
	int	first;

	if (ac == 2)
	{
		nb = atoi(av[1]);
		i = 2;
		first = 1;
		if (nb == 1)
		{
			printf("1\n");
			return (0);
		}
		while (i * i <= nb)
		{
			while (nb % i == 0)
			{
				if (first == 0)
					printf("*");
				printf("%d", i);
				nb = nb / i;
				first = 0;
			}
			i++;
		}
		if (nb > 1)
		{
			if (first == 0)
				printf("*");
			printf("%d", nb);
		}
		printf("\n");
	}
	else
		printf("\n");
	return (0);
}
