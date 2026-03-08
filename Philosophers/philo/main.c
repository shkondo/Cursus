/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:46:26 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/01 21:41:28 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_init(int number_of_philosophers, (void *)philo_exec(philo),
		t_philo *philo)
{
	pthread_t	thread;
	int			ret;
	int			count;

	count = 0;
	philo->id = 0;
	ret = pthread_create(&thread, NULL, philosopher_routine, (void *)philo);
	while (count < number_of_philosophers)
	{
		philo->thread = 0;
		philo->id += 1;
		philo->fork = 0;
	}
}

void	philo_exec(t_philo *philo)
{
	return ;
}

void	print_timestamp(t_philo *philo)
{
	struct timeval	now;
	long			elapsed_ms;

	gettimeofday(&now, NULL);
	elapsed_ms = (now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec
			- start.tv_usec) / 1000;
	printf('%d %d has taken a fork', elapsed_ms, philo->id);
}

int	count_to_die(t_philo philo, int time_to_die)
{
	int			time;
	pthread_t	thread;

	thread = philo->thread;
	while (thread)
	{
		if (time > time_to_die)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		number_of_philosophers;

	if (argc != 5 || argc != 6)
		return (1);
	number_of_philosophers = ft_atoi(argv[1]);
	tmp = malloc(number_of_philosophers * sizeof(t_philo));
	if (!tmp)
	{
		free(tmp);
		return (1);
	}
	philo = tmp;
	philo_init(&philo);
	philo_exec(philo);
	philo_destruct(philo);
	return (0);
}
