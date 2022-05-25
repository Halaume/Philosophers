/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:11:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/25 12:49:12 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	ft_atoi(const char *nptr)
{
	int			i;
	long long	nbr;

	i = 0;
	nbr = 0;
	if (!nptr || !*nptr)
		return (-1);
	while (nptr[i] == '\f' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] && nptr[i] == '-')
		return (-1);
	else if (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((nbr * -1) <= -2147483648)
			return (-1);
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
		if (nptr[i] && (nptr[i] < '0' || nptr[i] > '9'))
			return (-1);
	}
	return (nbr);
}
