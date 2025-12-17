/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:35:07 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/25 10:29:44 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putnbr(int nb)
{
	char	c;

	if (nb == 0)
	{
		write(STDOUT_FILENO, "0", 1);
		return ;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(STDOUT_FILENO, &c, 1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			return (0);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + s[i] - '0';
		i++;
	}
	return (res);
}

int	is_prime(int nb)
{
	int	i;

	if (nb == 2 || nb == 3)
		return (1);
	if (nb % 2 == 0)
		return (0);
	i = 5;
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	nb;
	int	res;
	int	i;

	nb = 0;
	res = 0;
	i = 2;
	if (ac == 2)
	{
		nb = ft_atoi(av[1]);
		if (is_prime(nb))
		{
			while (i <= nb)
			{
				if (is_prime(i))
					res += i;
				i++;
			}
		}
	}
	ft_putnbr(res);
	write(STDOUT_FILENO, "\n", 1);
}
