/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 16:01:05 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/08 21:58:05 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_clear_list(t_list **list, void (*fct_free)(void *))
{
	t_list	*tmp;

	if (list)
	{
		ft_go_start_list(*list);
		tmp = *list;
		while (tmp)
		{
			if (fct_free)
				(*fct_free)((*list)->data);
			tmp = (*list)->next;
			free(*list);
			*list = tmp;
		}
		*list = NULL;
	}
}
