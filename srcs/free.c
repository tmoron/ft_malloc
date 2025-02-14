/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:46:07 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/14 17:20:17 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	invalid_pointer(char *fnc);

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
			*res = cur;
		if ((cur->next > *alloc || cur->next == 0) && cur <= *alloc && \
				((t_ul)(*alloc) - (t_ul)cur) <= cur->size)
		{
			log_str("invalid pointer but address is known", 2, 1, 1);
			*alloc = cur;
			*res = prev;
		}
		if (*res)
			return (1);
		prev = cur;
		cur = cur->next;
	}
	log_str("invalid pointer inside of a chunk", 3, 1, 1);
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
	log_str("free pointer chunk found", 3, 1, 1);
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
	{
		log_str("unknown pointer given", 1, 1, 1);
		return ;
	}
	if (alloc == g_allocs.large)
		g_allocs.large = alloc->next;
	else if (prev)
		prev->next = alloc->next;
	log_str("munmap called with size ", 3, 1, 0);
	log_ul(alloc->size + sizeof(t_alloc), 3, 0, 1);
	munmap(alloc, alloc->size + sizeof(t_alloc));
	log_str("free sucessfull", 3, 1, 1);
}

void	free(void *ptr)
{
	t_alloc	*alloc;

	log_str("free function called", 3, 1, 1);
	if (!ptr)
		return ;
	alloc = (t_alloc *)ptr - 1;
	pthread_mutex_lock(&g_mallock);
	if (free_prealloc(alloc, &g_allocs.tiny, 0))
		log_str("free successful", 3, 1, 1);
	else if (free_prealloc(alloc, &g_allocs.small, 1))
		log_str("free successful", 3, 1, 1);
	else
		free_large(alloc);
	pthread_mutex_unlock(&g_mallock);
}
