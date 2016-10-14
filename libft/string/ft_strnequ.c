/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 23:10:32 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:23:55 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	eq;

	if (s1 && s2)
	{
		eq = (ft_strncmp(s1, s2, n) == 0 ? 1 : 0);
		return (eq);
	}
	return (0);
}
