/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 01:46:36 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 02:46:07 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	init_infos(t_infos *infos)
{
	infos->tt_used_mem = 0;
	infos->tt_unused_mem = 0;
	infos->tt_structs_mem = 0;
}

static void	print_infos_pool(t_infos *infos, char activate, char *str)
{
	unsigned long tt;

	tt = infos->tt_unused_mem + infos->tt_structs_mem + infos->tt_used_mem;
	if (!activate)
	{
		ft_putstr("\tnb of pools = ");
		ft_putnbr(infos->nb_pools);
		ft_putchar('\n');
	}
	print_info_bytes(str, infos, activate);
	if (tt)
	{
		ft_putstr("\tnb of allocate bytes in ");
		ft_putstr(str);
		if (activate)
			ft_putnbr(infos->nb_pools);
		ft_putstr(" with structs: ");
		ft_putnbr(infos->tt_structs_mem + infos->tt_used_mem);
		ft_putstr(" / ");
		ft_putnbr(tt);
		ft_putstr(" = ");
		ft_putnbr((infos->tt_structs_mem + infos->tt_used_mem) * 100 / tt);
		ft_putstr("%\n\n");
	}
	init_infos(infos);
}

static void	add_to_tt(t_infos *infos_all_pools, t_infos *infos_pool)
{
	infos_all_pools->tt_used_mem += infos_pool->tt_used_mem;
	infos_all_pools->tt_unused_mem += infos_pool->tt_unused_mem;
	infos_all_pools->tt_structs_mem += infos_pool->tt_structs_mem;
}

static void	print_infos(t_block *start, t_infos *infos_all_pools,
						t_infos *infos_pool)
{
	t_block			*block;

	block = start;
	while (block)
	{
		if (IS_START_HEAP(block))
		{
			add_to_tt(infos_all_pools, infos_pool);
			print_infos_pool(infos_pool, 1, "pool ");
			++infos_pool->nb_pools;
		}
		if (!IS_FREE(block))
			infos_pool->tt_used_mem += block->size;
		else
			infos_pool->tt_unused_mem += block->size;
		infos_pool->tt_structs_mem += BLOCK_SIZE;
		block = block->next;
	}
	add_to_tt(infos_all_pools, infos_pool);
	print_infos_pool(infos_pool, 1, "pool ");
	infos_all_pools->nb_pools = infos_pool->nb_pools;
	print_infos_pool(infos_all_pools, 0, "all pools");
}

void		show_alloc_mem_ex(void)
{
	t_infos			infos_all_pools;
	t_infos			infos_pool;

	pthread_mutex_lock(&g_thread_safe.mutex_show_alloc_mem_ex);
	init_infos(&infos_all_pools);
	init_infos(&infos_pool);
	infos_pool.nb_pools = 1;
	ft_putstr("TINY: \n");
	print_infos(g_env.tiny, &infos_all_pools, &infos_pool);
	ft_putstr("SMALL: \n");
	print_infos(g_env.small, &infos_all_pools, &infos_pool);
	pthread_mutex_unlock(&g_thread_safe.mutex_show_alloc_mem_ex);
}
