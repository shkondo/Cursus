/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:01:32 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/07 20:52:33 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>

int	ft_list_size(t_list *begin_list)
{
	int		count;
	t_list	*current;

  count = 0;
	current = begin_list;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}
