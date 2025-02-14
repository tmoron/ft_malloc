/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:38:01 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/14 18:16:06 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <fcntl.h>
# include "libft.h"

# define PAGE_SIZE sysconf(_SC_PAGESIZE)

# define TINY_MALLOC 256 
# define SMALL_MALLOC 4096 

# define TINY_CHUNK_SIZE align(((16 + TINY_MALLOC) * 100) + 32, PAGE_SIZE)
# define SMALL_CHUNK_SIZE align(((16 + SMALL_MALLOC) * 100) + 32, PAGE_SIZE)

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
	t_alloc		*large;

	short		log_level;
	int			fd;
}	t_allocations;

typedef struct t_settings
{
	uint8_t	debug_level:2;
	uint8_t	show_leaks:1;
	uint8_t	initialized:1;
}	t_settings; //size 1

typedef unsigned long	t_ul;

extern t_allocations	g_allocs;
extern pthread_mutex_t	g_mallock;

size_t		align(size_t nb, size_t align_nb);
size_t		show_pre_allocated(char *type, t_mem_chunk *chunk, int dump);
size_t		show_large(int dump);
void		put_ulnbr_base(t_ul nbr, char *base);
void		hex_dump(char *addr, size_t nb);

void		*malloc(size_t size);
t_settings	*get_settings(void);
void		show_alloc_mem(void);
void		free(void *ptr);
void		*realloc(void *ptr, size_t size);
void		log_str(char *str, int level, int print_level, int nl);
void		log_ul(unsigned long nb, int level, int print_level, int nl);

#endif
