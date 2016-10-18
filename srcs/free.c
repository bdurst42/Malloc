#include "malloc.h"

t_block	*merge_blocks(t_block *block)
{
	if (!IS_START_HEAP(block))
	{
		while (block->prev && IS_FREE(block->prev)
			&& !IS_START_HEAP(block->prev))
			block = block->prev;
	}
	while (block->next && IS_FREE(block->next) && !IS_START_HEAP(block->next))
	{
		block->size += BLOCK_SIZE + block->next->size;
		block->next = block->next->next;
	}
	if (block->next)
		block->next->prev = block;
	return (block);
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
	block->flag |= FLAG_FREE;
		ft_putstr("before size = ");
		ft_putnbr(block->size);
		ft_putstr("\nflag = ");
		ft_putnbr(block->flag);
		ft_putstr("\n");
	if (block->size <= MAX_SMALL)
	{
		block = merge_blocks(block);
	}
	else if ((IS_START_HEAP(block) && !block->next) || block->size > MAX_SMALL)
	{
		munmap(block->data, block->size);
		pop_block(block);
	}
}

void	free(void *ptr)
{
	t_block *block;

	pthread_mutex_lock(&thread_safe.mutex_free);
	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block && !IS_FREE(block))
	{
		deallocate_block(block);
		ft_putstr("after\n");
	}
	pthread_mutex_unlock(&thread_safe.mutex_free);
}