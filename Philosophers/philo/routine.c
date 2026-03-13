/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 10:00:00 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/11 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, MSG_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, MSG_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, MSG_FORK);
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, MSG_EAT);
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	*solo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, MSG_FORK);
	precise_sleep(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	philo_think(t_philo *philo)
{
	long	think_time;

	print_status(philo, MSG_THINK);
	if (philo->table->nb_philo % 2 == 0)
		return ;
	think_time = philo->table->time_to_eat * 2
		- philo->table->time_to_sleep;
	if (think_time > 0)
		precise_sleep(think_time, philo->table);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_philo == 1)
		return (solo_routine(philo));
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->time_to_eat / 2, philo->table);
	while (!is_sim_stopped(philo->table))
	{
		philo_eat(philo);
		if (is_sim_stopped(philo->table))
			break ;
		print_status(philo, MSG_SLEEP);
		precise_sleep(philo->table->time_to_sleep, philo->table);
		philo_think(philo);
	}
	return (NULL);
}
