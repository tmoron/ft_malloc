#include "srcs/includes/malloc.h"
#include <stdio.h>

int main(void)
{
	void *ptr;

	ptr = malloc(1203);
	free(ptr);
}
