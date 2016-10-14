/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:51:01 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:24:50 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s2[0])
		return ((char *)s1);
	while (s1[i])
	{
		while (s1[i] == s2[j])
		{
			i++;
			j++;
			if (!s2[j])
				return ((char *)&s1[i - j]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
