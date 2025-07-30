/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:45:05 by jpelline          #+#    #+#             */
/*   Updated: 2025/07/28 13:45:27 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;

	if (nmemb <= 0 || size <= 0)
		return (NULL);
	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	memset(tmp, 0, nmemb * size);
	return (tmp);
}
