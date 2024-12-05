#include "srcs/includes/malloc.h"
#include <stdio.h>

int main(void)
{
	void *ptr;

	printf("%zu\n", SMALL_CHUNK_SIZE);
	ptr = malloc(1203);
	show_alloc_mem();
	ptr = realloc(ptr, 12045);
	show_alloc_mem();
	free(ptr);
	show_alloc_mem();
}
