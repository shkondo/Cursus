/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 10:00:00 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/11 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
{
	int	idx;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (1);
	idx = 0;
	while (idx < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[idx], NULL) != 0)
			return (1);
		idx++;
	}
	return (0);
}

void	init_philos(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->nb_philo)
	{
		table->philos[idx].id = idx + 1;
		table->philos[idx].meal_count = 0;
		table->philos[idx].last_meal_time = table->start_time;
		table->philos[idx].left_fork = &table->forks[idx];
		table->philos[idx].right_fork
			= &table->forks[(idx + 1) % table->nb_philo];
		table->philos[idx].table = table;
		pthread_mutex_init(&table->philos[idx].meal_lock, NULL);
		idx++;
	}
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->must_eat = -1;
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	table->sim_stop = 0;
	table->start_time = get_time();
	if (init_forks(table) != 0)
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		return (1);
	init_philos(table);
	return (0);
}

void	cleanup_table(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[idx]);
		pthread_mutex_destroy(&table->philos[idx].meal_lock);
		idx++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->stop_lock);
	free(table->forks);
	free(table->philos);
}
