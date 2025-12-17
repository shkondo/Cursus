/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:59:26 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/05 09:03:04 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	tmp;

	if (ac == 3)
	{
    a = atoi(av[1]);
    b = atoi(av[2]);
		if (a > b)
		{
			while (a > b)
			{
				tmp = a % b;
				if (tmp == 0)
				{
					printf("%d", b);
					break;
				}
				a = b;
				b = tmp;
			}
		}
		if (b > a)
		{
			while (b > a)
			{
				tmp = b % a;
				if (tmp == 0)
				{
					printf("%d", a);
					break;
				}
				b = a;
				a = tmp;
			}
		}
	}
	printf("\n");
	return (0);
}
