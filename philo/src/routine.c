/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/22 02:13:33 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
		if (table->philos[i++].has_died ==  true)
			return (0);
	return (1);
}

size_t	get_time(t_table *table)
{
	long long	us;
	long		ms;

	gettimeofday(&table->end, NULL);
	us = ((long long)table->end.tv_sec * 1000000 + table->end.tv_usec)
		- ((long long)table->start.tv_sec * 1000000 + table->start.tv_usec);
	ms = us / 1000;
	return (ms);
}

void	eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->philos[philo->index].left_fork);
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].left_fork);
    pthread_mutex_lock(&philo->table->write_lock);
    printf("%ld %d is eating\n", get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
    ft_usleep(philo->time_to_eat, philo->table);
    pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].left_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%ld %d is sleeping\n", get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%ld %d is thinking\n", get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	gettimeofday(&philo->table->start, NULL);
	while (1)
	{
		if (!philo_died(philo->table))
			exit(1);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}
