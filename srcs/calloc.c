#include "malloc.h"

void	*calloc(size_t number, size_t size)
{
	size_t	*new;
	size_t	i;

	i = 0;
	pthread_mutex_lock(&thread_safe.mutex_calloc);
	if (!number || !size)
	{
		pthread_mutex_unlock(&thread_safe.mutex_calloc);
		return (NULL);
	}
	new = malloc(number * size);
	if (new)
	{
		size = ALIGN4(number * size) << 2;
		while (i < size)
			new[i++] = 0;
	}
	pthread_mutex_unlock(&thread_safe.mutex_calloc);
	return (new);
}