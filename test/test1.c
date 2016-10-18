// #include <stdlib.h>
#include "../includes/malloc.h"
#include <unistd.h>

int main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		write(1, "test\n", 5);
		addr[0] = 42;
		i++;
	}
	return (0);
}