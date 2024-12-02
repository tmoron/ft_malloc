/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:38:01 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/02 20:18:33 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft.h"

# define PAGE_SIZE sysconf(_SC_PAGESIZE)


# define TINY_MALLOC 1024
# define SMALL_MALLOC 4096

# define TINY_CHUNK_SIZE (((16 + TINY_MALLOC) * 100) + 32)
# define SMALL_CHUNK_SIZE 524288

typedef struct s_alloc
{
	size_t			size; //8
	struct s_alloc	*next; //8
}	t_alloc; //size 16

typedef struct s_mem_chunk
{
	size_t				space_left; //8
	struct s_mem_chunk	*next; //8
	t_alloc				*first; //8
	char				padding[8];
}	t_mem_chunk; //size 32

typedef struct s_allocations
{
	t_mem_chunk	*tiny;
	t_mem_chunk	*small;
	t_alloc	*large;
}	t_allocations;

typedef unsigned long t_ul;

extern t_allocations	g_allocs;

void	*malloc(size_t size);
void	show_alloc_mem();
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

#endif
