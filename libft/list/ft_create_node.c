/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 16:01:21 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 17:15:22 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list		*ft_create_node(void *data)
{
	t_list	*new_node;

	if ((new_node = (t_list *)malloc(sizeof(t_list))))
	{
		new_node->data = data;
		new_node->prev = NULL;
		new_node->next = NULL;
		return (new_node);
	}
	return (NULL);
}
