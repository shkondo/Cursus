/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:32:42 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/09 14:31:54 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	char	digit;

	while (nb >= 10)
		ft_putnbr(nb / 10);
	digit = (nb % 10) + '0';
	write(1, &digit, 1);
}

int	main(int ac, char **av)
{
	(void)av;
	ft_putnbr(ac - 1);
	write(1, "\n", 1);
	return (0);
}
