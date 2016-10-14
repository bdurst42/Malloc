/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:05:58 by bdurst            #+#    #+#             */
/*   Updated: 2015/01/10 12:50:18 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strchr(const char *s, int c)
{
	char		find;
	char		*fnd;
	int			ct;

	find = c;
	fnd = NULL;
	ct = 0;
	if (s)
	{
		while (s[ct] != '\0' && fnd == NULL)
		{
			if (s[ct] == find)
				fnd = (char *)(s + ct);
			ct++;
		}
		if (s[ct] == find && fnd == NULL)
			fnd = (char *)(s + ct);
	}
	return (fnd);
}
