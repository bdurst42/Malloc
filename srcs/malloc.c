#include "malloc.h"
#include 				<stdio.h>

t_env	env;

void	*mlc_allocate_with_mmap(size_t size)
{
	return (mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
}

t_block	*allocate_first_block(size_t size)
{
	t_block	*newblock;

	if (size % getpagesize())
		size = size / getpagesize() + getpagesize();
	if ((newblock = (t_block*)mlc_allocate_with_mmap(size)) == (void*)-1)
		return (NULL);
	newblock->flag ^= FLAG_FREE;
	newblock->size = size - BLOCK_SIZE;
	return (newblock);
}

char	mlc_init(void)
{
	if (!(env.tiny = allocate_first_block(MAX_TINY * POOL_SIZE)) ||
	 		!(env.small = allocate_first_block(MAX_SMALL * POOL_SIZE)))
			return (0);
	env.large = NULL;
	return (0);
}

t_block	*mlc_find_block(size_t size)
{
	t_block	*tmp;

	if (size <= MAX_TINY)
		tmp = env.tiny;
	else if (size <= MAX_SMALL)
		tmp = env.small;
	else
		tmp = env.large;
	while (tmp && tmp->next && (size > MAX_SMALL || !IS_FREE(tmp) || tmp->size < size))
		tmp = tmp->next;
	return (tmp);
}

t_block	*mlc_split_block(t_block *block, size_t size)
{
	t_block *newblock;

	if (size > MAX_SMALL)
	{
		if ((newblock = (t_block*)mlc_allocate_with_mmap(size)) == (void*)-1)
			return (NULL);
		newblock->size = size;
		if (block)
		{
			newblock->prev = block;
			block->next = newblock;
		}
		else
		{
			env.large = newblock;
		}
		return (newblock);
	}
	else
	{
		newblock = (void*)block->data + size;
		newblock->size = block->size - size - BLOCK_SIZE;
		newblock->flag ^= FLAG_FREE;
		block->size = size;
	}
	newblock->prev = block;
	block->next = newblock;
	return (block);
}

t_block	*mlc_fill_block(t_block *block, size_t size)
{
	if (size <= MAX_SMALL && (!IS_FREE(block) || block->size < size))
	{
		if (size > MAX_TINY)
			block->next = allocate_first_block(MAX_SMALL * POOL_SIZE);
		else
			block->next = allocate_first_block(MAX_TINY * POOL_SIZE);
		block = block->next;
	}
	if (size > MAX_SMALL || size < block->size)
		block = mlc_split_block(block, size);
	if (block)
	{
		block->ptr = block->data;
		block->flag |= FLAG_FREE;
	}
	return (block);
}

void show_alloc_mem(void)
{
	t_block *block;
	unsigned long total;

	printf("%s%p\n", "TINY: ", env.tiny);
	block = env.tiny;
	total = 0;
	while (block && block->next)
	{
		if (!IS_FREE(block))
		{
			printf("block = %p %p - %p : %lu octets\n", block, block->data, block->data + block->size, block->size);
			total += block->size;
		}
		// printf("%p - %p : %lu octets\n", block->data, block->next, (unsigned long)block->next - (unsigned long)block->data);
		// total += (unsigned long)block->next - (unsigned long)block->data;
		block = block->next;
	}
	printf("%s%p\n",  "SMALL: ", env.small);
	block = env.small;
	while (block && block->next)
	{
		if (!IS_FREE(block))
		{
			printf("%p - %p : %lu octets\n", block->data, block->data + block->size, block->size);
			total += block->size;
		}
		// printf("%p - %p : %lu octets\n", block->data, block->next, (unsigned long)block->next - (unsigned long)block->data);
		// total += (unsigned long)block->next - (unsigned long)block->data;
		block = block->next;
	}
	printf("%s%p\n", "LARGE: ", env.large);
	block = env.large;
	while (block)
	{
		printf("%p - %p : %lu octets\n", block->data, block->data + block->size, block->size);
		total += block->size;
		// printf("%p - %p : %lu octets\n", block->data, block->next, (unsigned long)block->next - (unsigned long)block->data);
		// total += (unsigned long)block->next - (unsigned long)block->data;
		block = block->next;
	}
	printf("Total: %lu\n", total);
}

void	*mallo(size_t size)
{
	t_block *block;

	size = ALIGN4(size);
	if (!env.tiny && mlc_init() == -1)
		return (NULL);
	block = mlc_fill_block(mlc_find_block(size), size);
	show_alloc_mem();
	if (block)
		return (block->data);
	return (block);
}