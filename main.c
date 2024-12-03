#include "srcs/includes/malloc.h"
#include <stdio.h>

int main(void)
{
	int i;
	
	i = 0;
	while(i < 110)
	{
		malloc(256);
		i++;
	}
	show_alloc_mem();

}
