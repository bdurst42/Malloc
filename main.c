#include "malloc.h"


void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	if (!b)
		return (NULL);
	s = b;
	// ft_putstr("before\n");
	while (len > 0)
	{
		*s = c;
		s++;
        // ft_putnbr(len);
	// ft_putstr("\n");
		len--;
	}
	return (b);
}


void rand_test(int len, int x_max)
{
    char **tab;
    int i = 0;
    int rdm;

    // ft_putnbr((len + 1) * sizeof(char *));
    // ft_putstr("\n");
    tab = (char **)malloc(sizeof(char *) * (len + 1));
    tab[len] = NULL;
    srand(time(NULL));
    while (i < len)
    {
        rdm = (rand() % x_max);
        tab[i] = (char *)malloc(sizeof(char) * (rdm + 1));
        if (!tab[i])
            ft_putstr("MALLOC RETURN NULL ERROR\n");
        tab[i] = ft_memset(tab[i], 'x', rdm);
        tab[i][0] -= 32;
        tab[i][rdm - 1] = '|';
        tab[i][rdm] = '\0';
        i++;
    }
    // show_alloc_mem_ex();
    /*i = 0;*/
    i--;
    // show_alloc_mem();
    while (i >= 0)
    {
        free(tab[i--]);
    	// show_alloc_mem();
    }
    free(tab);
    // t_block *block;
    // char    *tab = NULL;
    // int i = -1;
    // int rdm;
    // int rdm2;

    // while (++i < len)
    // {
    //     rdm = (rand() % x_max) + 1;
    //     rdm2 = (rand() % x_max) + 1;
    //    tab = calloc(rdm2, rdm);
    //     if (!tab)
    //     {
    //         ft_putstr("MALLOC RETURN NULL ERROR\n");
    //         exit(0);
    //     }
    //     int j = 0;
    //     while (tab[j])
    //         ++j;
    //     // show_alloc_mem();  
    // free(tab);
    // }

    // ft_putstr("block : \n");
    // ft_puthexa((unsigned long)block->data, 16, "0123456789 ABCDEF");
    // ft_putstr("\n");
    // ft_putstr("size = ");
    // ft_putnbr(block->size);
    // ft_putstr("\n");
    // ft_putstr("flag = ");
    // ft_putnbr(block->flag);
    // ft_putstr("\n");
}

void test(void)
{
    t_block block;

    block.flag |= FLAG_CANT_SPLIT;
    ft_putnbr(IS_CANT_SPLIT(&block));
    ft_putstr("\n");
    block.flag &= (0 << 2);
    ft_putnbr(IS_CANT_SPLIT(&block));
    ft_putstr("\n");

}

int main(void)
{
   rand_test(100000, 10000);
    show_alloc_mem();
    // test();
    return (0);
}
