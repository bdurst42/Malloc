/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 01:32:02 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/30 01:55:12 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

# define BLOCK_SIZE 		sizeof(t_block)
# define MAX_TINY			32
# define MAX_SMALL			1024
# define PSZ				128

# define ERROR				"\033[0;31m"
# define SUCCES				"\033[0;32m"
# define HEADER				"\033[0;34m"
# define END				"\033[0m"

# define FLAG_FREE			(1 << 0)
# define FLAG_START_HEAP	(1 << 1)
# define FLAG_CANT_SPLIT	(1 << 2)

# define IS_FREE(B)			(((B)->flag & FLAG_FREE))
# define IS_START_HEAP(B)	(((B)->flag & FLAG_START_HEAP))
# define IS_CANT_SPLIT(B)	(((B)->flag & FLAG_CANT_SPLIT))
# define ALIGN4(x)			(((((x) -1) >> 2) << 2)+4)
# define U(x)				use_block(x, b)
# define EXIST_BLOCK		U(g_env.tiny) || U(g_env.small) || U(g_env.large)

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	struct s_block	*prev;
	int				flag;
}					t_block;

typedef struct		s_infos
{
	unsigned long	tt_used_mem;
	unsigned long	tt_unused_mem;
	unsigned long	tt_structs_mem;
	int				nb_pools;
}					t_infos;

typedef struct		s_g_env
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_env;

typedef struct		s_g_thread_safe
{
	pthread_mutex_t	mutex_malloc;
	pthread_mutex_t	mutex_calloc;
	pthread_mutex_t	mutex_realloc;
	pthread_mutex_t	mutex_free;
	pthread_mutex_t	mutex_show_alloc_mem;
	pthread_mutex_t	mutex_show_alloc_mem_ex;
}					t_thread_safe;

t_env					g_env;
extern	t_thread_safe	g_thread_safe;

void				*malloc(size_t size);
void				*calloc(size_t number, size_t size);
char				use_block(t_block *start, t_block *block);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *p, size_t size);
void				*valloc(size_t size);
t_block				*split_block(t_block *block, size_t size, char src);
t_block				*fill_block(t_block *b, size_t size);
t_block				*allocate_first_block(size_t size);
t_block				*allocate_with_mmap(size_t size, char *name);
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);
void				ft_putnbr(long n);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_puthexa(unsigned long n, size_t nbase, char *base);
void				malloc_debug(char *color, char *fct, char *str);
void				*unlock_fct_with_return(void *ptr, pthread_mutex_t *mutex);
void				print_info_bytes(char *str, t_infos *infos, char activate);

#endif
