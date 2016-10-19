#include "malloc.h"

static void		init_infos(t_infos *infos)
{
	infos->total_used_memory = 0;
	infos->total_unused_memory = 36;
	infos->total_structs_memory = 0;
}

static void 	print_infos_pool(t_infos *infos, char activate, char *str)
{
	unsigned long total;

	total = infos->total_unused_memory + infos->total_structs_memory + infos->total_used_memory;
	if (!activate)
	{
		ft_putstr("\tnb of pools = ");
		ft_putnbr(infos->nb_pools);
		ft_putchar('\n');
	}
	ft_putstr("\tnb of allocate bytes in ");
	ft_putstr(str);
	if (activate)
		ft_putnbr(infos->nb_pools);
	ft_putstr(": ");
	ft_putnbr(infos->total_used_memory);
	ft_putchar('\n');
	if (total)
	{
		ft_putstr("\tnb of allocate bytes in ");
		ft_putstr(str);
		if (activate)
			ft_putnbr(infos->nb_pools);
		ft_putstr(" with structs: ");
		ft_putnbr(infos->total_structs_memory + infos->total_used_memory);
		ft_putstr(" / ");
		ft_putnbr(total);
		ft_putstr(" = ");
		ft_putnbr((infos->total_structs_memory + infos->total_used_memory) * 100 / total);
		ft_putstr("%\n\n");
	}
	init_infos(infos);
}

static void 	print_infos(t_block *start)
{
	t_block			*block;
	t_infos			infos_all_pools;
	t_infos			infos_pool;

	init_infos(&infos_all_pools);
	init_infos(&infos_pool);
	infos_pool.nb_pools = 1;
	block = start;
	while (block)
	{
		if (IS_START_HEAP(block))
		{
			print_infos_pool(&infos_pool, 1, "pool ");
			++infos_pool.nb_pools;
		}
		if (!IS_FREE(block))
		{
			infos_all_pools.total_used_memory += block->size;
			infos_all_pools.total_structs_memory += BLOCK_SIZE;
			infos_pool.total_used_memory += block->size;
			infos_pool.total_structs_memory += BLOCK_SIZE;
		}
		else
		{
			infos_pool.total_unused_memory += block->size;
			infos_all_pools.total_unused_memory += block->size;
		}
		block = block->next;
	}
	print_infos_pool(&infos_pool, 1, "pool ");
	infos_all_pools.nb_pools = infos_pool.nb_pools;
	print_infos_pool(&infos_all_pools, 0, "all pools");
}

void	show_alloc_mem_ex(void)
{
	// pthread_mutex_lock(&thread_safe.mutex_show_alloc_mem_ex);
	ft_putstr("TINY: \n");
	print_infos(env.tiny);
	ft_putstr("SMALL: \n");
	print_infos(env.small);
	// pthread_mutex_unlock(&thread_safe.mutex_show_alloc_mem_ex);
}