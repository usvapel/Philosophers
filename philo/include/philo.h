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

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_t		s_pthread;
typedef s_pthread		t_pthread;
typedef pthread_mutex_t	s_mutex;
typedef s_mutex			t_mutex;

typedef struct s_philo
{
	t_pthread	thread;
	t_mutex 	lock;
	int			left_fork;
	int			right_fork;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_to_eat;
	bool		times_to_eat_validity;
}				t_philo;

typedef struct s_table
{
	int		number_of_philos;
	t_philo	*philos;
}			t_table;

void		print_help(void);
void		parse_input(int ac, char **av, t_table *table);
void		setup_philos(t_table *table);
int			atoi_safe(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);

#endif // PHILO_H
