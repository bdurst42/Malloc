#include "malloc.h"

char	try_merge_with_next_block(t_block *block, size_t size)
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

void	copy_block(t_block *block, t_block *newblock)
{
	size_t	i;

	malloc_debug(SUCCES, "Realloc : ", "Copy");
	i = -1;
	while (++i < block->size && i < newblock->size)
		newblock->data[i] = block->data[i];
}

void	*new_alloc(t_block *block, size_t size)
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
	free(block->data);
	return (newblock->data);
}

void	*realloc(void *ptr, size_t size)
{
	t_block *block;
	char	merge;
	size_t	align_size;

	merge = 0;
	malloc_debug(HEADER, "-- REALLOC --", "");
	if (!ptr)
	{
		malloc_debug(SUCCES, "Realloc : ", "Addr null");
		malloc_debug(SUCCES, "Realloc : ", "New alloc");
		// pthread_mutex_unlock(&thread_safe.mutex_realloc);
		return (malloc(size));
	}
	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block && block->data == block->ptr)
	{
		size = ALIGN4(size);
	// 	ft_putstr("REALLOC after ALIGN size = ");
	// ft_putnbr(size);
	// ft_putstr("\n");
		if (size > MAX_SMALL && !IS_CANT_SPLIT(block) && (size + 36) % getpagesize())
			align_size = ((size + 36) / getpagesize() + 1) * getpagesize() - 36;
		else
			align_size = size;
		if (block->size == align_size)
		{
			malloc_debug(SUCCES, "Realloc : ", "Same size when we align at 4");
			// pthread_mutex_unlock(&thread_safe.mutex_realloc);
			return (ptr);
		}
		if ((size <= MAX_TINY && (block->size <= MAX_TINY || (IS_CANT_SPLIT(block) && block->size <= MAX_SMALL)))
			|| (size <= MAX_SMALL && size > MAX_TINY && block->size > MAX_TINY && (block->size <= MAX_SMALL || (IS_CANT_SPLIT(block) && block->size > MAX_SMALL))))
		{
			if (block->size >= size && block->size - size >= BLOCK_SIZE + 4)
				split_block(block, size, 1);
			else
				merge = try_merge_with_next_block(block, size);
		}
		else if (!merge)
		{
			// pthread_mutex_unlock(&thread_safe.mutex_realloc);
			return (new_alloc(block, size));
		}
		return (block->data);
	}
	// pthread_mutex_unlock(&thread_safe.mutex_realloc);
	malloc_debug(ERROR, "Realloc : ", "failed :(");
	return (NULL);
}