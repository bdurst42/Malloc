/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:34:15 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/05 16:46:55 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		z;

	i = 0;
	z = -1;
	while (s[i])
	{
		if (s[i] == c)
			z = i;
		i++;
	}
	if (s[i] == c)
		z = i;
	if (z != -1)
		return ((char *)&s[z]);
	return (NULL);
}
