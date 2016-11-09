/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 01:35:10 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 01:38:06 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	malloc_debug(char *color, char *fct, char *str)
{
	if (getenv("MALLOC_DEBUG"))
	{
		ft_putstr("[DEBUG] -> ");
		ft_putstr(color);
		ft_putstr(fct);
		ft_putstr(END);
		ft_putstr(str);
		ft_putchar('\n');
	}
}
