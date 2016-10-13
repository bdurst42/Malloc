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
	t_block	*newblock;

	if (!(newblock = malloc(size)))
		return (NULL);
	newblock = (t_block*)(newblock - BLOCK_SIZE);
	copy_block(block, newblock);
	free(new_alloc);
	return (newblock);
}

void	*realloc(void *ptr, size_t size)
{
	t_block *block;
	char	merge;

	merge = 0;
	if (!ptr)
		return (malloc(size));
	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block->size == size)
		return (ptr);
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
			return new_alloc(block, size);
	}
	return (NULL);
}