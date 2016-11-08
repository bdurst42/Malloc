#include "malloc.h"

void	*calloc(unsigned long number, unsigned long size)
{
	char	*new;
	size_t	i;
	t_block	*block;

	i = 0;
	malloc_debug(HEADER, "-- CALLOC --", "");
	// ft_putstr("size = ");
	// 	ft_putnbr(size);
	// 	ft_putstr("\nnumber = ");
	// 	ft_putnbr(number);
	// 	ft_putstr("\n");
	// pthread_mutex_lock(&thread_safe.mutex_calloc);
	if (!number || !size)
	{
		malloc_debug(ERROR, "Calloc failed : ", "number or size are null");
		// pthread_mutex_unlock(&thread_safe.mutex_calloc);
		return (NULL);
	}
	new = malloc(number * size);
	if (new)
	{
		block = (t_block*)(new - BLOCK_SIZE);
		// ft_putstr("Block->size = ");
		// ft_putnbr(block->size);
		// ft_putstr("\n");
		malloc_debug(SUCCES, "Calloc : ", "Fill allocation");
		// ft_putstr("calloc size -> ");
		// ft_putnbr(size);
		// ft_putstr("\n");
		// size /= `sizeof(new);
		while (i < block->size)
		 	new[i++] = 0;
		malloc_debug(SUCCES, "Calloc : ", "Succes !");
	}
	// pthread_mutex_unlock(&thread_safe.mutex_calloc);
	return (new);
}