/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:19:59 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/01 19:21:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

t_allocations	g_allocs;

void	*get_memory(size_t size, int no_write)
{
	t_mem_bloc	*bloc;

	bloc = mmap(0, size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE,
			-1, 0);
	if (bloc == MAP_FAILED)
		return (0);
	if(no_write)
		return(bloc);
	bloc->space_left = size - sizeof(t_mem_bloc);
	bloc->next = 0;
	return (bloc);
}

t_alloc	*reserve_addr(t_alloc *addr, size_t size, t_alloc *prev,
		t_mem_bloc *bloc)
{
	t_alloc	*tmp;

	if ((t_ul)addr % 16)
		addr = (t_alloc *)((char *)addr + (16 - ((t_ul)addr % 16)));
	addr->size = size;
	bloc->space_left -= (size + sizeof(t_alloc));
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

t_alloc	*get_suitable_addr_in_bloc(t_mem_bloc *bloc, size_t size)
{
	t_alloc	*tmp;
	size_t	space_left;
	size_t	free_space;

	tmp = bloc->first;
	space_left = bloc->space_left;
	if((t_ul)bloc->first - (t_ul)(bloc + 1) >= size + sizeof(t_alloc))
	{
		tmp = bloc->first;
		bloc->first = reserve_addr((void *)(bloc + 1), size, 0, bloc) - 1;
		bloc->first->next = tmp;
		return(bloc->first + 1);
	}
	while (tmp->next)
	{
		free_space = ((t_ul)tmp->next - (t_ul)tmp) - (tmp->size + sizeof(t_alloc));
		if (free_space >= size + sizeof(t_alloc))
			return (reserve_addr(
					(void *)((char *)tmp + tmp->size + sizeof(t_alloc)),
				size, tmp, bloc));
		space_left -= free_space;
		tmp = tmp->next;
	}
	if (space_left >= size + sizeof(t_alloc))
		return (reserve_addr(
				(t_alloc *)((char *)tmp + tmp->size + sizeof(t_alloc)),
			size, tmp, bloc));
	return (0);
}

t_mem_bloc	*create_new_bloc(int is_small, t_mem_bloc **bloc, t_mem_bloc *prev)
{
	t_mem_bloc	*new;
	size_t		mmap_size;

	if (is_small)
		mmap_size = SMALL_BLOC_SIZE;
	else
		mmap_size = TINY_BLOC_SIZE;
	new = get_memory(mmap_size, 0);
	if (!new)
		return (0);
	new->first = (t_alloc *)(new + 1);
	if (prev)
		prev->next = new;
	if (!*bloc)
		*bloc = new;
	return (new);
}

void	*pre_allocated(size_t size, t_mem_bloc **bloc, int is_small)
{
	t_mem_bloc	*tmp;
	t_mem_bloc	*prev;
	t_alloc		*res;

	tmp = *bloc;
	prev = *bloc;
	res = 0;
	while (tmp)
	{
		if (tmp->space_left >= size)
		{
			res = get_suitable_addr_in_bloc(tmp, size);
			if (res)
				return (res);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	tmp = create_new_bloc(is_small, bloc, prev);
	if (!tmp)
		return (0);
	return (reserve_addr((void *)tmp + sizeof(t_mem_bloc), size, 0, tmp));
}

void	*ft_malloc(size_t size)
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
