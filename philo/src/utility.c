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

void	print_help(void)
{
	const char	*help_text;

	help_text
		="┌─────────────────────────────────────────────────────────────────┐\n"
		"│                            Philosophers                         │\n"
		"├─────────────────────────────────────────────────────────────────┤\n"
		"│ Usage: ./philo <philos> <die> <eat> <sleep> [times_to_eat]      │\n"
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

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time(table);
	while ((get_time(table) - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;

	if (nmemb == 0 || size == 0)
		return (NULL);
	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	memset(tmp, 0, nmemb * size);
	return (tmp);
}

static int	check_input(const char *nptr, int sign)
{
	long	result;
	int		digit;

	result = 0;
	digit = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		if (sign == 1 && result > (INT_MAX - digit) / 10)
			return (INT_MAX);
		if (sign == -1 && result > (-(long)INT_MIN - digit) / 10)
			return (INT_MIN);
		result = result * 10 + digit;
		nptr++;
	}
	return ((int)result);
}

int	atoi_safe(const char *nptr)
{
	int		sign;

	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\a' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	return (check_input(nptr, sign));
}
