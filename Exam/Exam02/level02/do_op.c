/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:26:32 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/03 02:35:48 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	num1;
	int	num2;

	if (ac == 4)
	{
		num1 = atoi(av[1]);
		num2 = atoi(av[3]);
		if (av[2][0] == '+')
			printf("%d", num1 + num2);
		else if (av[2][0] == '-')
			printf("%d", num1 - num2);
		else if (av[2][0] == '*')
			printf("%d", num1 * num2);
		else if (av[2][0] == '/')
			printf("%d", num1 / num2);
		else if (av[2][0] == '%')
			printf("%d", num1 - num2);
	}
  printf("\n");
  return 0;
}
