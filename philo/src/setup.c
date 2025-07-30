/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:59:34 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 22:48:16 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_failure(t_table *table, int i)
{
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
	while (i)
	{
		pthread_join(table->philos[--i].thread, NULL);
		pthread_mutex_destroy(&table->philos[i].fork);
	}
	printf("Failure in thread creation");
	return (0);
}

static int	create_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->write_lock, NULL))
		return (0);
	if (pthread_mutex_init(&table->dead_lock, NULL))
	{
		pthread_mutex_destroy(&table->write_lock);
		return (0);
	}
	if (pthread_mutex_init(&table->meal_lock, NULL))
	{
		pthread_mutex_destroy(&table->write_lock);
		pthread_mutex_destroy(&table->dead_lock);
		return (0);
	}
	i = 0;
	while (i < table->number_of_philos)
		if (pthread_mutex_init(&table->philos[i++].fork, NULL))
			break ;
	if (i == table->number_of_philos)
		return (1);
	while (i)
		pthread_mutex_destroy(&table->philos[--i].fork);
	return (0);
}

static int	launch_threads(t_table *table, int i)
{
	if (pthread_create(&table->philos[i].thread, NULL, routine,
			(void *)&table->philos[i]))
	{
		pthread_mutex_lock(&table->write_lock);
		table->error_status = true;
		pthread_mutex_unlock(&table->write_lock);
		return (0);
	}
	return (1);
}

int	setup_philos(t_table *table)
{
	int	i;

	if (!create_mutexes(table))
		return (0);
	gettimeofday(&table->start, NULL);
	i = -1;
	while (++i < table->number_of_philos)
	{
		if (!launch_threads(table, i))
			break ;
	}
	pthread_mutex_lock(&table->write_lock);
	table->wait_status = false;
	if (table->error_status == false)
	{
		pthread_mutex_unlock(&table->write_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->write_lock);
	return (handle_failure(table, i));
}
