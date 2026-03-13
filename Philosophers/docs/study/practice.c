/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:46:26 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/12 00:16:36 by shkondo          ###   ########.fr       */
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

void	philo_meal(t_philo *philo, t_data *data)
{
	pthread_mutex_t	mut;

	// fork に mutex を適用
	pthread_mutex_lock(&mut);
	// もしかして右のフォークと左のフォーク、あるいはフォークの番号も管理する必要あり？
	philo->fork += 1;
	while (data->time_to_eat)
	{
		// 何かの処理？
	}
	philo->fork -= 1;
	pthread_mutex_unlock(&mut);
	return ;
}

void	philo_think(t_philo *philo, t_data *data)
{
	// 他の哲学者の行動によって相対的に制御する？
	return ;
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	while (data->time_to_sleep)
	{
		// 処理
	}
	return ;
}

void	philo_exec(t_philo *philo)
{
	pthread_mutex_t	mut;

	// n - 1: 食事
	// n: 思考
	// n + 1: 睡眠
	// 思考、食事、思考をそれぞれ管理する関数に分ける
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

void	data_init(int number_of_philosophers, int time_to_die, int time_to_eat,
		int time_to_sleep, int number_of_times_of_each_philosopher_must_eat)
{
	return ;
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_philo	*tmp;

	if (argc != 5 || argc != 6)
		return (1);
	tmp = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (!tmp)
	{
		free(tmp);
		return (1);
	}
	philo = tmp;
	data_init(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		ft_atoi(argv[4]), ft_atoi(argv[5]));
	philo_init(ft_atoi(argv[1]), &philo);
	philo_exec(philo);
	philo_destruct(philo);
	return (0);
}
