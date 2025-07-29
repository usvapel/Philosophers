/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/29 23:08:31 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*single_philo(t_philo *philo)
{
	print_handler(THINK, philo);
	print_handler(FORK, philo);
	ft_usleep(philo->time_to_die, philo->table);
	philo->death_time = get_time(philo->table);
	philo->has_died = true;
	return (NULL);
}

int	eating(t_philo *philo)
{
	const int	time = get_time(philo->table);
	int			mutex_tracker;

	pthread_mutex_lock(&philo->table->philos[philo->index].fork);
	mutex_tracker = 1;
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo, mutex_tracker));
	print_handler(FORK, philo);
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].fork);
	mutex_tracker = 2;
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo, mutex_tracker));
	print_handler(FORK, philo);
	if (!philo_died(philo->table))
		return (unlock_mutexes(philo, mutex_tracker));
	print_handler(EATING, philo);
	ft_usleep(philo->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->philos[philo->index].fork);
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].fork);
	pthread_mutex_lock(&philo->table->dead_lock);
	check_time(philo, time);
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (handle_meals(philo));
}

void	sleeping(t_philo *philo)
{
	print_handler(SLEEP, philo);
	ft_usleep(philo->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	print_handler(THINK, philo);
	usleep(1000);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->table->wait_status == true)
		if (philo->table->error_status == true)
			return (NULL);
	if (philo->table->number_of_philos == 1)
		return (single_philo(philo));
	thinking(philo);
	if (philo->number % 2 != 0)
		if (!eating(philo))
			return (NULL);
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
