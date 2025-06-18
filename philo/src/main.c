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

static void	print_help(void)
{
	const char	*help_text;

	help_text
		="┌─────────────────────────────────────────────────────────────────┐\n"
		"│                            Philosophers                         │\n"
		"├─────────────────────────────────────────────────────────────────┤\n"
		"│ Usage: ./philo <philosophers> <die> <eat> <sleep> [times_to_eat]│\n"
		"│                                                                 │\n"
		"│ Arguments:                                                      │\n"
		"│   philosophers - Number of philosophers (and forks)             │\n"
		"│   die          - Time (ms) before death without eating          │\n"
		"│   eat          - Time (ms) to eat                               │\n"
		"│   sleep        - Time (ms) to sleep                             │\n"
		"│   times_to_eat - [Optional] Times each philosopher must eat     │\n"
		"│                                                                 │\n"
		"│ Example: ./philo 5 800 200 200 3                                │\n"
		"└─────────────────────────────────────────────────────────────────┘\n";
	printf("%s", help_text);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 5 || ac == 6)
	{
		printf("test");
	}
	else
		print_help();
	return (0);
}
