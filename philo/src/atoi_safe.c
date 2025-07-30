/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:44:49 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/29 20:34:54 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return (0);
		if (sign == -1 && result > (-(long)INT_MIN - digit) / 10)
			return (0);
		result = result * 10 + digit;
		nptr++;
	}
	if (*nptr)
		return (0);
	return ((int)result * sign);
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
