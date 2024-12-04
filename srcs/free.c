/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:46:07 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/04 18:23:00 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void invalid_pointer(char *fnc)
{
	(void)fnc;
	write(2, fnc, ft_strlen(fnc));
	write(2, "(): invalid pointer\n", 21);
}

t_mem_chunk	*get_alloc_chunk(t_alloc *alloc, t_mem_chunk *first, int is_small)
{
	size_t	size;

	if (is_small)
		size = SMALL_CHUNK_SIZE;
	else
		size = TINY_CHUNK_SIZE;
	while (first)
	{
		if ((t_ul)alloc >= (t_ul)first && ((t_ul)alloc - \
				(t_ul)(first + 1)) <= size)
			return (first);
		first = first->next;
	}
	return (0);
}

int	get_prev_alloc(t_alloc **alloc, t_alloc **res, t_alloc *cur, char *fnc)
{
	t_alloc	*prev;

	*res = 0;
	if (cur == *alloc)
		return (1);
	prev = 0;
	while (cur)
	{
		if (cur->next == *alloc)
		{
			*res = cur;
			return (1);
		}
		if ((cur->next > *alloc || cur->next == 0) && cur <= *alloc && ((t_ul)*alloc - \
				(t_ul)cur) <= cur->size)
		{
			*alloc = cur;
			*res = prev;
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	invalid_pointer(fnc);
	return (0);
}

static int	free_prealloc(t_alloc *alloc, t_mem_chunk **main_chunk, \
	int is_small)
{
	t_mem_chunk	*chunk;
	t_alloc		*prev;
	size_t		size;

	chunk = get_alloc_chunk(alloc, *main_chunk, is_small);
	if (!chunk)
		return (0);
	if (!get_prev_alloc(&alloc, &prev, chunk->first, "free"))
		return (1);
	chunk->space_left -= alloc->size + sizeof(t_alloc);
	if (chunk->first == alloc)
		chunk->first = alloc->next;
	else if (prev)
		prev->next = alloc->next;
	if (!chunk->first)
	{
		if (*main_chunk == chunk)
			*main_chunk = chunk->next;
		if (is_small)
			size = SMALL_CHUNK_SIZE;
		else
			size = TINY_CHUNK_SIZE;
		munmap(chunk, size);
	}
	return (1);
}

static void	free_large(t_alloc *alloc)
{
	t_alloc	*prev;

	if (!get_prev_alloc(&alloc, &prev, g_allocs.large, "free"))
		return ;
	if (alloc == g_allocs.large)
		g_allocs.large = alloc->next;
	else if (prev)
		prev->next = alloc->next;
	munmap(alloc, alloc->size + sizeof(t_alloc));
}

void	free(void *ptr)
{
	t_alloc	*alloc;

	if (!ptr)
		return ;
	alloc = (t_alloc *)ptr - 1;
	if (free_prealloc(alloc, &g_allocs.tiny, 0))
		return ;
	if (free_prealloc(alloc, &g_allocs.small, 1))
		return ;
	free_large(alloc);
}
