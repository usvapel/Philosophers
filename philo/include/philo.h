/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:53:48 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/31 11:55:06 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "colors.h"

# define EATING "%d %d is eating\n"
# define FORK "%d %d has taken a fork\n"
# define SLEEP "%d %d is sleeping\n"
# define THINK "%d %d is thinking\n"
# define DEATH "%d %d died\n"

typedef pthread_t		t_pthread;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	t_mutex				fork;
	int					number;
	int					index;
	int					time;
	int					right_fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_to_eat;
	bool				times_to_eat_validity;
	bool				has_died;
	bool				has_eaten;
	int					death_time;
	int					last_meal;
	int					mutex_tracker;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philos;
	bool				death;
	volatile bool		error_status;
	volatile bool		wait_status;
	bool				start_sim;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					ac;
	char				**av;
	t_time				start;
	t_mutex				write_lock;
	t_mutex				dead_lock;
	t_mutex				meal_lock;
	t_philo				*philos;
}						t_table;

void					*routine(void *param);
int						monitor(t_table *table);
int						parse_input(t_table *table);
int						setup_philos(t_table *table);
void					*single_philo(t_philo *philo);
int						get_time(t_table *table);
void					check_time(t_philo *philo);
void					exit_error(t_table *table, char *s);
int						print_handler(char *type, t_philo *philo);
int						philo_died(t_table *table);
int						handle_meals(t_philo *philo);
int						unlock_mutexes(t_philo *philo);
int						wait_for_start(t_philo *philo);
int						atoi_safe(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);
int						ft_usleep(size_t milliseconds, t_table *table);

#endif // PHILO_H
