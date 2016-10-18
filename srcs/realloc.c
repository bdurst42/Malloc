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
		return (1);
	}
	return (0);
}

void	copy_block(t_block *block, t_block *newblock)
{
	size_t	i;

	i = -1;
	while (++i < block->size && i < newblock->size)
		newblock->data[i] = block->data[i];
}

void	*new_alloc(t_block *block, size_t size)
{
	void	*new_ptr;
	t_block	*newblock;

	newblock = NULL;
	if (!(new_ptr = malloc(size)))
		return (NULL);
	newblock = (t_block*)(new_ptr - BLOCK_SIZE);
	copy_block(block, newblock);
	free(block->data);
	return (newblock->data);
}

void	*realloc(void *ptr, size_t size)
{
	t_block *block;
	char	merge;

	merge = 0;
	pthread_mutex_lock(&thread_safe.mutex_realloc);
	if (!ptr)
	{
		pthread_mutex_unlock(&thread_safe.mutex_realloc);
		return (malloc(size));
	}
	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block->size == size)
	{
		pthread_mutex_unlock(&thread_safe.mutex_realloc);
		return (ptr);
	}
	if (block && block->data == block->ptr)
	{
		size = ALIGN4(size);
		if ((block->size <= MAX_TINY && size <= MAX_TINY)
			| (block->size <= MAX_SMALL && size <= MAX_SMALL))
		{
			if (block->size >= size)
				split_block(block, size);
			else
				merge = try_merge_with_next_block(block, size);
		}
		else if (!merge)
		{
			pthread_mutex_unlock(&thread_safe.mutex_realloc);
			return new_alloc(block, size);
		}
	}
	pthread_mutex_unlock(&thread_safe.mutex_realloc);
	return (NULL);
}