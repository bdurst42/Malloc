#include "malloc.h"

static t_block	*merge_blocks(t_block *block)
{
	malloc_debug(SUCCES, "Free : ", "Merge blocks");
	// ft_putstr("!!!!!!!!!!!!!!!!!!!!!!!! block->prev :\n");
	// if (block->prev)
	// {
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->prev->size);
	// 	ft_putstr("\nfree = ");
	// 	ft_putnbr(IS_FREE(block->prev));
	// 	ft_putstr("\n flag = ");
	// 	ft_putnbr(block->prev->flag);
	// 	ft_putstr("\nstart heap = ");
	// 	ft_putnbr(IS_START_HEAP(block->prev));
	// }
	// while (!IS_START_HEAP(block) && block->prev && IS_FREE(block->prev))
	// {
	// 	block = block->prev;
	// }
	while (block->next && IS_FREE(block->next) && !IS_START_HEAP(block->next))
	{
		// if (block->prev)
		// {
		// 	ft_putstr("\n?????????????????? block->prev :\n");
		// ft_puthexa((unsigned long)block->prev, 16, "0123456789ABCDEF");
		// ft_putstr("\n");
		// ft_putstr("size = ");
		// ft_putnbr(block->prev->size);
		// ft_putstr("\n");
		// ft_putstr("flag = ");
		// ft_putnbr(block->prev->flag);
		// ft_putstr("\n");
		// }
		// ft_putstr("?????????????????? block :\n");
		// ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
		// ft_putstr("\n");
		// ft_putstr("size = ");
		// ft_putnbr(block->size);
		// ft_putstr("\n");
		// ft_putstr("flag = ");
		// ft_putnbr(block->flag);
		// ft_putstr("\n");
		// ft_putstr("????????????????????????? block->next :\n");
		// ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
		// ft_putstr("\n");
		// ft_putstr("size = ");
		// ft_putnbr(block->next->size);
		// ft_putstr("\n");
		// ft_putstr("flag = ");
		// ft_putnbr(block->next->flag);
		// ft_putstr(" ?????????????????????????????????????\n");
		block->size += BLOCK_SIZE + block->next->size;
		block->next = block->next->next;
	}
	if (block->next)
		block->next->prev = block;
	// ft_putstr("\n{{{{{{{{{{ block->prev :\n");
	// if (block->prev)
	// {
	// ft_puthexa((unsigned long)block->prev, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->prev->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(block->prev->flag);
	// 	ft_putstr("\n");
	// }
	// 	ft_putstr("?????????????????? block :\n");
	// 	ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(block->flag);
	// 	ft_putstr("\n");
	// ft_putstr("????????????????????????? block->next :\n");
	// if (block->next)
	// {	
	// 	ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->next->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(block->next->flag);
	// 	ft_putstr(" }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}\n");
	// }
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

char	deallocate_block(t_block *block)
{
	size_t size;

	size = block->size;
	// ft_putstr("[[[[[[[[[[[[[[[[[[[[[[[ before flag = ");
	// 	ft_putnbr(block->flag);
	// 	ft_putstr("\n");
	block->flag |= FLAG_FREE;
	// ft_putstr("after flag = ");
	// 	ft_putnbr(block->flag);
	// 	ft_putstr("  ]]]]]]]]]]]]]]]]\n");
	if (size <= MAX_SMALL || IS_CANT_SPLIT(block))
	{
		block = merge_blocks(block);
	}
	if ((IS_START_HEAP(block) && !block->next && !getenv("DONT_FREE_ADDED_POOL")) || (size > MAX_SMALL && !IS_CANT_SPLIT(block)))
	{
		pop_block(block, size);
		if ((size > MAX_SMALL && !IS_CANT_SPLIT(block)) && !block->prev && !block->next)
		{
			malloc_debug(SUCCES, "Free : ", "Reset LARGE");
			env.large = NULL;
		}
		// ft_putstr("MUNMAP ======= ");
		// ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
		// ft_putstr("\n");
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
		// ft_putstr("\n");
		// show_alloc_mem();
			malloc_debug(ERROR, "Free : ", "MUNMAP failed");
			exit(0);
			return (0);
		}
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
	if (!ptr)
	{
		malloc_debug(ERROR, "Free : ", "NULL ptr");
		ft_putstr("NULL\n");
		return ;
	}
	block = (t_block*)(ptr - BLOCK_SIZE);
	// ft_putstr("block->prev->prev : \n");
	// if (block->prev &&block->prev->prev)
	// {
	// 	ft_puthexa((unsigned long)block->prev->prev, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->prev->prev->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(block->prev->prev->flag);
	// 	ft_putstr("\n");
	// }
	// ft_putstr("block->prev : \n");
	// if (block->prev)
	// {
	// 	ft_puthexa((unsigned long)block->prev, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->prev->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(block->prev->flag);
	// 	ft_putstr("\n");
	// }
	ft_putstr("block : \n");
	ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(block->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(block->flag);
	ft_putstr("\n");
	ft_putstr("block->next : \n");
	// if (block->next)
	// {
	// 	ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(block->next->size);
	// 	ft_putstr("\nflag = ");
	// 	ft_putnbr(block->next->flag);
	// 	ft_putstr("\n");
	// }
	// ft_putstr("block->next->next : \n");
	// if (block->next && block->next->next)
	// {
	// 	ft_puthexa((unsigned long)block->next->next, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = \n");
	// 	ft_putstr("wtf --> ");
	// 	ft_putnbr(block->next->next->size);
	// 	ft_putstr("\nflag = ");
	// 	ft_putnbr(block->next->next->flag);
	// 	ft_putstr("\n");
	// }
	if (block && !IS_FREE(block) && block->data == block->ptr)
	{
		if (block->size > MAX_SMALL && !IS_CANT_SPLIT(block))
			str = "Free LARGE : ";
		else
			str = "Free TINY or SMALL : ";
		if (deallocate_block(block))
			malloc_debug(SUCCES, str, "Succes !");
		else
			malloc_debug(ERROR, "Free : ", "failed");
	}
	else
	{
		ft_putstr("BAD\n");
		malloc_debug(ERROR, "Free : ", "failed");
	}
	// pthread_mutex_unlock(&thread_safe.mutex_free);
}