/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:46:26 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/11 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_arg(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] < '0' || str[idx] > '9')
			return (0);
		idx++;
	}
	if (idx == 0)
		return (0);
	return (1);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	int	idx;

	if (argc != 5 && argc != 6)
		return (1);
	idx = 1;
	while (idx < argc)
	{
		if (!is_valid_arg(argv[idx]))
			return (1);
		if (ft_atoi(argv[idx]) <= 0)
			return (1);
		idx++;
	}
	(void)table;
	return (0);
}

int	start_simulation(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->nb_philo)
	{
		if (pthread_create(&table->philos[idx].thread, NULL,
				philo_routine, &table->philos[idx]) != 0)
			return (1);
		idx++;
	}
	monitor_philos(table);
	idx = 0;
	while (idx < table->nb_philo)
	{
		pthread_join(table->philos[idx].thread, NULL);
		idx++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_args(&table, argc, argv) != 0)
	{
		write(2, "Error: invalid arguments\n", 25);
		return (1);
	}
	if (init_table(&table, argc, argv) != 0)
	{
		write(2, "Error: initialization failed\n", 29);
		return (1);
	}
	start_simulation(&table);
	cleanup_table(&table);
	return (0);
}
