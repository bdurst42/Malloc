#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#		include <stdio.h>

# define BLOCK_SIZE 		(3 * sizeof(void *) + sizeof(size_t) + sizeof(int))
# define MAX_TINY			16
# define MAX_SMALL			1024
# define POOL_SIZE			128

# define ERROR			"\033[0;31m"
# define SUCCES			"\033[0;32m"
# define HEADER			"\033[0;34m"
# define END			"\033[0m"

# define FLAG_FREE			(1 << 0)
# define FLAG_START_HEAP	(1 << 1)
# define FLAG_CANT_SPLIT	(1 << 2)

# define IS_FREE(B)			(((B)->flag & FLAG_FREE))
# define IS_START_HEAP(B)	(((B)->flag & FLAG_START_HEAP))
# define IS_CANT_SPLIT(B)	(((B)->flag & FLAG_CANT_SPLIT))
# define ALIGN4(x)			(((((x) -1) >> 2) << 2)+4)

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	struct s_block	*prev;
	void			*ptr;
	int				flag;
	char			data[1];
}					t_block;

typedef struct		s_infos
{
	unsigned long 	total_used_memory;
	unsigned long 	total_unused_memory;
	unsigned long 	total_structs_memory;
	int				nb_pools;
}					t_infos;

typedef struct		s_env
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_env;

typedef struct		s_thread_safe
{
	pthread_mutex_t	mutex_malloc;
	pthread_mutex_t	mutex_calloc;
	pthread_mutex_t	mutex_realloc;
	pthread_mutex_t	mutex_free;
	pthread_mutex_t	mutex_show_alloc_mem;
	pthread_mutex_t	mutex_show_alloc_mem_ex;
}					t_thread_safe;

extern t_env	env;
extern t_thread_safe thread_safe;

void				*malloc(size_t size);
void				*calloc(size_t number, size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *p, size_t size);
t_block				*split_block(t_block *block, size_t size, char src);
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);
void   				ft_putnbr(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void    			ft_puthexa(unsigned long n, size_t nbase, char *base);
void				malloc_debug(char *color, char *fct, char *str);

#endif