/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fill_block.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 03:28:11 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/23 01:15:56 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*allocate_large(t_block *newb, t_block *b, size_t size,
	char *name)
{
	malloc_debug(SUCCES, name, "Split LARGE block");
	if ((newb = (t_block*)allocate_with_mmap(size + BLOCK_SIZE, name))
		== (void*)-1)
		return (NULL);
	if (b)
	{
		newb->next = b->next;
		newb->prev = b;
		b->next = newb;
	}
	else
		g_env.large = newb;
	return (newb);
}

static t_block	*split_tiny_small(t_block *b, t_block *newb,
	size_t size, char src)
{
	newb = (void*)b + BLOCK_SIZE + size;
	newb->size = b->size - size - BLOCK_SIZE;
	newb->flag |= FLAG_FREE;
	if (src == 1 && b->next && IS_FREE(b->next) && !IS_START_HEAP(b->next))
	{
		newb->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
	}
	b->size = size;
	newb->next = b->next;
	b->next = newb;
	newb->prev = b;
	return (b);
}

t_block			*split_block(t_block *b, size_t size, char src)
{
	t_block *newb;
	char	*name;

	if (src == 0)
		name = "Malloc ; ";
	else
		name = "Realloc : ";
	newb = NULL;
	if (size > MAX_SMALL)
		return (allocate_large(newb, b, size, name));
	else if (size <= MAX_TINY ||
			(size > MAX_TINY && b->size - size > BLOCK_SIZE + MAX_TINY))
	{
		malloc_debug(SUCCES, name, "Split TINY or SMALL block");
		b = split_tiny_small(b, newb, size, src);
	}
	else
	{
		b->flag |= FLAG_CANT_SPLIT;
		malloc_debug(SUCCES, name, "No enough place to split");
	}
	return (b);
}

static void		allocate_new_pool(t_block *b, size_t size)
{
	if (size > MAX_TINY)
	{
		malloc_debug(SUCCES, "Malloc : ", "Allocate new pool of SMALL");
		b->next = allocate_first_block((MAX_SMALL + BLOCK_SIZE) * PSZ);
	}
	else
	{
		malloc_debug(SUCCES, "Malloc : ", "Allocate new pool of TINY");
		b->next = allocate_first_block((MAX_TINY + BLOCK_SIZE) * PSZ);
	}
}

t_block			*fill_block(t_block *b, size_t size)
{
	if (size <= MAX_SMALL && (!IS_FREE(b) || b->size < size))
	{
		allocate_new_pool(b, size);
		if (!b->next)
		{
			malloc_debug(ERROR, "Malloc : ", "Allocate new pool failed :(");
			return (NULL);
		}
		b->next->flag |= FLAG_START_HEAP;
		b->next->prev = b;
		b = b->next;
	}
	if (size > MAX_SMALL || b->size - size >= BLOCK_SIZE + 4)
		b = split_block(b, size, 0);
	else
		b->flag |= FLAG_CANT_SPLIT;
	if (b)
		b->flag ^= FLAG_FREE;
	return (b);
}
