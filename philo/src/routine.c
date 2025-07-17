/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/06/23 19:18:02 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->philos[philo->number].left_fork);
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].left_fork);
	printf("%ld %d is eating\n", get_time(philo->table), philo->number);
	ft_usleep(philo->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->philos[philo->number].left_fork);
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].left_fork);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	gettimeofday(&philo->table->start, NULL);
	while (1)
	{
		eat(philo);
		ft_usleep(1000, philo->table);
		// sleep(table);
		// think(table);
	}
	return (NULL);
}
