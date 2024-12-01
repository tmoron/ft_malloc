#include "srcs/includes/malloc.h"
#include <stdio.h>

int main(void)
{
	void *ptr;

	ft_malloc(1013);
	printf("%p\n",ft_malloc(100));
	ft_malloc(100);
	ptr = ft_malloc(1000);
	ft_malloc(100);
	ft_malloc(100);
	ft_free(ptr);
	ft_malloc(123);
	show_alloc_mem();
}
