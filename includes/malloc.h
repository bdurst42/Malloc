#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#		include <stdio.h>

# define BLOCK_SIZE 		(3 * sizeof(void *) + sizeof(size_t) + sizeof(int))
# define MAX_TINY			16
# define MAX_SMALL			1024
# define POOL_SIZE			128
# define FLAG_FREE			(1 << 0)
# define FLAG_START_HEAP	(1 << 1)
# define IS_FREE(B)			(((B)->flag & FLAG_FREE))
# define IS_START_HEAP(B)	(((B)->flag & FLAG_START_HEAP))
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

typedef struct		s_env
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_env;

extern t_env	env;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
t_block				*split_block(t_block *block, size_t size);
void				show_alloc_mem(void);

#endif