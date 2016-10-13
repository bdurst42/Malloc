#include "malloc.h"

int main(void)
{
	char *test;
	test = mallo(5);
	test = mallo(1);
	test = mallo(3);
	test = mallo(9);
	free(test);
	test = mallo(183);
	test = mallo(124);
	test = mallo(445);
	test = mallo(23);
	test = mallo(4453);
	test = mallo(5445);
	return (0);
}