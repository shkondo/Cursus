/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:56:46 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/26 12:00:30 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	len;
	int	*int_arr;
	int	i;

	if (start < end)
		len = end - start + 1;
	else
		len = start - end + 1;
	int_arr = (int *)malloc(len * sizeof(int));
	if (!int_arr)
		return (NULL);
	i = 0;
	if (start < end)
	{
		while (i < len)
		{
			int_arr[i] = end - i;
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			int_arr[i] = end + i;
			i++;
		}
	}
	return (int_arr);
}

int	main(void)
{
	int	*num_arr;
	int	i;
	int	len;

	i = 0;
	len = 4;
	num_arr = ft_rrange(0, -3);
	while (i < len)
	{
		printf("%d\n", num_arr[i]);
		i++;
	}
	free(num_arr);
	return (0);
}
