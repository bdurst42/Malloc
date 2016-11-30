/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 01:23:22 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/23 03:22:07 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static char	try_merge_with_next_block(t_block *block, size_t size)
{
	if (block->next && IS_FREE(block->next) && !IS_START_HEAP(block->next)
		&& block->size + BLOCK_SIZE + block->next->size >= size)
	{
		block->size += BLOCK_SIZE + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
		malloc_debug(SUCCES, "Realloc : ", "Merge succes");
		if (block->size >= size && block->size - size >= BLOCK_SIZE + 4)
			split_block(block, size, 1);
		return (1);
	}
	malloc_debug(ERROR, "Realloc : ", "Merge failed");
	return (0);
}

static void	copy_block(t_block *block, t_block *newblock)
{
	size_t	i;

	malloc_debug(SUCCES, "Realloc : ", "Copy");
	i = -1;
	while (++i < block->size && i < newblock->size)
		*(char*)((void*)newblock + BLOCK_SIZE + i) =
		*(char*)((void*)block + BLOCK_SIZE + i);
}

static void	*new_alloc(t_block *block, size_t size)
{
	void	*new_ptr;
	t_block	*newblock;

	newblock = NULL;
	malloc_debug(SUCCES, "Realloc : ", "New alloc");
	if (!(new_ptr = malloc(size)))
	{
		malloc_debug(ERROR, "Realloc : ", "Failed new alloc");
		return (NULL);
	}
	newblock = (t_block*)(new_ptr - BLOCK_SIZE);
	copy_block(block, newblock);
	free((void*)block + BLOCK_SIZE);
	return ((void*)newblock + BLOCK_SIZE);
}

static void	*find_good_way_to_realloc(t_block *block, size_t size, char merge,
										size_t align_size)
{
	if (size > MAX_SMALL && !IS_CANT_SPLIT(block)
		&& (size + BLOCK_SIZE) % getpagesize())
		align_size = ((size + BLOCK_SIZE) / getpagesize() + 1)
		* getpagesize() - BLOCK_SIZE;
	else
		align_size = size;
	if (block->size == align_size)
	{
		malloc_debug(SUCCES, "Realloc : ", "Same size when we align at 4");
		return ((void*)block + BLOCK_SIZE);
	}
	if ((size <= MAX_TINY && (block->size <= MAX_TINY || (IS_CANT_SPLIT(block)
		&& block->size <= MAX_SMALL))) || (size <= MAX_SMALL && size > MAX_TINY
		&& block->size > MAX_TINY && (block->size <= MAX_SMALL
		|| (IS_CANT_SPLIT(block) && block->size > MAX_SMALL))))
	{
		if (block->size >= size && block->size - size >= BLOCK_SIZE + 4)
			split_block(block, size, 1);
		else
			merge = try_merge_with_next_block(block, size);
	}
	else if (!merge)
		return (new_alloc(block, size));
	show_alloc_mem();
	return ((void*)block + BLOCK_SIZE);
}

void		*realloc(void *ptr, size_t size)
{
	t_block *b;
	char	merge;
	size_t	align_size;

	malloc_debug(HEADER, "-- REALLOC --", "");
	pthread_mutex_lock(&g_thread_safe.mutex_realloc);
	merge = 0;
	align_size = 0;
	if (!ptr)
	{
		malloc_debug(SUCCES, "Realloc : ", "Addr null");
		malloc_debug(SUCCES, "Realloc : ", "New alloc");
		return (unlock_fct_with_return(malloc(size),
				&g_thread_safe.mutex_realloc));
	}
	b = (t_block*)(ptr - BLOCK_SIZE);
	if (EXIST_BLOCK)
	{
		size = ALIGN4(size);
		return (unlock_fct_with_return(
		find_good_way_to_realloc(b, size, merge, align_size),
		&g_thread_safe.mutex_realloc));
	}
	malloc_debug(ERROR, "Realloc : ", "failed :(");
	return (unlock_fct_with_return(NULL, &g_thread_safe.mutex_realloc));
}
