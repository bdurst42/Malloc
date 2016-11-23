/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:19:15 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/04 15:31:19 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		z;

	i = 0;
	z = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] && i < n)
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
