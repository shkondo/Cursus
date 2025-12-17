/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 01:39:17 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/03 01:49:03 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	is_uppercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	char	c;

	i = 0;
	if (ac == 2)
	{
		while (av[1][i])
		{
			if (is_lowercase(av[1][i]))
			{
				if (av[1][i] < 'n')
				{
					c = av[1][i] + 13;
					write(1, &c, 1);
				}
				else if (av[1][i] >= 'n')
				{
					c = av[1][i] - 13;
					write(1, &c, 1);
				}
			}
			else if (is_uppercase(av[1][i]))
			{
				if (av[1][i] < 'N')
				{
					c = av[1][i] + 13;
					write(1, &c, 1);
				}
				else if (av[1][i] >= 'N')
				{
					c = av[1][i] - 13;
					write(1, &c, 1);
				}
			}
			else
				write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
