/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:00:00 by shkondo           #+#    #+#             */
/*   Updated: 2025/10/12 15:17:53 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	update_cache(t_data *data, int *min_val, int *min_pos)
{
	int	i;
	int	cur_val;

	*min_pos = 0;
	*min_val = get_at_index(data->a, 0);
	i = 1;
	while (i < data->a->size)
	{
		cur_val = get_at_index(data->a, i);
		if (cur_val < *min_val)
		{
			*min_val = cur_val;
			*min_pos = i;
		}
		i++;
	}
}

int	find_target_cached(t_data *data, int value, int min_pos)
{
	int	i;
	int	target;
	int	cur_val;

	target = -1;
	i = 0;
	while (i < data->a->size)
	{
		cur_val = get_at_index(data->a, i);
		if (cur_val > value)
		{
			if (target == -1 || cur_val < get_at_index(data->a, target))
				target = i;
		}
		i++;
	}
	if (target == -1)
		return (min_pos);
	return (target);
}
