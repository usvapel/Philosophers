/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:54:16 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/30 12:15:32 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac == 5 || ac == 6)
	{
		table = ft_calloc(1, sizeof(t_table));
		if (!table)
			return (1);
		table->ac = ac;
		table->av = av;
		if (!parse_input(table))
		{
			free(table->philos);
			free(table);
			printf("Error: all arguments must be positive integers.\n");
			return (1);
		}
		setup_philos(table);
		return (monitor(table));
	}
	else
		print_help();
	return (0);
}
