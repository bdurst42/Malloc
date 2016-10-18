#include "malloc.h"

t_env	env;
t_thread_safe	thread_safe = {
	.mutex_malloc = PTHREAD_MUTEX_INITIALIZER,
	// .mutex_calloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_realloc = PTHREAD_MUTEX_INITIALIZER,
	.mutex_free = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem = PTHREAD_MUTEX_INITIALIZER,
	.mutex_show_alloc_mem_ex = PTHREAD_MUTEX_INITIALIZER,
};

void	*allocate_with_mmap(size_t size)
{
	static int mdr = 0;
	mdr += size / getpagesize();
	ft_putstr("MDRRRRRRRR:");
	ft_putnbr(mdr);
	ft_putstr("\n\n");
	return (mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
}

t_block	*allocate_first_block(size_t size)
{
	t_block	*newblock;
	static int i = 0;

	if (size % getpagesize())
		size = (size / getpagesize() + 1) * getpagesize();
	if ((newblock = (t_block*)allocate_with_mmap(size)) == (void*)-1)
		return (NULL);
	newblock->flag |= FLAG_FREE;
	newblock->size = size - BLOCK_SIZE;
	i += size;
	ft_putstr("getpagesize = ");
	ft_putnbr(getpagesize());
	ft_putstr("\nnb alloc = ");
	ft_putnbr(i / getpagesize());
	ft_putstr("\nsize / getpagesize = ");
	ft_putnbr(size / getpagesize());
	ft_putstr("\nsize = ");
	ft_putnbr(size);
	ft_putstr("\n");
	return (newblock);
}

char	init(void)
{
	if (!(env.tiny = allocate_first_block(MAX_TINY * POOL_SIZE)) ||
	 		!(env.small = allocate_first_block(MAX_SMALL * POOL_SIZE)))
			return (0);
	env.large = NULL;
	return (0);
}

t_block	*find_block(size_t size)
{
	t_block	*tmp;

	// ft_putnbr(size);
	if (size <= MAX_TINY)
	{
	// ft_putstr(" FIND TINY\n");
		tmp = env.tiny;
	}
	else if (size <= MAX_SMALL)
	{
	// ft_putstr(" FIND SMALL\n");

		tmp = env.small;
	}
	else
	{
	// ft_putstr(" FIND LARGE\n");
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
			block->next = allocate_first_block(MAX_SMALL * POOL_SIZE);
		else
			block->next = allocate_first_block(MAX_TINY * POOL_SIZE);
		block->next->flag |= FLAG_START_HEAP;
		block = block->next;
	}
	if (size > MAX_SMALL || size < block->size)
		block = split_block(block, size);
	if (block)
		block->flag ^= FLAG_FREE;
	return (block);
}



void	*malloc(size_t size)
{
	t_block *block;

	// ft_putstr("malloc\n");
	pthread_mutex_lock(&thread_safe.mutex_malloc);
	size = ALIGN4(size);
	if (!env.tiny && init() == -1)
		return (NULL);
	block = fill_block(find_block(size), size);
	show_alloc_mem_ex();
	pthread_mutex_unlock(&thread_safe.mutex_malloc);
	if (block)
		return (block->data);
	return (block);
}