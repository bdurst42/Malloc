/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 16:11:50 by bdurst            #+#    #+#             */
/*   Updated: 2015/01/31 16:11:51 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char		*ft_utoa(unsigned long long n, size_t nbase, char *base)
{
	char				*dst;
	unsigned long long	i;
	unsigned long long	k;

	k = n;
	i = ft_unbrlen(n, nbase);
	dst = malloc(sizeof(char) * (i + 1));
	dst[i] = '\0';
	while ((--i + 1) != 0)
	{
		dst[i] = base[k % nbase];
		k = k / nbase;
	}
	return (dst);
}
