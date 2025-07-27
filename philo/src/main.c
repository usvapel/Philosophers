/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:54:16 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/27 20:05:30 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_simulation(t_table *table)
{
	int i;

	i = 0;
	while (i < table->number_of_philos)
		pthread_join(table->philos[i++].thread, NULL);
	i = 0;
	while (i < table->number_of_philos)
		pthread_mutex_destroy(&table->philos[i++].left_fork);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->dead_lock);
	free(table->philos);
	exit(0);
}

static void monitor(t_table *table)
{
	int i;

	while (true)
	{
		i = 0;
		while (i < table->number_of_philos)
		{
			if (table->philos[i].has_died == true)
			{
				printf(RESET"%-5d %d "WHITE"died\n"RESET, get_time(table), table->philos[i].number);
				exit_simulation(table);
			}
			i++;
		}
		ft_usleep(1000, table);
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		table.ac = ac;
		table.av = av;
		if (!parse_input(&table))
			return (1);
		setup_philos(&table);
		monitor(&table);
	}
	else
		print_help();
	return (0);
}
