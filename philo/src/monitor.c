/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:42:43 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 11:53:05 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	exit_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
		pthread_join(table->philos[i++].thread, NULL);
	i = 0;
	while (i < table->number_of_philos)
		pthread_mutex_destroy(&table->philos[i++].fork);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
	free(table->philos);
	free(table);
	return (0);
}

static int	all_philos_have_eaten(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		if (table->philos[i].times_to_eat != 0
			|| table->number_of_philos == 1)
			return (1);
		i++;
	}
	return (0);
}

int	monitor(t_table *table)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < table->number_of_philos)
		{
			if (table->philos[i].has_died == true)
			{
				printf("%d %d died\n", table->philos[i].death_time,
					table->philos[i].number);
				return (exit_simulation(table));
			}
			if (table->ac == 6 && !all_philos_have_eaten(table))
				return (exit_simulation(table));
			i++;
		}
	}
}
