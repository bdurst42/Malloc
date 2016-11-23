/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 02:31:59 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/23 08:01:20 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*merge_bs(t_block *b)
{
	malloc_debug(SUCCES, "Free : ", "Merge bs");
	while (!IS_START_HEAP(b) && b->prev && IS_FREE(b->prev))
		b = b->prev;
	while (b->next && IS_FREE(b->next) && !IS_START_HEAP(b->next))
	{
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
	}
	if (b->next)
		b->next->prev = b;
	return (b);
}

static void		pop_b(t_block *b, size_t size)
{
	malloc_debug(SUCCES, "Free : ", "Pop b");
	if (b->prev)
		b->prev->next = b->next;
	if (b->next)
	{
		if ((size > MAX_SMALL && !IS_CANT_SPLIT(b)) && !b->prev)
			g_env.large = b->next;
		b->next->prev = b->prev;
	}
}

static char		desallocate_b(t_block *b, size_t size)
{
	b->flag |= FLAG_FREE;
	if (size <= MAX_SMALL || IS_CANT_SPLIT(b))
		b = merge_bs(b);
	if ((IS_START_HEAP(b) && !b->next && !getenv("DONT_FREE_ADD_POOL"))
		|| (size > MAX_SMALL && !IS_CANT_SPLIT(b)))
	{
		pop_b(b, size);
		if ((size > MAX_SMALL && !IS_CANT_SPLIT(b)) && !b->prev && !b->next)
		{
			malloc_debug(SUCCES, "Free : ", "Reset LARGE");
			g_env.large = NULL;
		}
		if (munmap(b, b->size + BLOCK_SIZE) == -1)
		{
			malloc_debug(ERROR, "Free : ", "MUNMAP failed");
			return (0);
		}
		b = NULL;
		malloc_debug(SUCCES, "Free : ", "MUNMAP");
	}
	else if (IS_CANT_SPLIT(b))
		b->flag ^= FLAG_CANT_SPLIT;
	return (1);
}

char			use_block(t_block *start, t_block *block)
{
	if (start && block)
	{
		while (start && start != block)
			start = start->next;
		if (start)
			return (1);
	}
	return (0);
}

void			free(void *ptr)
{
	t_block	*b;
	char	*str;

	malloc_debug(HEADER, "-- FREE --", "");
	pthread_mutex_lock(&g_thread_safe.mutex_free);
	if (!ptr)
		malloc_debug(ERROR, "Free : ", "NULL ptr");
	else
	{
		b = (t_block*)(ptr - BLOCK_SIZE);
		if ((EXIST_BLOCK) && !IS_FREE(b))
		{
			if (b->size > MAX_SMALL && !IS_CANT_SPLIT(b))
				str = "Free LARGE : ";
			else
				str = "Free TINY or SMALL : ";
			if (desallocate_b(b, b->size))
				malloc_debug(SUCCES, str, "Succes !");
			else
				malloc_debug(ERROR, "Free : ", "failed");
		}
		else
			malloc_debug(ERROR, "Free : ", "failed");
	}
	pthread_mutex_unlock(&g_thread_safe.mutex_free);
}
