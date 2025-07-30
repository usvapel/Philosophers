/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:59:30 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/31 00:36:52 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(t_philo *philo)
{
	if (!print_handler(THINK, philo))
		return (0);
	if (!print_handler(FORK, philo))
		return (0);
	ft_usleep(philo->time_to_die, philo->table);
	pthread_mutex_lock(&philo->table->dead_lock);
	philo->death_time = get_time(philo->table);
	philo->has_died = true;
	philo->table->death = true;
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (NULL);
}

int	print_handler(char *type, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!philo_died(philo->table)
		&& get_time(philo->table) >= philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return (0);
	}
	printf(type, get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
	return (1);
}

int	philo_died(t_table *table)
{
	pthread_mutex_lock(&table->dead_lock);
	if (table->death == true)
	{
		pthread_mutex_unlock(&table->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&table->dead_lock);
	return (1);
}

int	handle_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->times_to_eat_validity == true)
	{
		philo->times_to_eat--;
		if (philo->times_to_eat == 0)
		{
			pthread_mutex_unlock(&philo->table->meal_lock);
			return (0);
		}
	}
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (1);
}

int	unlock_mutexes(t_philo *philo)
{
	if (philo->mutex_tracker >= 1)
	{
		if (philo->index < philo->right_fork)
			pthread_mutex_unlock(&philo->table->philos[philo->index].fork);
		else
			pthread_mutex_unlock(&philo->table->philos[philo->right_fork].fork);
	}
	if (philo->mutex_tracker == 2)
	{
		if (philo->index < philo->right_fork)
			pthread_mutex_unlock(&philo->table->philos[philo->right_fork].fork);
		else
			pthread_mutex_unlock(&philo->table->philos[philo->index].fork);
	}
	return (0);
}
