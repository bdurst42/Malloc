#include "malloc.h"

static size_t	ft_unbrlen(unsigned long long nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		i++;
		nb /= base;
	}
	return (i);
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char const *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	write (1, str, i);
}

char		*ft_utoa(unsigned long long n, size_t nbase, char *base)
{
	char				*dst;
	unsigned long long	i;
	unsigned long long	k;

	k = n;
	i = ft_unbrlen(n, nbase);
	dst = malloc(sizeof(char) * (i + 1));
	dst[i] = '\0';
	while ((--i + 1) != 0)
	{
		dst[i] = base[k % nbase];
		k = k / nbase;
	}
	return (dst);
}

void    ft_putnbr(int n)
{
    if (n > 9)
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
    else if (n >= 0)
        ft_putchar(n + '0');
    else if (n == -2147483648)
        ft_putstr("-2147483648");
    else
    {
        ft_putchar('-');
        ft_putnbr(-n);
    }
}