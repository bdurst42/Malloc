/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 22:01:02 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:17:59 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memcpybis(void *dest, const void *src, size_t n)
{
	char		*dest2;
	const char	*src2;

	dest2 = dest;
	src2 = src;
	while (n--)
		*dest2++ = *src2++;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*tmp;

	tmp = malloc(n);
	ft_memcpybis(tmp, src, n);
	ft_memcpybis(dest, tmp, n);
	free (tmp);
	return (dest);
}
