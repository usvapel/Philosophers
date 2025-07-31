/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:59:34 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/31 12:03:21 by jpelline         ###   ########.fr       */
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
		i--;
		pthread_join(table->philos[i].thread, NULL);
		pthread_mutex_destroy(&table->philos[i].fork);
	}
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
	int	err;

	err = pthread_create(&table->philos[i].thread, NULL, routine,
			(void *)&table->philos[i]);
	if (err)
	{
		pthread_mutex_lock(&table->write_lock);
		table->error_status = true;
		pthread_mutex_unlock(&table->write_lock);
		printf("Failed to create thread %d: error %d\n", i, err);
		return (0);
	}
	return (1);
}

int	setup_philos(t_table *table)
{
	int	i;

	if (!create_mutexes(table))
		return (0);
	i = 0;
	while (i < table->number_of_philos)
	{
		if (!launch_threads(table, i))
			break ;
		i++;
	}
	gettimeofday(&table->start, NULL);
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
