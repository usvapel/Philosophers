/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:54:16 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/15 20:53:01 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		table.ac = ac;
		table.av = av;
		parse_input(&table);
		setup_philos(&table);
	}
	else
		print_help();
	return (0);
}
