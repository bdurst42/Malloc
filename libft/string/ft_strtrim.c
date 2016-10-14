/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 01:29:06 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:25:11 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strtrim(char const *s)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	if (s)
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		j = ft_strlen(s) - 1;
		while (j > i && (s[j] == ' ' || s[j] == '\t' || s[j] == '\n'))
			j--;
		dst = ft_strsub(s, i, j - i + 1);
		return (dst);
	}
	return (NULL);
}
