/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:10:37 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/02 21:03:49 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	char	used[256] = {0};
	int		i;

	if (ac == 3)
	{
		i = 0;
		while (av[1][i])
		{
			if (!used[(unsigned char)av[1][i]])
			{
				used[(unsigned char)av[1][i]] = 1;
				write(1, &av[1][i], 1);
			}
			i++;
		}
		while (av[2][i])
		{
			if (!used[(unsigned char)av[2][i]])
			{
				used[(unsigned char)av[2][i]] = 1;
				write(1, &av[2][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
