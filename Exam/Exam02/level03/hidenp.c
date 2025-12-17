/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:58:20 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/26 12:00:26 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	hidenp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[j])
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
			j++;
		if (s1[i] == '\0')
			return (1);
		if (s2[j] == '\0')
			return (0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		if (hidenp(av[1], av[2]))
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
	write(1, "\n", 1);
	return (0);
}
