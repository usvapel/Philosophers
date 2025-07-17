/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:53:48 by jpelline          #+#    #+#             */
/*   Updated: 2025/06/16 20:54:07 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_t		t_pthread;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	t_mutex				left_fork;
	atomic_int			right_fork;
	atomic_int			time_to_die;
	atomic_int			time_to_eat;
	atomic_int			time_to_sleep;
	atomic_int			times_to_eat;
	bool				times_to_eat_validity;
	atomic_int			number;
	bool				has_eaten;
	bool				has_slept;
	bool				is_thinking;
	bool				has_died;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philos;
	int					ac;
	t_time				start;
	t_time				end;
	char				**av;
	t_philo				*philos;
}						t_table;

void					print_help(void);
void					parse_input(t_table *table);
void					setup_philos(t_table *table);
void					*routine(void *param);
int						atoi_safe(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);
size_t					get_current_time(void);
int						ft_usleep(size_t milliseconds);
#endif // PHILO_H
