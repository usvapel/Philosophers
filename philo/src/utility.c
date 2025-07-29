/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:56:48 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/15 20:56:53 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*g_help_text = BOLD_WHITE
	"┌─────────────────────────────────────────────────────────────────┐\n"
	"│                           Philosophers                          │\n"
	"├─────────────────────────────────────────────────────────────────┤\n"
	"│ Usage: ./philo <philos> <die> <eat> <sleep> [times_to_eat]      │\n"
	"│                                                                 │\n"
	"│ Arguments:       (accepts positive integers)                    │\n"
	"│   philosophers - Number of philosophers                         │\n"
	"│   die          - Time (ms) before death without eating          │\n"
	"│   eat          - Time (ms) to eat                               │\n"
	"│   sleep        - Time (ms) to sleep                             │\n"
	"│   times_to_eat - [Optional] Times each philosopher must eat     │\n"
	"│                                                                 │\n"
	"│ Example: ./philo 5 800 200 200 3                                │\n"
	"└─────────────────────────────────────────────────────────────────┘\n";

void	print_help(void)
{
	printf("%s", g_help_text);
}

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time(table);
	while ((get_time(table) - start) < milliseconds)
		usleep(500);
	return (0);
}

int	get_time(t_table *table)
{
	long long	us;
	long		ms;

	gettimeofday(&table->end, NULL);
	us = ((long long)table->end.tv_sec * 1000000 + table->end.tv_usec)
		- ((long long)table->start.tv_sec * 1000000 + table->start.tv_usec);
	ms = us / 1000;
	return ((int)ms);
}

void	exit_error(t_table *table, char *s)
{
	printf("%s\n", s);
	free(table->philos);
	free(table);
	exit(EXIT_FAILURE);
}
