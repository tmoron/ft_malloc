/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:46:07 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/01 03:16:19 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_mem_bloc *get_alloc_bloc(t_alloc *alloc, t_mem_bloc *first, size_t size)
{
	while(first)
	{
		if((t_ul)alloc >= (t_ul)first && ((t_ul)alloc - (t_ul)(first + 1)) <= size)
			return(first);
		first = first->next;
	}
	return(0);
}

int	get_prev_alloc(t_alloc **alloc, t_alloc **res, t_alloc *cur)
{
	t_alloc *prev;

	if(cur == *alloc)
		return(1);
	prev = 0;
	while(cur)
	{
		if(cur->next == *alloc)
		{
			*res = cur;
			return(1);
		}
		if(cur->next > *alloc && cur <= *alloc && ((t_ul)alloc - (t_ul)cur) <= cur->size)
		{
			*alloc = cur;
			*res = prev;
			return(1);
		}
		prev = cur;
		cur = cur->next;
	}
	return(0);
}

int free_prealloc(t_alloc *alloc, t_mem_bloc **main_bloc, size_t size)
{
	t_mem_bloc *bloc;
	t_alloc *prev;

	bloc = get_alloc_bloc(alloc, *main_bloc, size);
	if(!bloc)
		return(0);
	if(!get_prev_alloc(&alloc, &prev, bloc->first))
		return(1);
	bloc->space_left -= alloc->size + sizeof(t_alloc);
	if(bloc->first == alloc)
		bloc->first = alloc->next;
	else if(prev)
		prev->next = alloc->next;
	if(!bloc->first)
	{
		if(*main_bloc == bloc)
			*main_bloc = bloc->next;
		munmap(bloc, size);
	}
	return(1);
}

void free_large(t_alloc *alloc)
{
	t_alloc *prev;
	
	if(!get_prev_alloc(&alloc, &prev, g_allocs.large))
		return ;
	if(alloc == g_allocs.large)
		g_allocs.large = alloc->next;
	else if(prev)
		prev->next = alloc->next;
	munmap(alloc, alloc->size + sizeof(t_alloc));
}

void ft_free(void *ptr)
{
	t_alloc *alloc;

	alloc = (t_alloc *)ptr - 1;
	if(free_prealloc(alloc, &g_allocs.tiny, TINY_BLOC_SIZE)) 
		return ;
	if(free_prealloc(alloc, &g_allocs.small, SMALL_BLOC_SIZE)) 
		return ;
	free_large(alloc);
}
