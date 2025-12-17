/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:06:55 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/20 17:31:16 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	check_digit(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb == -2147483648)
	{
		return (11);
	}
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	int		i;
	int		digit;
	char	*res;

	i = 0;
	digit = check_digit(nb);
	res = (char *)malloc((digit + 1) * sizeof(char));
	res[digit] = '\0';
	if (!res)
		return (NULL);
	if (nb == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		res[digit - 1 - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	return (res);
}

int	main(void)
{
	int	i;

	i = 42;
	printf("%s", ft_itoa(i));
	return (0);
}
