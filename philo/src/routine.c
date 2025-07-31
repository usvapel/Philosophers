/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/31 12:41:50 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_forks(t_philo *philo)
{
	if (philo->index < philo->right_fork)
	{
		pthread_mutex_lock(&philo->table->philos[philo->index].fork);
		philo->mutex_tracker = 1;
		if (!print_handler(FORK, philo))
			return (unlock_mutexes(philo));
		pthread_mutex_lock(&philo->table->philos[philo->right_fork].fork);
		philo->mutex_tracker = 2;
		if (!print_handler(FORK, philo))
			return (unlock_mutexes(philo));
	}
	else
	{
		pthread_mutex_lock(&philo->table->philos[philo->right_fork].fork);
		philo->mutex_tracker = 1;
		if (!print_handler(FORK, philo))
			return (unlock_mutexes(philo));
		pthread_mutex_lock(&philo->table->philos[philo->index].fork);
		philo->mutex_tracker = 2;
		if (!print_handler(FORK, philo))
			return (unlock_mutexes(philo));
	}
	return (1);
}

static int	eating(t_philo *philo)
{
	philo->time = get_time(philo->table);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->has_eaten = false;
	pthread_mutex_unlock(&philo->table->meal_lock);
	if (!handle_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->table->dead_lock);
	philo->last_meal = get_time(philo->table);
	pthread_mutex_unlock(&philo->table->dead_lock);
	if (!print_handler(EATING, philo))
		return (unlock_mutexes(philo));
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->has_eaten = true;
	pthread_mutex_unlock(&philo->table->meal_lock);
	ft_usleep(philo->time_to_eat, philo->table);
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo));
	unlock_mutexes(philo);
	return (handle_meals(philo));
}

static int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!philo_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return (0);
	}
	printf(SLEEP, get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->time_to_sleep, philo->table);
	return (1);
}

static int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!philo_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return (0);
	}
	printf(THINK, get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	return (1);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (!wait_for_start(philo))
		return (NULL);
	if (philo->table->number_of_philos == 1)
		return (single_philo(philo));
	if (philo->number % 2 != 0)
		usleep(philo->time_to_eat * 500);
	while (1)
	{
		if (!thinking(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		usleep(1000);
	}
}
