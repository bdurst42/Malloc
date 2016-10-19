#include "malloc.h"

t_block	*merge_blocks(t_block *block)
{
	malloc_debug(ERROR, "Free : ", "Merge blocks");
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
	malloc_debug(SUCCES, "Free : ", "Pop block");
	if (block->prev)
		block->prev->next = block->next;
	if (block->next)
		block->next->prev = block->prev;
}

void	deallocate_block(t_block *block)
{
	block->flag |= FLAG_FREE;
		// ft_putstr("before size = ");
		// ft_putnbr(block->size);
		// ft_putstr("\nflag = ");
		// ft_putnbr(block->flag);
		// ft_putstr("\n");
	if (block->size <= MAX_SMALL)
	{
		block = merge_blocks(block);
	}
	else if ((IS_START_HEAP(block) && !block->next && !getenv("DONT_FREE_ADDED_POOL")) || block->size > MAX_SMALL)
	{
		if (!munmap(block->data, block->size))
			malloc_debug(SUCCES, "Free : ", "MUNMAP");
		else
		{
			malloc_debug(ERROR, "Free : ", "MUNMAP failed");
			return ;
		}
		pop_block(block);
	}
}

void	free(void *ptr)
{
	t_block *block;

	malloc_debug(SUCCES, "-- FREE --", "");
	// ft_putstr("free -> ");
	// ft_puthexa((unsigned long)ptr, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
	pthread_mutex_lock(&thread_safe.mutex_free);
	block = (t_block*)(ptr - BLOCK_SIZE);
	// ft_putnbr((int)block->data);
	// ft_putstr("\nblock free-> ");
	// ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
	if (block && !IS_FREE(block) && block->data == block->ptr)
	{
		deallocate_block(block);
		// ft_putstr("after\n");
	}
	else
		malloc_debug(ERROR, "Free : ", "failed");	
	pthread_mutex_unlock(&thread_safe.mutex_free);
}