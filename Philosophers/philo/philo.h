/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:52:39 by shkondo           #+#    #+#             */
/*   Updated: 2026/03/11 10:00:00 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				sim_stop;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	t_philo			*philos;
}					t_table;

int		ft_atoi(const char *str);
long	get_time(void);
void	precise_sleep(long ms, t_table *table);
void	print_status(t_philo *philo, char *msg);
int		is_sim_stopped(t_table *table);
int		init_table(t_table *table, int argc, char **argv);
void	init_philos(t_table *table);
int		init_forks(t_table *table);
int		init_mutexes(t_table *table);
void	*philo_routine(void *arg);
void	philo_eat(t_philo *philo);
int		start_simulation(t_table *table);
void	monitor_philos(t_table *table);
void	cleanup_table(t_table *table);
int		parse_args(t_table *table, int argc, char **argv);

#endif
