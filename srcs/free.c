#include "malloc.h"

void	merge_blocks(t_block *block)
{
	while (block->prev && IS_FREE(block->prev))
		block = block->prev;
	while (block->next && IS_FREE(block->next))
	{
		block->size += BLOCK_SIZE + block->next->size;
		block->next = block->next->next;
	}
	if (block->next)
		block->next->prev = block;
}

void	pop_block(t_block *block)
{
	if (block->prev)
		block->prev->next = block->next;
	if (block->next)
		block->next->prev = block->prev;
}

void	deallocate_block(t_block *block)
{
	block->flag ^= FLAG_FREE;
	if (block->size > MAX_SMALL)
	{
		munmap(block->data, block->size);
		pop_block(block);
	}
	else
	{
		merge_blocks(block);
	}
}

void	free(void *ptr)
{
	t_block *block;

	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block && !IS_FREE(block) && block->data == block->ptr)
		deallocate_block(block);
}