/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:22:23 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/04 15:31:56 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		z;

	i = 0;
	z = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i])
	{
		if (s1[i] == s2[z])
		{
			z++;
			if (s2[z] == '\0')
				return ((char *)&s1[i - z + 1]);
		}
		else
			z = 0;
		i++;
	}
	return (NULL);
}
