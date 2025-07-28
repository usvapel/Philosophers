/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:53:48 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/27 20:01:57 by jpelline         ###   ########.fr       */
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

# define WHITE "\001\x1b[38;5;231m\002"
# define GREEN "\001\x1b[38;5;82m\002"
# define RED "\001\x1b[38;5;196m\002"
# define BLUE "\001\x1b[38;5;75m\002"
# define YELLOW "\001\x1b[38;5;226m\002"
# define RESET "\001\x1b[0m\002"

# define EATING RESET "%-5d %d " GREEN "is eating\n" RESET
# define FORK RESET "%-5d %d " WHITE "has taken a fork\n" RESET
# define SLEEP RESET "%-5d %d " BLUE "is sleeping\n" RESET
# define THINK RESET "%-5d %d " YELLOW "is thinking\n" RESET
# define DEATH RESET "%-5d %d " WHITE "died\n" RESET

typedef pthread_t		t_pthread;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	t_mutex				left_fork;
	int					number;
	int					index;
	int					right_fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_to_eat;
	bool				times_to_eat_validity;
	bool				has_eaten;
	bool				has_slept;
	bool				is_thinking;
	bool				has_died;
	int					death_time;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philos;
	int					ac;
	char				**av;
	t_time				start;
	t_time				end;
	t_mutex				write_lock;
	t_mutex				dead_lock;
	t_mutex				meal_lock;
	t_philo				*philos;
}						t_table;

void					print_help(void);
int						parse_input(t_table *table);
void					setup_philos(t_table *table);
void					*routine(void *param);
int						atoi_safe(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);
int						get_time(t_table *table);
int						ft_usleep(size_t milliseconds, t_table *table);

void					monitor(t_table *table);

#endif // PHILO_H
