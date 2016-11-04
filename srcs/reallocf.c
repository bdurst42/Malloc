#include "malloc.h"

void *reallocf(void *p, size_t size)
{
	void *newp;

	malloc_debug(HEADER, "-- FREE --", "");
	newp = realloc(p, size);
	free(p);
	return (newp);
}