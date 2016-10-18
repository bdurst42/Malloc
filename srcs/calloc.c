#include "malloc.h"

void	*calloc(size_t number, size_t size)
{
	size_t	*new;
	size_t	i;

	i = 0;
	ft_putstr("calloc\n");
	pthread_mutex_lock(&thread_safe.mutex_calloc);
	if (!number || !size)
	{
		pthread_mutex_unlock(&thread_safe.mutex_calloc);
		return (NULL);
	}
	new = malloc(number * size);
	if (new)
	{
		ft_putstr("size = ");
		ft_putnbr(size);
		ft_putstr("\nnumber = ");
		ft_putnbr(number);
		ft_putstr("\nnumber * size = ");
		ft_putnbr(number * size);
		size = ALIGN4(number * size) >> 2;
		ft_putstr("\nsize after = ");
		ft_putnbr(size);
		while (i < size)
			new[i++] = 0;
		ft_putstr("\n i = ");
		ft_putnbr(i);
		ft_putstr("\n");
	}
	pthread_mutex_unlock(&thread_safe.mutex_calloc);
	return (new);
}