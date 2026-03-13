/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 20:46:49 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/11 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	idx;
	int		sign;
	int		nb;

	idx = 0;
	sign = 1;
	while (is_space(str[idx]))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	nb = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		nb = nb * 10 + (str[idx] - '0');
		idx++;
	}
	return (nb * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	precise_sleep(long ms, t_table *table)
{
	long	target;

	target = get_time() + ms;
	while (get_time() < target)
	{
		if (is_sim_stopped(table))
			break ;
		usleep(200);
	}
}

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	if (!is_sim_stopped(philo->table))
	{
		timestamp = get_time() - philo->table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
