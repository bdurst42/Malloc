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
    // char **tab;
    // int i = 0;
    // int rdm;

    // // ft_putnbr((len + 1) * sizeof(char *));
    // // ft_putstr("\n");
    // tab = (char **)malloc(sizeof(char *) * (len + 1));
    // tab[len] = NULL;
    // srand(time(NULL));
    // while (i < len)
    // {
    //     rdm = (rand() % x_max);
    //     tab[i] = (char *)malloc(sizeof(char) * (rdm + 1));
    //      = (t_block*)(tab[i] - BLOCK_SIZE);
    //     if (!tab[i])
    //         ft_putstr("MALLOC RETURN NULL ERROR\n");
    //     tab[i] = ft_memset(tab[i], 'x', rdm);
    //     tab[i][0] -= 32;
    //     tab[i][rdm - 1] = '|';
    //     tab[i][rdm] = '\0';
    //     i++;
    // }
    // /*i = 0;*/
    // i--;
    // // show_alloc_mem();
    // while (i >= 0)
    // {
    //     free(tab[i--]);
    // 	// show_alloc_mem();
    // }
    // free(tab);
    t_block *block;
    char    *tab = NULL;
    int i = -1;
    int rdm;

    while (++i < len)
    {
        rdm = (rand() % x_max + 1);
        tab = realloc(tab, (rdm + 1));
        if (!tab)
        {
            ft_putstr("MALLOC RETURN NULL ERROR\n");
            exit(0);
        }
        tab = ft_memset(tab, 'x', rdm);
        tab[0] -= 32;
        tab[rdm - 1] = '|';
        tab[rdm] = '\0';
        ft_putstr("MEMESET\n");
    }
    free(tab);
    ft_putstr("endd\n");
}

int main(void)
{
    rand_test(100000, 10000);
    show_alloc_mem();
    return (0);
}