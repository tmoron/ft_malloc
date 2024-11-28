/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:19:59 by tomoron           #+#    #+#             */
/*   Updated: 2024/11/28 20:22:55 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

void *get_memory(size_t size)
{
	void *ptr;
	t_mem_bloc *bloc_info;

	ptr = mmap(0, size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if(ptr == MAP_FAILED)
		return(0);
	bloc_info = ptr;
	bloc_info->first_alloc = 0;
	bloc_info->next = 0;
	return(ptr);
}

void *allocate_memory(size_t size)
{
	(void)size;
	return(0);
}

t_mem_bloc *get_mem_bloc(t_mem_bloc **bloc, size_t size)
{
	t_mem_bloc *tmp;

		
}

void *pre_allocated(size_t size, s_mem_bloc **bloc)
{
	t_mem_bloc *mem_bloc;
	t_alloc new;	

	mem_bloc = get_mem_bloc(bloc, size)
}

void *ft_malloc(size_t size)
{
	static t_allocations allocs;
	
	if(size <= TINY_ALLOC)
		return(pre_allocated(size, &allocs->tiny));
	else if(size <= SMALL_ALLOC)
		return(pre_allocated(size, &allocs->small));
	else
		return(allocate_memory(size));
	
	return(0);
}

#include <stdlib.h>

int main(void)
{
//	void *p1 = malloc(1);
//	void *p2 = malloc(1);
//	void *p3 = malloc(1);
//	(void)p3;
//	printf("%ld\n", p2 - p1);
}
