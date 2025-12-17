/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:08:14 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/25 11:02:50 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_atoi(char *s)
{
	int	i;
	int	nb;

	i = 0;
  nb = 0;
	while (is_space(s[i]))
		i++;
	while (s[i])
  {
		nb = (nb * 10) + s[i] - '0';
    i++;
  }
	return (nb);
}

void	print_hex(int nb)
{
	char	arr_hex[] = "0123456789abcdef";
	char	c;

	if (nb >= 16)
  {
    nb /= 16;
		print_hex(nb);
  }
	c = arr_hex[nb % 16];
	write(STDOUT_FILENO, &c, 1);
}

int	main(int ac, char **av)
{
	unsigned int	nb;

	if (ac != 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	nb = ft_atoi(av[1]);
  printf("args:%d\n", nb); // atoiチェック
	print_hex(nb);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
