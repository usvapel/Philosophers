/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:56:48 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 12:30:31 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*g_help_text = BOLD_WHITE
	"┌─────────────────────────────────────────────────────────────────┐\n"
	"│                           Philosophers                          │\n"
	"├─────────────────────────────────────────────────────────────────┤\n"
	"│ Usage: ./philo <philos> <die> <eat> <sleep> [times_to_eat]      │\n"
	"│                                                                 │\n"
	"│ Arguments:       (accepts positive integers)                    │\n"
	"│   philosophers - Number of philosophers                         │\n"
	"│   die          - Time (ms) before death without eating          │\n"
	"│   eat          - Time (ms) to eat                               │\n"
	"│   sleep        - Time (ms) to sleep                             │\n"
	"│   times_to_eat - [Optional] Times each philosopher must eat     │\n"
	"│                                                                 │\n"
	"│ Example: ./philo 5 800 200 200 3                                │\n"
	"└─────────────────────────────────────────────────────────────────┘\n"
	RESET;

void	print_help(void)
{
	printf("%s", g_help_text);
}

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time(table);
	while ((get_time(table) - start) < milliseconds)
	{
		usleep(500);
		pthread_mutex_lock(&table->dead_lock);
		if (table->death == true)
		{
			pthread_mutex_unlock(&table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&table->dead_lock);
		if (!philo_died(table))
			break ;
	}
	return (0);
}

int	get_time(t_table *table)
{
	t_time		now;
	long long	us;
	long		ms;

	gettimeofday(&now, NULL);
	us = ((long long)now.tv_sec * 1000000 + now.tv_usec)
		- ((long long)table->start.tv_sec * 1000000 + table->start.tv_usec);
	ms = us / 1000;
	return ((int)ms);
}

static void	reset_time(t_philo *philo)
{
	t_time	now;

	while (1)
	{
		pthread_mutex_lock(&philo->table->write_lock);
		gettimeofday(&now, NULL);
		if (now.tv_sec > philo->table->start.tv_sec
			|| (now.tv_sec == philo->table->start.tv_sec
				&& now.tv_usec >= philo->table->start.tv_usec))
		{
			pthread_mutex_unlock(&philo->table->write_lock);
			break ;
		}
		usleep(100);
		pthread_mutex_unlock(&philo->table->write_lock);
	}
}

int	wait_for_start(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->write_lock);
		if (philo->table->wait_status == false)
		{
			pthread_mutex_unlock(&philo->table->write_lock);
			break ;
		}
		if (philo->table->error_status == true)
		{
			pthread_mutex_unlock(&philo->table->write_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->write_lock);
		usleep(10);
	}
	reset_time(philo);
	return (1);
}
