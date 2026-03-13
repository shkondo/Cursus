/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 10:00:00 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/11 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sim_stopped(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->stop_lock);
	stopped = table->sim_stop;
	pthread_mutex_unlock(&table->stop_lock);
	return (stopped);
}

static void	set_sim_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_lock);
	table->sim_stop = 1;
	pthread_mutex_unlock(&table->stop_lock);
}

static int	check_death(t_table *table)
{
	int		idx;
	long	time_since_meal;

	idx = 0;
	while (idx < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[idx].meal_lock);
		time_since_meal = get_time() - table->philos[idx].last_meal_time;
		pthread_mutex_unlock(&table->philos[idx].meal_lock);
		if (time_since_meal > table->time_to_die)
		{
			print_status(&table->philos[idx], MSG_DIED);
			set_sim_stop(table);
			return (1);
		}
		idx++;
	}
	return (0);
}

static int	check_all_ate(t_table *table)
{
	int	idx;
	int	finished;

	if (table->must_eat == -1)
		return (0);
	finished = 0;
	idx = 0;
	while (idx < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[idx].meal_lock);
		if (table->philos[idx].meal_count >= table->must_eat)
			finished++;
		pthread_mutex_unlock(&table->philos[idx].meal_lock);
		idx++;
	}
	if (finished == table->nb_philo)
	{
		set_sim_stop(table);
		return (1);
	}
	return (0);
}

void	monitor_philos(t_table *table)
{
	while (1)
	{
		if (check_death(table) || check_all_ate(table))
			break ;
		usleep(500);
	}
}
