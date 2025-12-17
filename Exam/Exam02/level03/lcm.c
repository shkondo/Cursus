/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:25:03 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/04 22:28:54 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

unsigned int	lcm(unsigned int x, unsigned int y, unsigned int hcf)
{
	unsigned int	res;

	res = (x / hcf) * y;
	return (res);
}

int	main(int ac, char **av)
{
	unsigned int	hcf = 0;
	unsigned int	original_a;
	unsigned int	original_b;
	unsigned int	a;
	unsigned int	b;
	unsigned int	tmp;

	if (ac == 3)
	{
		if (av[1] == 0 || av[2] == 0)
			return (0);
		original_a = atoi(av[1]);
		original_b = atoi(av[2]);
		a = original_a;
		b = original_b;
		if (a > b)
		{
			while (a > b)
			{
				tmp = a % b;
				if (tmp == 0)
				{
					hcf = b;
					break ;
				}
				a = b;
				b = tmp;
			}
      printf("hcf: %d\n", hcf);
			printf("lcm: %d", lcm(original_a, original_b, hcf));
		}
		else if (b > a)
		{
			while (b > a)
			{
				tmp = b % a;
				if (tmp == 0)
				{
					hcf = a;
					break ;
				}
				b = a;
				a = tmp;
			}
      printf("hcf: %d\n", hcf);
			printf("lcm: %d", lcm(original_b, original_a, hcf));
		}
		else
			printf("%d", a);
	}
	printf("\n");
}
