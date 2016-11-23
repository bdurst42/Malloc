/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:59:31 by lguarda           #+#    #+#             */
/*   Updated: 2014/12/29 20:10:29 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		iswhite(int c)
{
	if ((c == '\n') || (c == '\v') ||
			(c == '\t') || (c == '\r') || (c == '\f') || (c == ' '))
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int		i;
	int		m;

	i = 0;
	m = 0;
	while (iswhite(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		m = 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		i = (i * 10) + *str - '0';
		str++;
	}
	if (m)
		return (-i);
	return (i);
}
