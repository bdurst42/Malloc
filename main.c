#include "malloc.h"

int main(void)
{
	char *test;
	test = malloc(5);
	test = malloc(1);
	test = malloc(3);
	test = malloc(9);
	free(test);
	test = malloc(183);
	test = malloc(124);
	test = malloc(445);
	test = malloc(23);
	test = malloc(4453);
	test = malloc(5445);
	test = realloc(test, 12);
	test = malloc(2);
	return (0);
}