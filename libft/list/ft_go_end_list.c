/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_end_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 16:02:02 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:15:29 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_go_end_list(t_list *node)
{
	if (node)
	{
		while (node->next)
			node = node->next;
		return (node);
	}
	return (NULL);
}
