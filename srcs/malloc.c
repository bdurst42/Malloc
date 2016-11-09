/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 02:42:59 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 03:39:14 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_env			g_env;
t_thread_safe	g_thread_safe = {
	.mutex_malloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_calloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_realloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_free = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem_ex = PTHREAD_MUTEX_INITIALIZER,
};

t_block			*allocate_with_mmap(size_t size, char *name)
{
	void	*ret;
	t_block	*newb;

	if (size % getpagesize())
		size = (size / getpagesize() + 1) * getpagesize();
	ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	newb = (t_block*)ret;
	if (ret == (void*)-1)
		malloc_debug(ERROR, name, "MMAP failed");
	else
	{
		malloc_debug(SUCCES, name, "MMAP succes");
		newb->size = size - BLOCK_SIZE;
		newb->flag |= FLAG_FREE;
	}
	return (newb);
}

t_block			*allocate_first_block(size_t size)
{
	t_block	*newb;

	malloc_debug(SUCCES, "Malloc : ", "Allocate first pool");
	if ((newb = allocate_with_mmap(size, "Malloc : ")) == (void*)-1)
		return (NULL);
	return (newb);
}

static char		init(void)
{
	malloc_debug(SUCCES, "Malloc : ", "Init");
	if (!(g_env.tiny = allocate_first_block((MAX_TINY + BLOCK_SIZE) * PSZ)) ||
		!(g_env.small = allocate_first_block((MAX_SMALL + BLOCK_SIZE) * PSZ)))
		return (-1);
	g_env.large = NULL;
	return (0);
}

static t_block	*get_block(size_t size)
{
	t_block	*tmp;

	if (size <= MAX_TINY)
	{
		malloc_debug(SUCCES, "Malloc : ", "Get TINY");
		tmp = g_env.tiny;
	}
	else if (size <= MAX_SMALL)
	{
		malloc_debug(SUCCES, "Malloc : ", "Get SMALL");
		tmp = g_env.small;
	}
	else
	{
		malloc_debug(SUCCES, "Malloc : ", "Get LARGE");
		tmp = g_env.large;
	}
	while (tmp && tmp->next && (size > MAX_SMALL
			|| !IS_FREE(tmp) || tmp->size < size))
		tmp = tmp->next;
	return (tmp);
}

void			*malloc(size_t size)
{
	t_block	*b;

	malloc_debug(HEADER, "-- MALLOC --", "");
	pthread_mutex_lock(&g_thread_safe.mutex_malloc);
	size = ALIGN4(size);
	if (!g_env.tiny && init() == -1)
	{
		malloc_debug(ERROR, "Malloc : ", "Malloc failed : init error");
		return (NULL);
	}
	b = fill_block(get_block(size), size);
	pthread_mutex_unlock(&g_thread_safe.mutex_malloc);
	if (b)
	{
		malloc_debug(SUCCES, "Malloc : ", "Malloc succes !");
		return (b->data);
	}
	malloc_debug(ERROR, "Malloc : ", "Malloc failed : b null");
	return (b);
}
