#include "malloc.h"

t_env	env;
// t_thread_safe	thread_safe = {
	// .mutex_malloc = PTHREAD_MUTEX_INITIALIZER,
	// .mutex_calloc = PTHREAD_MUTEX_INITIALIZER,
	// .mutex_realloc = PTHREAD_MUTEX_INITIALIZER,
	// .mutex_free = PTHREAD_MUTEX_INITIALIZER,
	// .mutex_show_alloc_mem = PTHREAD_MUTEX_INITIALIZER,
	// .mutex_show_alloc_mem_ex = PTHREAD_MUTEX_INITIALIZER,
// };

static t_block	*allocate_with_mmap(size_t size)
{
	void	*ret;
	t_block	*newblock;
	static int mdr = 0;
	static int i = 0;

	mdr += size / getpagesize();
	if (size % getpagesize())
		size = (size / getpagesize() + 1) * getpagesize();
	
	ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	i += size;
	if (ret == (void*)-1)
		malloc_debug(ERROR, "Malloc : ", "MMAP failed");
	else
		malloc_debug(SUCCES, "Malloc : ", "MMAP succes");
	newblock = (t_block*)ret;
	newblock->size = size - BLOCK_SIZE;
	return (newblock);
}

t_block	*allocate_first_block(size_t size)
{
	t_block	*newblock;
	
	malloc_debug(SUCCES, "Malloc : ", "Allocate first pool");
	if ((newblock = allocate_with_mmap(size)) == (void*)-1)
		return (NULL);
	newblock->flag |= FLAG_FREE;
	return (newblock);
}

char	init(void)
{
	malloc_debug(SUCCES, "Malloc : ", "Init");
	if (!(env.tiny = allocate_first_block(MAX_TINY * POOL_SIZE)) ||
	 		!(env.small = allocate_first_block(MAX_SMALL * POOL_SIZE)))
			return (0);
	env.large = NULL;
	return (0);
}

t_block	*get_block(size_t size)
{
	t_block	*tmp;

	if (size <= MAX_TINY)
	{
	 	malloc_debug(SUCCES, "Malloc : ", "Get TINY");
		tmp = env.tiny;
	}
	else if (size <= MAX_SMALL)
	{
	 	malloc_debug(SUCCES, "Malloc : ", "Get SMALL");
		tmp = env.small;
	}
	else
	{
	 	malloc_debug(SUCCES, "Malloc : ", "Get LARGE");
		tmp = env.large;
	}
	while (tmp && tmp->next && (size > MAX_SMALL || !IS_FREE(tmp) || tmp->size < size))
	{
		ft_putstr("loop\n");
		tmp = tmp->next;
	}
	if (tmp)
	{
		ft_putstr("tmp->next = ");
		ft_puthexa((unsigned long)tmp->next, 16, "0123456789ABCDEF");
		ft_putstr("\n");
	}
	else
		ft_putstr("tmp doesn't exist\n");
	return (tmp);
}

t_block	*split_block(t_block *block, size_t size)
{
	t_block *newblock;

	newblock = NULL;
	if (size > MAX_SMALL)
	{
		malloc_debug(SUCCES, "Malloc : ", "Split LARGE block");
		if ((newblock = (t_block*)allocate_with_mmap(size)) == (void*)-1)
			return (NULL);
		newblock->flag |= FLAG_FREE;
		newblock->size = size;
		newblock->next = NULL;
		newblock->prev = NULL;
		if (block)
		{
			newblock->prev = block;
			block->next = newblock;
		}
		else
			env.large = newblock;
		return (newblock);
	}
	else if ((size > MAX_TINY && block->size - size > BLOCK_SIZE + MAX_TINY) || (size <= MAX_TINY && block->size - size >= BLOCK_SIZE + 4))
	{
		malloc_debug(SUCCES, "Malloc : ", "Split TINY or SMALL block");
		ft_putstr("block = ");
		ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
		ft_putstr("\nblock->size = ");
		ft_putnbr(block->size);
		ft_putstr("\nblock->flag = ");
		ft_putnbr(block->flag);
		ft_putstr("\nblock->next = ");
		ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
		ft_putstr("\nblock->prev = ");
		ft_puthexa((unsigned long)block->prev, 16, "0123456789ABCDEF");
		ft_putstr("\n\n");
		newblock = (void*)block->data + size;
		newblock->size = block->size - size - BLOCK_SIZE;
		newblock->flag |= FLAG_FREE;
		block->size = size;
		newblock->next = block->next;
		block->next = newblock;
		newblock->prev = block;
		ft_putstr("block = ");
		ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
		ft_putstr("\nblock->size = ");
		ft_putnbr(block->size);
		ft_putstr("\nblock->flag = ");
		ft_putnbr(block->flag);
		ft_putstr("\nblock->next = ");
		ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
		ft_putstr("\nblock->prev = ");
		ft_puthexa((unsigned long)block->prev, 16, "0123456789ABCDEF");
		ft_putstr("\n\n");
		ft_putstr("newblock = ");
		ft_puthexa((unsigned long)newblock, 16, "0123456789ABCDEF");
		ft_putstr("\nnewblock->size = ");
		ft_putnbr(newblock->size);
		ft_putstr("\nnewblock->flag = ");
		ft_putnbr(newblock->flag);
		ft_putstr("\nnewblock->next = ");
		ft_puthexa((unsigned long)newblock->next, 16, "0123456789ABCDEF");
		ft_putstr("\nnewblock->prev = ");
		ft_puthexa((unsigned long)newblock->prev, 16, "0123456789ABCDEF");
		ft_putstr("\n\n");
	}
	return (block);
}

t_block	*fill_block(t_block *block, size_t size)
{
	if (size <= MAX_SMALL && (!IS_FREE(block) || block->size < size))
	{
		if (size > MAX_TINY)
		{
			malloc_debug(SUCCES, "Malloc : ", "Allocate new pool of SMALL");
			block->next = allocate_first_block(MAX_SMALL * POOL_SIZE);
		}
		else
		{
			malloc_debug(SUCCES, "Malloc : ", "Allocate new pool of TINY");
			block->next = allocate_first_block(MAX_TINY * POOL_SIZE);
		}
		block->next->flag |= FLAG_START_HEAP;
		block = block->next;
	}
	if (size > MAX_SMALL || size < block->size)
		block = split_block(block, size);
	if (block)
	{
		block->ptr = block->data;
		block->flag ^= FLAG_FREE;
	}
	return (block);
}



void	*malloc(size_t size)
{
	t_block *block;

	malloc_debug(SUCCES, "-- MALLOC --", "");
	// pthread_mutex_lock(&thread_safe.mutex_malloc);
	size = ALIGN4(size);
	if (!env.tiny && init() == -1)
	{
		malloc_debug(ERROR, "Malloc : ", "Malloc failed : init error");
		return (NULL);
	}
	block = fill_block(get_block(size), size);
	// show_alloc_mem();
	// pthread_mutex_unlock(&thread_safe.mutex_malloc);

	if (block)
	{
		malloc_debug(SUCCES, "Malloc : ", "Malloc succes !");
		return (block->data);
	}
	malloc_debug(ERROR, "Malloc : ", "Malloc failed : block null");
	return (block);
}