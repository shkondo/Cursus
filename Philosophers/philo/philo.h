/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:52:39 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/01 20:10:20 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*fork;
}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_data;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				is_available;
}					t_fork;

typedef struct s_table
{
	t_fork			*forks;
	t_philo			*philos;
	t_data			data;
}					t_table;

void				*philo_thread(void *arg);
void				*monitor_thread(void *arg);
void				*fork_thread(void *arg);
void				*eat_thread(void *arg);
void				*sleep_thread(void *arg);
void				*think_thread(void *arg);
int					init_table(t_table *table, int argc, char **argv);
int					init_philos(t_table *table);
int					init_forks(t_table *table);
int					init_data(t_table *table, int argc, char **argv);
int					init_mutex(t_table *table);
int					init_threads(t_table *table);
int					init_monitor(t_table *table);
int					destroy_table(t_table *table);
int					destroy_philos(t_table *table);
int					destroy_forks(t_table *table);
int					destroy_data(t_table *table);
int					destroy_mutex(t_table *table);
int					destroy_threads(t_table *table);
int					destroy_monitor(t_table *table);
int					destroy_fork_threads(t_table *table);
int					destroy_eat_threads(t_table *table);
int					destroy_sleep_threads(t_table *table);
int					destroy_think_threads(t_table *table);
int					destroy_monitor_thread(t_table *table);

#endif
