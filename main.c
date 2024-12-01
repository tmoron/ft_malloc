#include "srcs/includes/malloc.h"

int main(void)
{
	void *ptr;

	ptr = ft_malloc(1013);
	ft_free(ptr);
	show_alloc_mem();
}
