/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:59:30 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/29 20:59:37 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_handler(char *type, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf(type, get_time(philo->table), philo->number);
	pthread_mutex_unlock(&philo->table->write_lock);
}

int	philo_died(t_table *table)
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

void	check_time(t_philo *philo, const int time)
{
	if (get_time(philo->table) - time >= philo->time_to_die + 10)
	{
		philo->has_died = true;
		philo->death_time = get_time(philo->table);
	}
}

int	handle_meals(t_philo *philo)
{
	if (philo->times_to_eat_validity == true)
	{
		philo->times_to_eat--;
		if (philo->times_to_eat == 0)
			return (0);
	}
	return (1);
}
