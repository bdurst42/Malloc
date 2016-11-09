/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 01:45:00 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 01:45:47 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	display_mem_of_block(void *data, size_t size)
{
	ft_putstr("0x");
	ft_puthexa((unsigned long)data, 16, "0123456789ABCDEF");
	ft_putstr(" - 0x");
	ft_puthexa((unsigned long)data + size, 16, "0123456789ABCDEF");
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

static void	foreach_block(t_block *start, char *str, unsigned long *total)
{
	t_block			*block;

	ft_putstr(str);
	ft_putstr(": 0x");
	ft_puthexa((unsigned long)start, 16, "0123456789ABCDEF");
	ft_putchar('\n');
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

void		show_alloc_mem(void)
{
	unsigned long	total;

	total = 0;
	pthread_mutex_lock(&g_thread_safe.mutex_show_alloc_mem);
	foreach_block(g_env.tiny, "TINY", &total);
	foreach_block(g_env.small, "SMALL", &total);
	foreach_block(g_env.large, "LARGE", &total);
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putchar('\n');
	pthread_mutex_unlock(&g_thread_safe.mutex_show_alloc_mem);
}
