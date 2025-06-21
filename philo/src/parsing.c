/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:56:54 by jpelline          #+#    #+#             */
/*   Updated: 2025/06/18 21:57:28 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(int ac, char **av, t_table *table)
{
	int	i;

	table->number_of_philos = atoi_safe(av[1]);
	table->philos = ft_calloc(table->number_of_philos, sizeof(t_philo));
	i = 0;
	while (i < table->number_of_philos)
	{
		table->philos[i].time_to_die   = atoi_safe(av[2]);
		table->philos[i].time_to_eat   = atoi_safe(av[3]);
		table->philos[i].time_to_sleep = atoi_safe(av[4]);
		if (ac == 6)
		{
			table->philos[i].times_to_eat_validity = true;
			table->philos[i].times_to_eat  = atoi_safe(av[5]);
		}
		else
			table->philos[i].times_to_eat_validity = false;
		i++;
	}
}
