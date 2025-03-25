/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:58:16 by tomoron           #+#    #+#             */
/*   Updated: 2025/03/25 14:20:14 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "srcs/includes/malloc.h"

void malloc_free_test()
{
	void *ptr[3];

	printf("MALLOC TEST (pointers shouldn't be null):\n");
	ptr[0] = malloc(42);
	printf("tiny malloc : %p\n", ptr[0]);
	ptr[1] = malloc(1024);
	printf("small malloc : %p\n", ptr[1]);
	ptr[2] = malloc(16384 * 1024);
	printf("large malloc : %p\n", ptr[2]);

	printf("\n\n\nFREE TEST (1024 bloc is from printf):\n");
	printf("before : \n");
	show_alloc_mem();
	printf("\n");
	free(ptr[0]);
	free(ptr[1]);
	free(ptr[2]);
	printf("after : \n");
	show_alloc_mem();
}


void realloc_test()
{	
	void *ptr[3];

	printf("\n\n\nREALLOC TEST :\n");
	printf("test 1 : the data in the first print should be the same in the second print and the size should be 20 in the show alloc\n");
	ptr[0] = malloc(10);
	strcpy(ptr[0], "potato");
	printf("before realloc : %s\nptr : %p\n", (char *)ptr[0], ptr[0]);

	ptr[0] = realloc(ptr[0], 20);
	printf("after realloc :%s\nptr : %p\n", (char *)ptr[0], ptr[0]);
	show_alloc_mem();

	printf("test 2 : changing chunk size (form 20 to 500), the pointer used is the same as test1\n");
	ptr[0] = realloc(ptr[0], 500);
	printf("after realloc :%s\nptr : %p\n", (char *)ptr[0], ptr[0]);
	show_alloc_mem();

	printf("test 3 : changing chunk size (form 500 to 8192), the pointer used is the same as test2\n");
	ptr[0] = realloc(ptr[0], 8192);
	printf("after realloc :%s\nptr : %p\n", (char *)ptr[0], ptr[0]);
	show_alloc_mem();
	free(ptr[0]);
}

void show_alloc_ex_test()
{
	char *data;

	printf("\n\n\nSHOW_ALLOC_EX TEST:\n");
	data = malloc(1020);
	memset(data, 0, 1020);
	strcpy(data, "0123456789abcdef");
	strcpy(data + 16, "potato");
	data[584] = 'a';
	show_alloc_mem_ex();
	free(data);
}

void defrag_test()
{
	void *ptrs[3];

	printf("\n\n\nDEFRAG_TEST: making two alloc of size 20\n");
	ptrs[0] = malloc(20);
	ptrs[1] = malloc(20);
	show_alloc_mem();
	printf("\nfree allocs\n");
	free(ptrs[0]);
	free(ptrs[1]);
	printf("allocating a new bloc of size 40, address should be the same as first bloc\n");
	ptrs[2] = malloc(40);
	show_alloc_mem();
	if(ptrs[2] == ptrs[0])
		printf("\nallocated bloc has the same address\n");
	else
		printf("\nERROR : allocated bloc doesn't have the same address\n");
	free(ptrs[2]);
}

int main(void)
{
	malloc_free_test();
	realloc_test();
	show_alloc_ex_test();
	defrag_test();

	#if 0
		printf("allocating memory before end of program\n");
		malloc(10);
		malloc(50);
		malloc(8000);
		malloc(1024);
	#endif
}
