/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 01:38:47 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_philo(t_philo *philo)
{
	if (!print_handler(THINK, philo))
		return (0);
	if (!print_handler(FORK, philo))
		return (0);
	ft_usleep(philo->time_to_die, philo->table);
	philo->death_time = get_time(philo->table);
	philo->has_died = true;
	philo->table->death = true;
	return (NULL);
}

static int	eating(t_philo *philo)
{
	int			mutex_tracker;

	pthread_mutex_lock(&philo->table->philos[philo->index].fork);
	mutex_tracker = 1;
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo, mutex_tracker));
	if (!print_handler(FORK, philo))
		return (unlock_mutexes(philo, mutex_tracker));
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].fork);
	mutex_tracker = 2;
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->time = get_time(philo->table);
	pthread_mutex_unlock(&philo->table->meal_lock); FIX THIS SHIT 3 100 60 60
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo, mutex_tracker));
	if (!print_handler(FORK, philo))
		return (unlock_mutexes(philo, mutex_tracker));
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo, mutex_tracker));
	if (!print_handler(EATING, philo))
		return (unlock_mutexes(philo, mutex_tracker));
	ft_usleep(philo->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->philos[philo->index].fork);
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].fork);
	check_time(philo);
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
	ft_usleep(philo->time_to_sleep, philo->table);
	pthread_mutex_unlock(&philo->table->write_lock);
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

static int	wait_for_start(t_philo *philo)
{
	while (philo->table->wait_status == true)
	{
		if (philo->table->error_status == true)
			return (0);
		usleep(10);
	}
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
	if (philo->index % 2 != 0)
        usleep(1000);
	while (1)
	{
		if (!philo_died(philo->table) || !thinking(philo))
			return (NULL);
		usleep(1000);
		if (!philo_died(philo->table) || !eating(philo))
			return (NULL);
		if (!philo_died(philo->table) || !sleeping(philo))
			return (NULL);
	}
}
