/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:56:54 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/27 20:05:27 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_table *table)
{
	int	i;

	table->number_of_philos = atoi_safe(table->av[1]);
	table->philos = ft_calloc(table->number_of_philos, sizeof(t_philo));
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->number_of_philos)
	{
		table->philos[i].index = i;
		table->philos[i].number = i + 1;
		table->philos[i].table = table;
		table->philos[i].time_to_die = atoi_safe(table->av[2]);
		table->philos[i].time_to_eat = atoi_safe(table->av[3]);
		table->philos[i].time_to_sleep = atoi_safe(table->av[4]);
		table->philos[i].right_fork = (i + 1) % table->number_of_philos;
		if (i + 1 == table->number_of_philos)
			table->philos[i].right_fork = 0;
		else
			table->philos[i].right_fork = i + 1;
		if (table->ac == 6)
		{
			table->philos[i].times_to_eat_validity = true;
			table->philos[i].times_to_eat = atoi_safe(table->av[5]);
		}
		else
			table->philos[i].times_to_eat_validity = false;
		i++;
	}
	return (1);
}
