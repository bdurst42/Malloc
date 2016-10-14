/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 16:03:01 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/16 21:09:12 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void		ft_node_push_back(t_list **begin_list, void *data)
{
	t_list	*new_node;
	t_list	*ptr;

	if (begin_list)
	{
		if (*begin_list)
		{
			ptr = *begin_list;
			new_node = ft_create_node(data);
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new_node;
			new_node->prev = ptr;
		}
		else
			*begin_list = ft_create_node(data);
	}
}
