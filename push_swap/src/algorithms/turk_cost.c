/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:30:00 by shkondo           #+#    #+#             */
/*   Updated: 2025/10/12 15:18:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_rotation_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (pos - size);
}

static void	find_target_helper(t_data *data, int value, int *target)
{
	int	i;
	int	cur_val;

	*target = -1;
	i = 0;
	while (i < data->a->size)
	{
		cur_val = get_at_index(data->a, i);
		if (cur_val > value)
		{
			if (*target == -1 || cur_val < get_at_index(data->a, *target))
				*target = i;
		}
		i++;
	}
}

int	find_target_pos(t_data *data, int value)
{
	int	target;
	int	min_pos;

	min_pos = find_min_index(data->a);
	find_target_helper(data, value, &target);
	if (target == -1)
		return (min_pos);
	return (target);
}

static int	get_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

int	calculate_total_cost(int cost_a, int cost_b)
{
	int	abs_a;
	int	abs_b;

	abs_a = get_abs(cost_a);
	abs_b = get_abs(cost_b);
	if ((cost_a > 0 && cost_b > 0) || (cost_a < 0 && cost_b < 0))
	{
		if (abs_a > abs_b)
			return (abs_a);
		return (abs_b);
	}
	return (abs_a + abs_b);
}
