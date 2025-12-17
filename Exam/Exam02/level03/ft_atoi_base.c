/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:22:29 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/22 13:05:36 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	char_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	is_valid_char(char c, int base)
{
	int	digit;

	digit = char_to_digit(c);
	return (digit >= 0 && digit < base);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	res;
	int	sign;
	int	i;
	int	digit;

	if (str_base < 2 || str_base > 16)
		return (0);
	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
  // 基数チェック&進数変換
	while (str[i] && is_valid_char(str[i], str_base))
	{
		digit = char_to_digit(str[i]);
		res = res * str_base + digit;
		i++;
	}
	return (res * sign);
}

int	main(int ac, char **av)
{
	int	nb;

	if (ac == 3)
	{
		nb = ft_atoi_base(av[1], atoi(av[2]));
		printf("%d", nb);
	}
	else
	{
		printf("1010 -> %d\n", ft_atoi_base("1010", 2));
		printf("123 -> %d\n", ft_atoi_base("123", 8));
		printf("FF -> %d\n", ft_atoi_base("FF", 16));
		printf("12fdb3 -> %d\n", ft_atoi_base("12fdb3", 16));
		printf("-FF -> %d\n", ft_atoi_base("-FF", 16));
	}
}
