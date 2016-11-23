/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 18:04:26 by lguarda           #+#    #+#             */
/*   Updated: 2015/02/19 02:23:20 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_fill_trim(char *dst, char *src)
{
	while (42)
	{
		while (*src && ft_iswhite(*src))
			src++;
		while (*src && !ft_iswhite(*src))
		{
			*dst = *src;
			src++;
			dst++;
		}
		if (*src == '\0')
		{
			*dst = '\0';
			break ;
		}
		*dst = ' ';
		dst++;
	}
	dst--;
	while (ft_iswhite(*dst))
	{
		*dst = '\0';
		dst--;
	}
}

char			*ft_trim(char *s)
{
	char	*new;
	int		i;

	new = s;
	i = 0;
	while (ft_iswhite(*new))
		new++;
	while (42)
	{
		while (*new && !ft_iswhite(*new))
		{
			new++;
			i++;
		}
		while (*new && ft_iswhite(*new))
			new++;
		i++;
		if (*new == '\0')
			break ;
	}
	new = (char*)malloc(sizeof(char) * i);
	ft_fill_trim(new, s);
	return (new);
}
