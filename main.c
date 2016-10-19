#include "malloc.h"

int main(void)
{
	t_block *block;
	void	*test;

	test = malloc(5);
	ft_putstr("size after = 5\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(1);
	ft_putstr("size after = 1\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(3);
	ft_putstr("size after = 3\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(9);
	ft_putstr("size after = 9\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	ft_putstr("WESHHHH\n");
	test = malloc(183);
	ft_putstr("size after = 183\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(124);
	ft_putstr("size after = 124\n");
	block = (t_block*)((test - BLOCK_SIZE));
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(445);
	ft_putstr("size after = 445\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(23);
	ft_putstr("size after = 23\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(4453);
	ft_putstr("size after = 4453\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(5445);
	ft_putstr("size after = 5445\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = realloc(test, 12);
	ft_putstr("size after = 12\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	test = malloc(2);
	ft_putstr("size after = 2\n");
	block = (t_block*)(test - BLOCK_SIZE);
	ft_putstr("size before = ");
	ft_putnbr((int)block->size);
	ft_putstr("\n");
	free(test);
	return (0);
}