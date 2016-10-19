#include "malloc.h"

t_env	env;
t_thread_safe	thread_safe = {
	.mutex_malloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_calloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_realloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_free = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem_ex = PTHREAD_MUTEX_INITIALIZER,
};

void	*allocate_with_mmap(size_t size)
{
	void	*ret;
	static int mdr = 0;
	static int i = 0;

	mdr += size / getpagesize();
	// ft_putstr("MDRRRRRRRR:");
	// ft_putnbr(mdr);
	// ft_putstr("\n\n");
	if (size % getpagesize())
		size = (size / getpagesize() + 1) * getpagesize();
	
	ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	i += size;
	// ft_putstr("getpagesize = ");
	// ft_putnbr(getpagesize());
	// ft_putstr("\nnb alloc = ");
	// ft_putnbr(i / getpagesize());
	// ft_putstr("\nsize / getpagesize = ");
	// ft_putnbr(size / getpagesize());
	// ft_putstr("\nsize = ");
	// ft_putnbr(size);
	// ft_putstr("\n");
	if (ret == (void*)-1)
		malloc_debug(ERROR, "Malloc : ", "MMAP failed");
	else
		malloc_debug(SUCCES, "Malloc : ", "MMAP succes");
	return (ret);
}

t_block	*allocate_first_block(size_t size)
{
	t_block	*newblock;
	
	malloc_debug(SUCCES, "Malloc : ", "Allocate first pool");
	if ((newblock = (t_block*)allocate_with_mmap(size)) == (void*)-1)
		return (NULL);
	newblock->flag |= FLAG_FREE;
	newblock->size = size - BLOCK_SIZE;
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

	// ft_putnbr(size);
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
		tmp = tmp->next;
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
		newblock = (void*)block->data + size;
		newblock->size = block->size - size - BLOCK_SIZE;
		newblock->flag |= FLAG_FREE;
		block->size = size;
		block->next = newblock;
		newblock->prev = block;
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

	// ft_putstr("malloc\n");
	malloc_debug(SUCCES, "-- MALLOC --", "");
	pthread_mutex_lock(&thread_safe.mutex_malloc);
	size = ALIGN4(size);
	if (!env.tiny && init() == -1)
	{
		malloc_debug(ERROR, "Malloc : ", "Malloc failed : init error");
		return (NULL);
	}
	block = fill_block(get_block(size), size);
	// show_alloc_mem();
	pthread_mutex_unlock(&thread_safe.mutex_malloc);
	// ft_putstr("alloc block ---> ");
	// ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
	if (block)
	{
	// ft_putstr("alloc data---> ");
	// ft_puthexa((unsigned long)block->data, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
		malloc_debug(SUCCES, "Malloc : ", "Malloc succes !");
		return (block->data);
	}
	malloc_debug(ERROR, "Malloc : ", "Malloc failed : block null");
	return (block);
}