/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 16:19:32 by lguarda           #+#    #+#             */
/*   Updated: 2014/11/23 16:34:11 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char **str, char *ptr)
{
	char	*new;

	new = (char*)malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(ptr) + 1));
	if (new)
	{
		ft_strcpy(new, *str);
		ft_strcat(new, ptr);
		if (str)
			free(*str);
	}
	return (new);
}
