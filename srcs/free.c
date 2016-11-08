#include "malloc.h"

static t_block	*merge_blocks(t_block *block)
{
	malloc_debug(SUCCES, "Free : ", "Merge blocks");
	while (!IS_START_HEAP(block) && block->prev && IS_FREE(block->prev))
		block = block->prev;
	while (block->next && IS_FREE(block->next) && !IS_START_HEAP(block->next))
	{
		block->size += BLOCK_SIZE + block->next->size;
		block->next = block->next->next;
	}
	if (block->next)
		block->next->prev = block;
	return (block);
}

static void	pop_block(t_block *block, size_t size)
{
	malloc_debug(SUCCES, "Free : ", "Pop block");
	if (block->prev)
		block->prev->next = block->next;
	if (block->next)
	{

		if ((size > MAX_SMALL && !IS_CANT_SPLIT(block)) && !block->prev)
			env.large = block->next;
		block->next->prev = block->prev;
	}
}

static char	desallocate_block(t_block *block)
{
	size_t size;

	size = block->size;
	block->flag |= FLAG_FREE;
	if (size <= MAX_SMALL || IS_CANT_SPLIT(block))
		block = merge_blocks(block);
	if ((IS_START_HEAP(block) && !block->next && !getenv("DONT_FREE_ADDED_POOL")) || (size > MAX_SMALL && !IS_CANT_SPLIT(block)))
	{
		pop_block(block, size);
		if ((size > MAX_SMALL && !IS_CANT_SPLIT(block)) && !block->prev && !block->next)
		{
			malloc_debug(SUCCES, "Free : ", "Reset LARGE");
			env.large = NULL;
		}
		if (munmap(block, block->size + BLOCK_SIZE) == -1)
		{
			ft_putstr("munmap fail\n");
			ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
			ft_putstr("\nNEXT = \n");
			ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
			ft_putstr("\nflag = \n");
			ft_putnbr(block->flag);
			ft_putstr("\nsize = ");
			ft_putnbr(block->size);
			ft_putstr("\n");
			// show_alloc_mem();
			malloc_debug(ERROR, "Free : ", "MUNMAP failed");
			return (0);
		}
		block = NULL;
		malloc_debug(SUCCES, "Free : ", "MUNMAP");
	}
	else if (IS_CANT_SPLIT(block))
		block->flag ^= FLAG_CANT_SPLIT;
	return (1);
}

void	free(void *ptr)
{
	t_block *block;
	char	*str;

	malloc_debug(HEADER, "-- FREE --", "");
	// pthread_mutex_lock(&thread_safe.mutex_free);
	// ft_putstr("free addr : \n");
	// ft_puthexa((unsigned long)ptr, 16, "0123456789 ABCDEF");
	// ft_putstr("\n");
	if (!ptr)
	{
		malloc_debug(ERROR, "Free : ", "NULL ptr");
		ft_putstr("NULL\n");
		return ;
	}
	block = (t_block*)(ptr - BLOCK_SIZE);
	if (block && !IS_FREE(block) && block->data == block->ptr)
	{
		if (block->size > MAX_SMALL && !IS_CANT_SPLIT(block))
			str = "Free LARGE : ";
		else
			str = "Free TINY or SMALL : ";
		if (desallocate_block(block))
			malloc_debug(SUCCES, str, "Succes !");
		else
			malloc_debug(ERROR, "Free : ", "failed");
	}
	else
	{
		// ft_putstr("BAD\n");
		malloc_debug(ERROR, "Free : ", "failed");
	}
	// pthread_mutex_unlock(&thread_safe.mutex_free);
}