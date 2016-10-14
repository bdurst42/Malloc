/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_start_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 16:02:10 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:15:44 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_go_start_list(t_list *node)
{
	if (node)
	{
		while (node->prev)
			node = node->prev;
		return (node);
	}
	return (NULL);
}
