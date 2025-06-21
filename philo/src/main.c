/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:54:16 by jpelline          #+#    #+#             */
/*   Updated: 2025/06/17 19:57:15 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_table *table)
{
	
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(ac, av, &table);
		setup_philos(&table);
		routine(&table);
	}
	else
		print_help();
	return (0);
}
