/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:17:50 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 18:18:04 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_ftoi_ext(const char **str)
{
	float	i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isdigit(**str))
	{
		i = (i * 10) + **str - '0';
		++j;
		if (j > 7)
			return (i);
		(*str) += 1;
	}
	return (i);
}

void			ft_ftoi_ext2(const char *str, float *i)
{
	float	j;
	int		z;

	z = 0;
	str += 1;
	if (!ft_isdigit(*str))
		return ;
	else if (*str == '0')
	{
		while (*str == '0')
		{
			str += 1;
			++z;
		}
	}
	j = ft_ftoi_ext(&str);
	while (j >= 10)
		j /= 10;
	while (z > 0)
	{
		j /= 10;
		z--;
	}
	*i += j / 10;
}

float			ft_ftoi(const char *str)
{
	float	i;
	int		m;

	m = 0;
	if (*str == '-')
	{
		m = 1;
		str += 1;
	}
	i = ft_ftoi_ext(&str);
	if (*str == '.')
		ft_ftoi_ext2(str, &i);
	if (m)
		return (-i);
	return (i);
}
