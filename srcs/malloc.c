/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:19:59 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/02 19:54:00 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

t_allocations	g_allocs;

void	*get_memory(size_t size, int no_write)
{
	t_mem_chunk	*chunk;

	chunk = mmap(0, size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE,
			-1, 0);
	if (chunk == MAP_FAILED)
		return (0);
	if(no_write)
		return(chunk);
	chunk->space_left = size - sizeof(t_mem_chunk);
	chunk->next = 0;
	return (chunk);
}

t_alloc	*reserve_addr(t_alloc *addr, size_t size, t_alloc *prev,
		t_mem_chunk *chunk)
{
	t_alloc	*tmp;

	if ((t_ul)addr % 16)
		addr = (t_alloc *)((char *)addr + (16 - ((t_ul)addr % 16)));
	addr->size = size;
	chunk->space_left -= (size + sizeof(t_alloc));
	if (prev)
	{
		tmp = prev->next;
		prev->next = addr;
		addr->next = tmp;
	}
	else
		addr->next = 0;
	return (addr + 1);
}

t_alloc	*get_suitable_addr_in_chunk(t_mem_chunk *chunk, size_t size)
{
	t_alloc	*tmp;
	size_t	space_left;
	size_t	free_space;

	tmp = chunk->first;
	space_left = chunk->space_left;
	if((t_ul)chunk->first - (t_ul)(chunk + 1) >= size + sizeof(t_alloc))
	{
		tmp = chunk->first;
		chunk->first = reserve_addr((void *)(chunk + 1), size, 0, chunk) - 1;
		chunk->first->next = tmp;
		return(chunk->first + 1);
	}
	while (tmp->next)
	{
		free_space = ((t_ul)tmp->next - (t_ul)tmp) - (tmp->size + sizeof(t_alloc));
		if (free_space >= size + sizeof(t_alloc))
			return (reserve_addr(
					(void *)((char *)tmp + tmp->size + sizeof(t_alloc)),
				size, tmp, chunk));
		space_left -= free_space;
		tmp = tmp->next;
	}
	if (space_left >= size + sizeof(t_alloc))
		return (reserve_addr(
				(t_alloc *)((char *)tmp + tmp->size + sizeof(t_alloc)),
			size, tmp, chunk));
	return (0);
}

t_mem_chunk	*create_new_chunk(int is_small, t_mem_chunk **chunk, t_mem_chunk *prev)
{
	t_mem_chunk	*new;
	size_t		mmap_size;

	if (is_small)
		mmap_size = SMALL_CHUNK_SIZE;
	else
		mmap_size = TINY_CHUNK_SIZE;
	new = get_memory(mmap_size, 0);
	if (!new)
		return (0);
	new->first = (t_alloc *)(new + 1);
	if (prev)
		prev->next = new;
	if (!*chunk)
		*chunk = new;
	return (new);
}

void	*pre_allocated(size_t size, t_mem_chunk **chunk, int is_small)
{
	t_mem_chunk	*tmp;
	t_mem_chunk	*prev;
	t_alloc		*res;

	tmp = *chunk;
	prev = *chunk;
	res = 0;
	while (tmp)
	{
		if (tmp->space_left >= size)
		{
			res = get_suitable_addr_in_chunk(tmp, size);
			if (res)
				return (res);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	tmp = create_new_chunk(is_small, chunk, prev);
	if (!tmp)
		return (0);
	return (reserve_addr((void *)tmp + sizeof(t_mem_chunk), size, 0, tmp));
}

void	*malloc(size_t size)
{
	t_alloc	*new;

	if (size <= TINY_MALLOC)
		return (pre_allocated(size, &(g_allocs.tiny), 0));
	else if (size <= SMALL_MALLOC)
		return (pre_allocated(size, &(g_allocs.small), 1));

	new = get_memory(size + sizeof(t_alloc), 1);
	if (!new)
		return (0);
	new->size = size;
	new->next = g_allocs.large;
	g_allocs.large = new;
	return ((char *)new + sizeof(t_alloc));
}
