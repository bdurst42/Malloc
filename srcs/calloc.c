/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 00:58:47 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 01:38:33 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(unsigned long number, unsigned long size)
{
	char	*new;
	size_t	i;
	t_block	*block;

	i = 0;
	malloc_debug(HEADER, "-- CALLOC --", "");
	pthread_mutex_lock(&g_thread_safe.mutex_calloc);
	if (!number || !size)
	{
		malloc_debug(ERROR, "Calloc failed : ", "number or size are null");
		return (unlock_fct_with_return(NULL, &g_thread_safe.mutex_calloc));
	}
	new = malloc(number * size);
	if (new)
	{
		block = (t_block*)(new - BLOCK_SIZE);
		malloc_debug(SUCCES, "Calloc : ", "Fill allocation");
		while (i < block->size)
			new[i++] = 0;
		malloc_debug(SUCCES, "Calloc : ", "Succes !");
	}
	return (unlock_fct_with_return(new, &g_thread_safe.mutex_calloc));
}
