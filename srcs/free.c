#include "malloc.h"

t_block	*merge_blocks(t_block *block)
{
	malloc_debug(SUCCES, "Free : ", "Merge blocks");
	if (!IS_START_HEAP(block))
	{
		while (block->prev && IS_FREE(block->prev)
			&& !IS_START_HEAP(block->prev))
		{
			block = block->prev;
		}
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
	else
	{
		if (block->next)
		{
			env.large = block->next;
			block->next->prev = block->prev;
		}
	}
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
		pop_block(block);
		if (block->size > MAX_SMALL && !block->prev && !block->next)
			env.large = NULL;
		if (munmap(block, block->size + BLOCK_SIZE) == -1)
		{
			malloc_debug(ERROR, "Free : ", "MUNMAP failed");
			return ;
		}
		malloc_debug(SUCCES, "Free : ", "MUNMAP");
	}
}

void	free(void *ptr)
{
	t_block *block;

	malloc_debug(SUCCES, "-- FREE --", "");
	// pthread_mutex_lock(&thread_safe.mutex_free);
	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block && !IS_FREE(block) && block->data == block->ptr)
	{
		deallocate_block(block);
		malloc_debug(SUCCES, "Free : ", "Succes !");	
	}
	else
	{
		malloc_debug(ERROR, "Free : ", "failed");	
	}
	// pthread_mutex_unlock(&thread_safe.mutex_free);
}