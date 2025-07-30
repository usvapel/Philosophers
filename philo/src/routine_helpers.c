/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:59:30 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 12:03:50 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (get_time(philo->table) - philo->last_meal > philo->time_to_die)
	{
		philo->death_time = get_time(philo->table);
		philo->has_died = true;
		philo->table->death = true;
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
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
	if (philo->mutex_tracker == 2)
		pthread_mutex_unlock(&philo->table->philos[philo->right_fork].fork);
	pthread_mutex_unlock(&philo->table->philos[philo->index].fork);
	return (0);
}
