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

static t_block	*allocate_with_mmap(size_t size, char *name)
{
	void	*ret;
	t_block	*newblock;

	if (size % getpagesize())
		size = (size / getpagesize() + 1) * getpagesize();
	
	ret = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	newblock = (t_block*)ret;
	if (ret == (void*)-1)
		malloc_debug(ERROR, name, "MMAP failed");
	else
	{
		malloc_debug(SUCCES, name, "MMAP succes");
		newblock->size = size - BLOCK_SIZE;
	}
	return (newblock);
}

t_block	*allocate_first_block(size_t size)
{
	t_block	*newblock;
	
	malloc_debug(SUCCES, "Malloc : ", "Allocate first pool");
	if ((newblock = allocate_with_mmap(size, "Malloc : ")) == (void*)-1)
		return (NULL);
	newblock->flag |= FLAG_FREE;
	return (newblock);
}

char	init(void)
{
	malloc_debug(SUCCES, "Malloc : ", "Init");
	if (!(env.tiny = allocate_first_block((MAX_TINY + BLOCK_SIZE) * POOL_SIZE)) ||
	 		!(env.small = allocate_first_block((MAX_SMALL + BLOCK_SIZE) * POOL_SIZE)))
			return (0);
	env.large = NULL;
	return (0);
}

static t_block	*get_block(size_t size)
{
	t_block	*tmp;

	ft_putstr("tiny : \n");
	if (env.tiny)
	{
	ft_puthexa((unsigned long)env.tiny, 16, "0123456789ABCDEF");
	ft_putstr("\n");
		}
	// ft_putstr("size = ");
	// ft_putnbr(env.tiny->size);
	// ft_putstr("\n");
	// ft_putstr("flag = ");
	// ft_putnbr(env.tiny->flag);
	// ft_putstr("\n");
	// }
	// ft_putstr("small : \n");
	// if (env.small)
	// {
	// 	tmp = env.small;
	// 	ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(tmp->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(tmp->flag);
	// 	ft_putstr("\n");
	// 	ft_putstr("large : \n");
	// }
	// if (env.large)
	// {
	// 	tmp = env.large;
	// 	ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(tmp->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(tmp->flag);
	// 	ft_putstr("\n");
	// }
	if (size <= MAX_TINY)
	{
		ft_putstr("get size --> ");
		ft_putnbr(size);
		ft_putstr("\n");
	 	malloc_debug(SUCCES, "Malloc : ", "Get TINY");
		tmp = env.tiny;
	}
	else if (size <= MAX_SMALL)
	{
		ft_putstr("get size --> ");
		ft_putnbr(size);
		ft_putstr("\n");
	 	malloc_debug(SUCCES, "Malloc : ", "Get SMALL");
	ft_putstr("step 3\n");
		tmp = env.small;
		ft_putstr("step 4\n");
	}
	else
	{
		ft_putstr("get size --> ");
		ft_putnbr(size);
		ft_putstr("\n");
	 // 	ft_putstr("\nMalloc : Get LARGE\n");
	 	malloc_debug(SUCCES, "Malloc : ", "Get LARGE");
		tmp = env.large;
	}
	ft_putstr("step 1\n");
	if (tmp)
	{
	ft_putstr("tmp : \n");
	ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(tmp->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(tmp->flag);
	ft_putstr("\n");
	ft_putstr("tmp->prev : \n");
	if (tmp->prev)
	{
		ft_puthexa((unsigned long)tmp->prev, 16, "0123456789ABCDEF");
		ft_putstr("\n");
		ft_putstr("size = ");
		ft_putnbr(tmp->prev->size);
		ft_putstr("\n");
		ft_putstr("flag = ");
		ft_putnbr(tmp->prev->flag);
		ft_putstr("\n");
	}
	// ft_putstr("tmp : \n");
	// ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
	// ft_putstr("size = ");
	// ft_putnbr(tmp->size);
	// ft_putstr("\n");
	// ft_putstr("flag = ");
	// ft_putnbr(tmp->flag);
	// ft_putstr("\n");
	ft_putstr("tmp->next : \n");
	if (tmp->next)
	{
		ft_puthexa((unsigned long)tmp->next, 16, "0123456789ABCDEF");
		ft_putstr("\n");
		ft_putstr("-----------------------------------------------> size = ");
		ft_putnbr(tmp->next->size);
		ft_putstr("\nflag = ");
		ft_putnbr(tmp->next->flag);
		ft_putstr("\n");
	}
	}
	ft_putstr("tmp : \n");
	if (tmp)
	{
	ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(tmp->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(tmp->flag);
	ft_putstr("\n");
	ft_putstr("step 2\n");
	}
	while (tmp && tmp->next && (size > MAX_SMALL || !IS_FREE(tmp) || tmp->size < size))
		tmp = tmp->next;
	ft_putstr("tmp : \n");
	if (tmp)
	{
	ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(tmp->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(tmp->flag);
	ft_putstr("\n");
	ft_putstr("step 2\n");
	}
	// ft_putstr("tmp->prev : \n");
	// if (tmp)
	// {
	// if (tmp->prev)
	// {
	// 	ft_puthexa((unsigned long)tmp->prev, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = ");
	// 	ft_putnbr(tmp->prev->size);
	// 	ft_putstr("\n");
	// 	ft_putstr("flag = ");
	// 	ft_putnbr(tmp->prev->flag);
	// 	ft_putstr("\n");
	// }
	// ft_putstr("tmp : \n");
	// ft_puthexa((unsigned long)tmp, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
	// ft_putstr("size = ");
	// ft_putnbr(tmp->size);
	// ft_putstr("\n");
	// ft_putstr("flag = ");
	// ft_putnbr(tmp->flag);
	// ft_putstr("\n");
	// ft_putstr("tmp->next : \n");
	// if (tmp->next)
	// {
	// 	ft_puthexa((unsigned long)tmp->next, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("-----------------------------------------------> size = ");
	// 	ft_putnbr(tmp->next->size);
	// 	ft_putstr("\nflag = ");
	// 	ft_putnbr(tmp->next->flag);
	// 	ft_putstr("\n");
	// }
	// }
	return (tmp);
}

t_block	*split_block(t_block *block, size_t size, char src)
{
	t_block *newblock;
	char	*name;

	if (src == 0)
		name = "Malloc ; ";
	else 
		name = "Realloc : ";
	newblock = NULL;
	if (size > MAX_SMALL)
	{
		malloc_debug(SUCCES, name, "Split LARGE block");
		if ((newblock = (t_block*)allocate_with_mmap(size + BLOCK_SIZE, name)) == (void*)-1)
			return (NULL);
		newblock->flag |= FLAG_FREE;
		if (block)
		{
			newblock->next = block->next;
			newblock->prev = block;
			block->next = newblock;
		}
		else
			env.large = newblock;
		return (newblock);
	}
	else if (size <= MAX_TINY || (size > MAX_TINY && block->size - size > BLOCK_SIZE + MAX_TINY))
	{
		ft_putstr("env tiny : \n");
	ft_puthexa((unsigned long)env.tiny, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
		malloc_debug(SUCCES, name, "Split TINY or SMALL block");
		newblock = (void*)block->data + size;
		newblock->size = block->size - size - BLOCK_SIZE;
		newblock->flag |= FLAG_FREE;
		block->size = size;
		newblock->next = block->next;
		block->next = newblock;
		newblock->prev = block;
		ft_putstr("*********** newblock : \n");
	ft_puthexa((unsigned long)newblock, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(newblock->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(newblock->flag);
	ft_putstr(" *******************\n");
	ft_putstr("env tiny : \n");
	ft_puthexa((unsigned long)env.tiny, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
	}
	else
	{
		block->flag |= FLAG_CANT_SPLIT;
		// ft_putstr("flag split = ");
		// ft_putnbr(IS_CANT_SPLIT(block));
		// ft_putstr("\n|||||||||||||||||\n");
		// ft_putstr("size = ");
		// ft_putnbr(size);
		// ft_putstr("\nblock->size = ");
		// ft_putnbr(block->size);
		// ft_putstr("\n|||||||||||||||||\n");
		malloc_debug(SUCCES, name, "No enough place to split");
	}
	return (block);
}

t_block	*fill_block(t_block *block, size_t size)
{
	if (block)
	{
	ft_putstr("FILLLLLLLLLLLLLL block : \n");
	ft_puthexa((unsigned long)block, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(block->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(block->flag);
	ft_putstr(" ENDDDDDDDDDDDDDDD\n");
	}
	if (size <= MAX_SMALL && (!IS_FREE(block) || block->size < size))
	{
		if (size > MAX_TINY)
		{
			malloc_debug(SUCCES, "Malloc : ", "Allocate new pool of SMALL");
			block->next = allocate_first_block((MAX_SMALL + BLOCK_SIZE) * POOL_SIZE);
		}
		else
		{
			malloc_debug(SUCCES, "Malloc : ", "Allocate new pool of TINY");
			block->next = allocate_first_block((MAX_TINY + BLOCK_SIZE) * POOL_SIZE);
		}
		if (!block->next)
		{
			malloc_debug(ERROR, "Malloc : ", "Allocate new pool failed :(");
			return (NULL);
		}
		block->next->flag |= FLAG_START_HEAP;
		block->next->prev = block;
		block = block->next;
	}
	if (size > MAX_SMALL || block->size - size >= BLOCK_SIZE + 4)
		block = split_block(block, size, 0);
	else
	{
		block->flag |= FLAG_CANT_SPLIT;
		// ft_putstr("flag split ELSE = ");
		// ft_putnbr(IS_CANT_SPLIT(block));
		// ft_putstr("\n{{{{{{{{{{{{{{\n");
		// ft_putstr("size = ");
		// ft_putnbr(size);
		// ft_putstr("\nblock->size = ");
		// ft_putnbr(block->size);
		// ft_putstr("\n}}}}}}}}}}}}}}}}}}}}}}}}}\n");
	}
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

	ft_putstr("\nSTART M size = ");
	ft_putnbr(size);
	ft_putstr("\n");
	ft_putstr("tiny : \n");
	ft_puthexa((unsigned long)env.tiny, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
	// if (env.tiny)
	// {
	// block = env.tiny;
	// ft_puthexa((unsigned long)block, 16, "0123456789ABCDEF");
	// ft_putstr("\n");
	// ft_putstr("size = ");
	// ft_putnbr(block->size);
	// ft_putstr("\n");
	// ft_putstr("flag = ");
	// ft_putnbr(block->flag);
	// ft_putstr("\n");
	// ft_putstr("small : \n");
	// }
	malloc_debug(HEADER, "-- MALLOC --", "");
	// pthread_mutex_lock(&thread_safe.mutex_malloc);
	size = ALIGN4(size);
	ft_putstr("before ALIGN size = ");
	ft_putnbr(size);
	ft_putstr("\n");
	if (!env.tiny && init() == -1)
	{
		malloc_debug(ERROR, "Malloc : ", "Malloc failed : init error");
		return (NULL);
	}
	block = get_block(size);
	if (block)
	{
	ft_putstr("YLOLOOOOOOOOOOOOO block : \n");
	ft_puthexa((unsigned long)block, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(block->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(block->flag);
	ft_putstr(" SWGGGGGGGGGGGGGGG\n");
	}
	block = fill_block(block, size);
	//show_alloc_mem();
	// pthread_mutex_unlock(&thread_safe.mutex_malloc);
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
	ft_puthexa((unsigned long)block, 16, "0123456789 ABCDEF");
	ft_putstr("\n");
	ft_putstr("size = ");
	ft_putnbr(block->size);
	ft_putstr("\n");
	ft_putstr("flag = ");
	ft_putnbr(block->flag);
	ft_putstr("\n");
	// ft_putstr("block->next : \n");
	// if (block->next)
	// {
	// 	ft_puthexa((unsigned long)block->next, 16, "0123456789ABCDEF");
	// 	ft_putstr("\n");
	// 	ft_putstr("size = \n");
	// 	ft_putstr("wtf ----------------------------------------------------------------------------------------------------------------------------------> ");
	// 	ft_putnbr(block->next->size);
	// 	ft_putstr("\nflag = ");
	// 	ft_putnbr(block->next->flag);
	// 	ft_putstr("\n");
	// }
	if (block)
	{
		malloc_debug(SUCCES, "Malloc : ", "Malloc succes !");
		return (block->data);
	}
	malloc_debug(ERROR, "Malloc : ", "Malloc failed : block null");
	return (block);
}