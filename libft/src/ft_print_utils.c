/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:18:18 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 18:21:41 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_base_uint(int fd, unsigned int nbr, unsigned int base)
{
	unsigned int tmp;
	unsigned int l;

	tmp = nbr;
	l = 1;
	while (tmp >= base)
	{
		tmp /= base;
		l *= base;
	}
	while (l)
	{
		write(fd, &BASE[nbr / l], 1);
		nbr = nbr % l;
		l /= base;
	}
}

void		ft_putnbr_base_int(int fd, int nbr, int base)
{
	unsigned int	l;
	int				tmp;

	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	tmp = nbr;
	l = 1;
	while (tmp >= base)
	{
		tmp /= base;
		l *= base;
	}
	while (l)
	{
		write(fd, &BASE[nbr / l], 1);
		nbr = nbr % l;
		l /= base;
	}
}

static void	ft_print_float(int fd, float nbr)
{
	float	tmp;
	long	l;

	tmp = nbr;
	l = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		if (l > 1000000000)
			return ;
		l *= 10;
	}
	while (l)
	{
		ft_putchar_fd(((long)nbr / l) + '0', fd);
		nbr = nbr - (float)(((long)nbr / l) * (float)l);
		l /= 10;
	}
}

void		ft_putnbr_float(int fd, float nbr)
{
	if (nbr < 0)
	{
		nbr = -nbr;
		write(fd, "-", 1);
	}
	ft_print_float(fd, nbr);
	write(fd, ".", 1);
	nbr -= (int)nbr;
	nbr *= 1000000;
	ft_print_float(fd, nbr);
}
