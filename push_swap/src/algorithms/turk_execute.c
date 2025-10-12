/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:00:00 by shkondo           #+#    #+#             */
/*   Updated: 2025/10/12 15:18:03 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	execute_rotation_a(t_data *data, int cost)
{
	while (cost > 0)
	{
		ra(data, 1);
		cost--;
	}
	while (cost < 0)
	{
		rra(data, 1);
		cost++;
	}
}

static void	execute_rotation_b(t_data *data, int cost)
{
	while (cost > 0)
	{
		rb(data, 1);
		cost--;
	}
	while (cost < 0)
	{
		rrb(data, 1);
		cost++;
	}
}

void	execute_double_rotation(t_data *data, int cost_a, int cost_b)
{
	while (cost_a > 0 && cost_b > 0)
	{
		rr(data, 1);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(data, 1);
		cost_a++;
		cost_b++;
	}
	execute_rotation_a(data, cost_a);
	execute_rotation_b(data, cost_b);
}

void	final_rotate(t_data *data)
{
	int	min_pos;
	int	cost;

	min_pos = find_min_index(data->a);
	cost = get_rotation_cost(min_pos, data->a->size);
	while (cost > 0)
	{
		ra(data, 1);
		cost--;
	}
	while (cost < 0)
	{
		rra(data, 1);
		cost++;
	}
}
