/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:58:18 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:17:35 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!n || !str1 || !str2)
		return (0);
	while ((*str1 == *str2) && n - 1 != 0)
	{
		n--;
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
