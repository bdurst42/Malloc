#include "malloc.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	if (!b)
		return (NULL);
	s = b;
	while (len > 0)
	{
		*s = c;
		s++;
		len--;
	}
	return (b);
}

void	*calloc(size_t number, size_t size)
{
	size_t	*new;
	size_t	i;

	i = 0;
	malloc_debug(SUCCES, "-- CALLOC --", "");
	pthread_mutex_lock(&thread_safe.mutex_calloc);
	if (!number || !size)
	{
		malloc_debug(ERROR, "Calloc failed : ", "number or size are null");
		pthread_mutex_unlock(&thread_safe.mutex_calloc);
		return (NULL);
	}
	new = malloc(number * size);
	if (new)
	{
		malloc_debug(SUCCES, "Calloc : ", "Fill allocation");
		ft_putstr("size = ");
		ft_putnbr(size);
		ft_putstr("\nnumber = ");
		ft_putnbr(number);
		ft_putstr("\nnumber * size = ");
		ft_putnbr(number * size);
		size = ALIGN4(number * size);
		if (size % getpagesize())
			size = (size / getpagesize() + 1) * getpagesize();
		ft_putstr("\nsize after = ");
		ft_putnbr(size);
		while (i < size * number)
		{
		 	new[i] = 0;
		 	i++;
		}
		// ft_putstr("\n i = ");
		// ft_putnbr(i);
		ft_putstr("\n");
		// ft_memset(new, 0, size);
	}
	ft_putnbr((int)new);
		ft_putstr("\n");
	pthread_mutex_unlock(&thread_safe.mutex_calloc);
	return (new);
}