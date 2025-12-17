/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:37:21 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/23 16:37:34 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int ac, char **av)
{
	int	i;
	int	first_word;

	if (ac != 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	i = 0;
	first_word = 1;
	while (av[1][i] && is_space(av[1][i]))
		i++;
	while (av[1][i])
	{
		if (!is_space(av[1][i]))
		{
			if (first_word == 0)
				write(STDOUT_FILENO, " ", 1);
			first_word = 0;
			while (av[1][i] && !is_space(av[1][i]))
			{
				write(STDOUT_FILENO, &av[1][i], 1);
				i++;
			}
		}
		else
		{
			while (av[1][i] && is_space(av[1][i]))
				i++;
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
