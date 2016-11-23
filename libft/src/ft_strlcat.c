/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:13:40 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/07 12:11:56 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	size;
	size_t	i;
	size_t	z;

	size = n;
	i = 0;
	z = 0;
	while (dst[i] && n--)
		i++;
	n = size - i;
	dst += i;
	if (!n)
		return (i + ft_strlen(src));
	while (src[z])
	{
		if (n != 1)
		{
			*dst = src[z];
			dst++;
			n--;
		}
		z++;
	}
	*dst = '\0';
	return (i + z);
}
