/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:38:01 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/01 03:08:41 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft.h"

# define PAGE_SIZE sysconf(_SC_PAGESIZE)

# define TINY_BLOC_SIZE (PAGE_SIZE * 4)
# define SMALL_BLOC_SIZE 524288

# define TINY_MALLOC 1024
# define SMALL_MALLOC 4096

typedef struct s_alloc
{
	size_t			size; //8
	struct s_alloc	*next; //8
}	t_alloc; //size 16

typedef struct s_mem_bloc
{
	size_t				space_left; //8
	struct s_mem_bloc	*next; //8
	t_alloc				*first; //8
	char				padding[8];
}	t_mem_bloc; //size 32

typedef struct s_allocations
{
	t_mem_bloc	*tiny;
	t_mem_bloc	*small;
	t_alloc	*large;
}	t_allocations;

typedef unsigned long t_ul;

extern t_allocations	g_allocs;

void	*ft_malloc(size_t size);
void	show_alloc_mem();
void	ft_free(void *ptr);

#endif
