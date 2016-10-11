#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <string.h>

# define BLOCK_SIZE 36
# define MAX_TINY		16
# define MAX_SMALL		1024
# define POOL_SIZE	128
# define ALIGN4(x) (((((x) -1) > >2) < <2)+4)

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	struct s_block	*prev;
	void			*ptr;
	int				free;
	char			data[1];
}					t_block;

typedef struct		s_env
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_env;

extern t_env	env;

void				*mallo(size_t size);

#endif