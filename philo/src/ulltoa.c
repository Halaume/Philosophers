/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulltoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:58:39 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/19 11:03:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(unsigned long long nb)
{
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	if (nb < 10)
		ft_putchar(nb + '0');
}
