/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/27 19:53:06 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->dead_lock);
	i = 0;
	while (i < table->number_of_philos)
	{
		if (table->philos[i].has_died == true)
		{
			pthread_mutex_unlock(&table->dead_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&table->dead_lock);
	return (1);
}

static int single_philo(t_philo *philo)
{
	ft_usleep(philo->time_to_die, philo->table);
	pthread_mutex_lock(&philo->table->dead_lock);
	philo->has_died = true;
	philo->death_time = get_time(philo->table);
	pthread_mutex_unlock(&philo->table->dead_lock);
	pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (0);
}

int	eating(t_philo *philo)
{
	const int	time = get_time(philo->table);

	pthread_mutex_lock(&philo->table->meal_lock);
	pthread_mutex_lock(&philo->table->philos[philo->index].left_fork);
	printf(FORK, get_time(philo->table), philo->number);
	if (philo->table->number_of_philos == 1)
		return (single_philo(philo));
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].left_fork);
	printf(FORK, get_time(philo->table), philo->number);
	pthread_mutex_lock(&philo->table->write_lock);
	printf(EATING, get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].left_fork);
	pthread_mutex_lock(&philo->table->dead_lock);
	if (get_time(philo->table) - time >= philo->time_to_die)
	{
		philo->has_died = true;
		philo->death_time = get_time(philo->table);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (1);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf(SLEEP, get_time(philo->table),
		philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf(THINK, get_time(philo->table),
		philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (!philo_died(philo->table))
			return (NULL);
		thinking(philo);
		if (!philo_died(philo->table))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!philo_died(philo->table))
			return (NULL);
		sleeping(philo);
	}
}
