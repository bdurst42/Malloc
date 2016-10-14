#include "malloc.h"

static void display_mem_of_block(void *data, size_t size)
{
	ft_putstr(ft_utoa(data, 16));
	ft_putstr(" - ");
	ft_putstr(ft_utoa(data + size, 16, "0123456789abcdef"));
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

static void	foreach_block(t_block *start, char *str, unsigned long *total)
{
	t_block			*block;

	ft_putstr(str);
	ft_putstr(ft_utoa(start, 16));
	ft_putchar("\n");
	block = start;
	while (block)
	{
		if (!IS_FREE(block))
		{
			display_mem_of_block(block->data, block->size);
			*total += block->size;
		}
		block = block->next;
	}
}

void show_alloc_mem(void)
{
	unsigned long	total;

	total = 0;
	foreach_block(env.tiny, "TINY: ", &total);
	foreach_block(env.small, "SMALL: ", &total);
	foreach_block(env.large, "LARGE: ", &total);
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putchar("\n");
}