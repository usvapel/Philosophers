/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:56:54 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 12:15:35 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_input_validity(t_table *table)
{
	if (table->number_of_philos <= 0
		|| table->philos[0].time_to_die <= 0
		|| table->philos[0].time_to_eat <= 0
		|| table->philos[0].time_to_sleep <= 0)
	{
		printf("Error: all arguments must be positive integers.\n");
		return (0);
	}
	if (table->ac == 6 && table->philos[0].times_to_eat <= 0)
	{
		printf("Error: all arguments must be positive integers.\n");
		return (0);
	}
	return (1);
}

static void	assign_values(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		table->philos[i].index = i;
		table->philos[i].number = i + 1;
		table->philos[i].table = table;
		table->philos[i].death_time = -1;
		table->philos[i].time_to_die = atoi_safe(table->av[2]);
		table->philos[i].time_to_eat = atoi_safe(table->av[3]);
		table->philos[i].time_to_sleep = atoi_safe(table->av[4]);
		table->philos[i].right_fork = (i + 1) % table->number_of_philos;
		if (table->ac == 6)
		{
			table->philos[i].times_to_eat_validity = true;
			table->philos[i].times_to_eat = atoi_safe(table->av[5]);
		}
		i++;
	}
}

int	parse_input(t_table *table)
{
	table->number_of_philos = atoi_safe(table->av[1]);
	if (table->number_of_philos <= 0)
	{
		printf("Error: all arguments must be positive integers.\n");
		return (0);
	}
	table->philos = ft_calloc(table->number_of_philos, sizeof(t_philo));
	if (!table->philos)
		return (0);
	assign_values(table);
	if (!check_input_validity(table))
		return (0);
	table->time_to_die = table->philos[0].time_to_die;
	table->time_to_eat = table->philos[0].time_to_eat;
	table->time_to_sleep = table->philos[0].time_to_sleep;
	return (1);
}
