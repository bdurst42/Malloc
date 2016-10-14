/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 16:12:33 by bdurst            #+#    #+#             */
/*   Updated: 2015/01/31 16:12:35 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include <limits.h>

char	*ft_itoa(long long n, int nbase, char *base)
{
	char		*dst;
	long long	i;
	long long	k;

	if (n == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	k = (n < 0) ? -n : n;
	i = ft_nbrlen(n, nbase);
	dst = malloc(sizeof(char) * (i + 1));
	if (n < 0)
	{
		*dst++ = '-';
		i--;
	}
	dst[i] = '\0';
	while (--i >= 0)
	{
		dst[i] = base[k % nbase];
		k = k / nbase;
	}
	if (n < 0)
		return (--dst);
	return (dst);
}
