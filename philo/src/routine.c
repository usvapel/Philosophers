/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 12:15:34 by jpelline         ###   ########.fr       */
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
	philo->time = get_time(philo->table);
	pthread_mutex_lock(&philo->table->philos[philo->index].fork);
	philo->mutex_tracker = 1;
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo));
	if (!print_handler(FORK, philo))
		return (unlock_mutexes(philo));
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].fork);
	philo->mutex_tracker = 2;
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo));
	if (!print_handler(FORK, philo))
		return (unlock_mutexes(philo));
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo));
	if (!print_handler(EATING, philo))
		return (unlock_mutexes(philo));
	ft_usleep(philo->time_to_eat, philo->table);
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo));
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].fork);
	pthread_mutex_unlock(&philo->table->philos[philo->index].fork);
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
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->time_to_sleep, philo->table);
	return (1);
}

static int	thinking(t_philo *philo)
{
	usleep(1000);
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
	if (philo->number % 2 == 0)
		ft_usleep(1, philo->table);
	while (1)
	{
		if (!philo_died(philo->table) || !thinking(philo))
			return (NULL);
		if (!philo_died(philo->table) || !eating(philo))
			return (NULL);
		if (!philo_died(philo->table) || !sleeping(philo))
			return (NULL);
	}
}
