/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:14:54 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/20 19:41:39 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

void	print_word(char *str, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	end;
	int	start;
	int	first_word;

	if (ac == 2)
	{
		i = ft_strlen(av[1]) - 1;
		first_word = 1;
		while (i >= 0)
		{
			while (i >= 0 && is_space(av[1][i]))
				i--;
			if (i >= 0)
			{
				end = i;
				while (i >= 0 && !is_space(av[1][i]))
					i--;
				start = i + 1;
				if (!first_word)
					write(1, " ", 1);
				print_word(av[1], start, end);
				first_word = 0;
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
