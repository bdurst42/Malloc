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
	char	*new;
	size_t	i;

	i = 0;
	malloc_debug(SUCCES, "-- CALLOC --", "");
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
		malloc_debug(SUCCES, "Calloc : ", "Fill allocation");
		// size = ALIGN4(number * size);
		// if (size > MAX_SMALL)
		// {
			// if (size % getpagesize())
				// size = (size / getpagesize() + 1) * getpagesize();
		// }
		// size /= sizeof(new);
		while (i < size * number)
		{
		 	new[i] = 0;
		 	i++;
		}
		// ft_memset(new, 0, size);
	}
	// ft_putnbr((int)new);
	// 	ft_putstr("\n");
	// pthread_mutex_unlock(&thread_safe.mutex_calloc);
	ft_putstr("calloc -> ");
	ft_puthexa((unsigned long)new, 16, "0123456789ABCDEF");
	ft_putstr("\n");
	return (new);
}