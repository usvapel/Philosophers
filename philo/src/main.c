/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:54:16 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/31 12:09:21 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*g_help_text = BOLD_WHITE
	"┌─────────────────────────────────────────────────────────────────┐\n"
	"│                           Philosophers                          │\n"
	"├─────────────────────────────────────────────────────────────────┤\n"
	"│ Usage: ./philo <philos> <die> <eat> <sleep> [times_to_eat]      │\n"
	"│                                                                 │\n"
	"│ Arguments:                                                      │\n"
	"│   philosophers - Number of philosophers                         │\n"
	"│   die          - Time (ms) before death without eating          │\n"
	"│   eat          - Time (ms) to eat                               │\n"
	"│   sleep        - Time (ms) to sleep                             │\n"
	"│   times_to_eat - [Optional] Times each philosopher must eat     │\n"
	"│                                                                 │\n"
	"│ Example: ./philo 5 800 200 200 3                                │\n"
	"└─────────────────────────────────────────────────────────────────┘\n"
	RESET;

static int	exit_program(t_table *table, int status)
{
	free(table->philos);
	free(table);
	return (status);
}

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
			return (exit_program(table, 1));
		if (!setup_philos(table))
			return (exit_program(table, 1));
		monitor(table);
		return (exit_program(table, 0));
	}
	else
		printf("%s", g_help_text);
	return (0);
}
