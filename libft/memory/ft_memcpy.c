/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:59:29 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:17:49 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest2;
	const char	*src2;

	if (dest && src)
	{
		dest2 = dest;
		src2 = src;
		while (n--)
			*dest2++ = *src2++;
		return (dest);
	}
	return (NULL);
}
