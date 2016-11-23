/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 00:58:47 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/23 03:52:46 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void		*calloc(unsigned long number, unsigned long size)
{
	void	*ptr;
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
	ptr = malloc(number * size);
	if (ptr)
	{
		block = (t_block*)((void*)ptr - BLOCK_SIZE);
		malloc_debug(SUCCES, "Calloc : ", "Fill allocation");
		ft_memset(ptr, 0, block->size);
		malloc_debug(SUCCES, "Calloc : ", "Succes !");
	}
	return (unlock_fct_with_return(ptr, &g_thread_safe.mutex_calloc));
}
