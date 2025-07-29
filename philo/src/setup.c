/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:59:34 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/27 19:56:33 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_failure(t_table *table, int i)
{
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
	while (i)
	{
		pthread_join(table->philos[--i].thread, NULL);
		pthread_mutex_destroy(&table->philos[i].left_fork);
	}
	exit_error(table, "Error: pthread_create");
}

static void	create_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->write_lock, NULL))
		exit_error(table, "Error: pthread_mutex_init");
	if (pthread_mutex_init(&table->dead_lock, NULL))
	{
		pthread_mutex_destroy(&table->write_lock);
		exit_error(table, "Error: pthread_mutex_init");
	}
	if (pthread_mutex_init(&table->meal_lock, NULL))
	{
		pthread_mutex_destroy(&table->write_lock);
		pthread_mutex_destroy(&table->dead_lock);
		exit_error(table, "Error: pthread_mutex_init");
	}
	i = 0;
	while (i < table->number_of_philos)
		if (pthread_mutex_init(&table->philos[i++].left_fork, NULL))
			break ;
	if (i == table->number_of_philos)
		return ;
	while (i)
		pthread_mutex_destroy(&table->philos[--i].left_fork);
	exit_error(table, "Error: pthread_mutex_init");
}

void	setup_philos(t_table *table)
{
	int	i;

	create_mutexes(table);
	gettimeofday(&table->start, NULL);
	i = 0;
	while (i < table->number_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, routine,
				(void *)&table->philos[i]))
		{
			table->error_status = true;
			break ;
		}
		i++;
	}
	table->wait_status = false;
	if (table->error_status == false)
		return ;
	handle_failure(table, i);
}
