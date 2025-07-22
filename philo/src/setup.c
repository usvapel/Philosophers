/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:59:34 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/22 02:13:29 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_philos(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	i = 0;
	while (i < table->number_of_philos)
	{
		if (i + 1 == table->number_of_philos)
			table->philos[i].right_fork = 0;
		else
			table->philos[i].right_fork = i + 1;
		pthread_mutex_init(&table->philos[i].left_fork, NULL);
		pthread_create(&table->philos[i].thread, NULL, routine, (void *)&table->philos[i]);
		i++;
	}
}
