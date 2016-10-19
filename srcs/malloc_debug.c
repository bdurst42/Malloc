#include "malloc.h"

void	malloc_debug(char *color, char *fct, char *str)
{
	if (getenv("MALLOC_DEBUG"))
	{
		ft_putstr("[DEBUG] -> ");
		ft_putstr(color);
		ft_putstr(fct);
		ft_putstr(END);
		ft_putstr(str);
		ft_putchar('\n');
	}
}