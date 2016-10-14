/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:27:15 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:17:14 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dest2;
	const char	*src2;

	dest2 = dest;
	src2 = src;
	while (n--)
	{
		if (*src2 == c)
		{
			*dest2++ = *src2++;
			return (dest2);
		}
		*dest2++ = *src2++;
	}
	return (NULL);
}
