/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:44:32 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/10 18:18:45 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	*get_memory(size_t size, int no_write);
t_alloc	*reserve_addr(t_alloc *addr, size_t size, t_alloc *prev,
			t_mem_chunk *chunk);

t_mem_chunk	*create_new_chunk(int is_small, t_mem_chunk **chunk, \
	t_mem_chunk *prev)
{
	t_mem_chunk	*new;
	size_t		mmap_size;

	log_str("no suitable address found in previously allocated chunks, \
creating new chunk", 3, 1, 1);
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

static t_alloc	*get_suitable_addr_in_chunk_middle_end(size_t space_left, \
		t_alloc *tmp, size_t size, t_mem_chunk *chunk)
{
	size_t	free_space;

	while (tmp->next)
	{
		free_space = ((t_ul)tmp->next - (t_ul)tmp) - \
			(tmp->size + sizeof(t_alloc));
		if (free_space >= size + sizeof(t_alloc))
		{
			log_str("suitable address found between two alocations", 3, 1, 1);
			return (reserve_addr(
					(void *)((char *)tmp + tmp->size + sizeof(t_alloc)),
				size, tmp, chunk));
		}
		space_left -= free_space;
		tmp = tmp->next;
	}
	if (space_left >= size + sizeof(t_alloc))
	{
		log_str("suitable address found at the end of a chunk", 3, 1, 1);
		return (reserve_addr(
				(t_alloc *)((char *)tmp + tmp->size + sizeof(t_alloc)),
			size, tmp, chunk));
	}
	return (0);
}

t_alloc	*get_suitable_addr_in_chunk(t_mem_chunk *chunk, size_t size)
{
	t_alloc	*tmp;
	size_t	space_lft;

	tmp = chunk->first;
	space_lft = chunk->space_left;
	if ((t_ul)chunk->first - (t_ul)(chunk + 1) >= size + sizeof(t_alloc))
	{
		tmp = chunk->first;
		chunk->first = reserve_addr((void *)(chunk + 1), size, 0, chunk) - 1;
		chunk->first->next = tmp;
		log_str("suitable address found in the start of an already allocated \
chunk", 3, 1, 1);
		return (chunk->first + 1);
	}
	return (get_suitable_addr_in_chunk_middle_end(space_lft, tmp, size, chunk));
}
