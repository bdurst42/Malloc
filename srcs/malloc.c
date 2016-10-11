#include "malloc.h"
#include 				<stdio.h>

t_env	env;

void	*allocate_with_mmap(size_t size)
{
	return (mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
}

char	init(void)
{
	if ((env.tiny = (t_block*)allocate_with_mmap(MAX_TINY * POOL_SIZE)) == (void*)-1 ||
	 		(env.small = (t_block*)allocate_with_mmap(MAX_SMALL * POOL_SIZE)) == (void*)-1)
			return (-1);
	env.tiny->free = 1;
	env.tiny->size = MAX_TINY * POOL_SIZE - BLOCK_SIZE;
	env.small->free = 1;
	env.small->size = MAX_SMALL * POOL_SIZE - BLOCK_SIZE;
	env.large = NULL;
	return (0);
}

void	*mallo(size_t size)
{
	(void)size;

	printf("%d\n", (int)env.tiny);
	if (!env.tiny && init() == -1)
		return (NULL);
	printf("%d\n", (int)env.small->size);
	printf("%d\n", (int)env.tiny->next);
	printf("%d\n", (int)env.tiny->prev);
	printf("%d\n", (int)env.tiny->free);
	return (NULL);
}