/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:41:25 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:24:30 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	char		find;
	char		*fnd;
	int			ct;

	find = c;
	fnd = NULL;
	ct = 0;
	while (s[ct] != '\0')
	{
		if (s[ct] == find)
			fnd = (char *)(s + ct);
		ct++;
	}
	if (s[ct] == find)
		fnd = (char *)(s + ct);
	return (fnd);
}
