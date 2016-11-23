/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 02:20:59 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/23 04:33:13 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	write(1, str, i);
}

void	ft_puthexa(unsigned long n, size_t nbase, char *base)
{
	if (n > nbase - 1)
	{
		ft_puthexa(n / nbase, nbase, base);
		ft_puthexa(n % nbase, nbase, base);
	}
	else
		ft_putchar(base[n]);
}

void	ft_putnbr(long n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n >= 0)
		ft_putchar(n + '0');
	else if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
}

void	print_info_bytes(char *str, t_infos *infos, char activate)
{
	ft_putstr("\tnb of allocate bytes in ");
	ft_putstr(str);
	if (activate)
		ft_putnbr(infos->nb_pools);
	ft_putstr(": ");
	ft_putnbr(infos->tt_used_mem);
	ft_putchar('\n');
	ft_putstr("\tnb of unused bytes in ");
	ft_putstr(str);
	if (activate)
		ft_putnbr(infos->nb_pools);
	ft_putstr(": ");
	ft_putnbr(infos->tt_used_mem);
	ft_putchar('\n');
}
