/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:35:45 by shkondo           #+#    #+#             */
/*   Updated: 2025/09/28 20:23:43 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node		*head;
	int			size;
}				t_stack;

typedef struct s_data
{
	t_stack	*a;
	t_stack	*b;
	int		total_size;
}			t_data;

void		sa(t_data *data, int print);
void		sb(t_data *data, int print);
void		ss(t_data *data, int print);
void		pa(t_data *data, int print);
void		pb(t_data *data, int print);
void		ra(t_data *data, int print);
void		rb(t_data *data, int print);
void		rr(t_data *data, int print);
void		rra(t_data *data, int print);
void		rrb(t_data *data, int print);
void		rrr(t_data *data, int print);
void		sort_three(t_data *data);
void		turk_sort(t_data *data);
void		compress_values(t_data *data);
void		final_rotate(t_data *data);
int			get_rotation_cost(int pos, int size);
int			find_target_pos(t_data *data, int value);
int			calculate_total_cost(int cost_a, int cost_b);
void		execute_double_rotation(t_data *data, int cost_a, int cost_b);
void		update_cache(t_data *data, int *min_val, int *min_pos);
int			find_target_cached(t_data *data, int value, int min_pos);
int			is_sorted(t_stack *stack);
int			find_min_index(t_stack *stack);
int			find_max_index(t_stack *stack);
void		free_data(t_data *data);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
t_stack		*stack_init(void);
t_data		*data_init(int capacity);
void		stack_free(t_stack *stack);
t_node		*create_node(int value);
void		push_front(t_stack *stack, int value);
int			get_at_index(t_stack *stack, int index);
t_data		*parse_args(int argc, char **argv);
int			validate_args(int argc, char **argv);
int			has_duplicates(int *array, int size);
int			check_int_overflow(const char *str);
char		*get_next_line(void);
int			execute_operation(t_data *data, char *line);

#endif
