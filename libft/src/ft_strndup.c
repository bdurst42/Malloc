/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 07:36:45 by lguarda           #+#    #+#             */
/*   Updated: 2014/12/28 07:36:48 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int i)
{
	char *str;

	str = malloc(sizeof(*str) * (i + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s1, i);
	return (str);
}
