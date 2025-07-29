/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:17:04 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/29 22:41:04 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int single_philo(t_philo *philo)
{
	ft_usleep(philo->time_to_die, philo->table);
	pthread_mutex_lock(&philo->table->dead_lock);
	philo->death_time = get_time(philo->table);
	philo->has_died = true;
	pthread_mutex_unlock(&philo->table->dead_lock);
	pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (0);
}

int	eating(t_philo *philo)
{
	const int	time = get_time(philo->table);

	pthread_mutex_lock(&philo->table->philos[philo->index].left_fork);
	if (!philo_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
		return (0);
	}
	print_handler(FORK, philo);
	if (philo->table->number_of_philos == 1)
		return (single_philo(philo));
	pthread_mutex_lock(&philo->table->philos[philo->right_fork].left_fork);
	if (!philo_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->philos[philo->right_fork].left_fork);
		pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
		return (0);
	}
	print_handler(FORK, philo);
	if (!philo_died(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(&philo->table->philos[philo->right_fork].left_fork);
		pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
		return (0);
	}
	print_handler(EATING, philo);
	ft_usleep(philo->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->philos[philo->index].left_fork);
	pthread_mutex_unlock(&philo->table->philos[philo->right_fork].left_fork);
	pthread_mutex_lock(&philo->table->dead_lock);
	check_time(philo, time);
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (handle_meals(philo));
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%d %d is sleeping\n", get_time(philo->table),
		philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%d %d is thinking\n", get_time(philo->table),
		philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	usleep(1000);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->table->wait_status == true)
	{
		if (philo->table->error_status == true)
			return (NULL);
	}
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
