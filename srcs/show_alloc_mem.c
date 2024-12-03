/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:19:34 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/03 18:50:25 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

static void	put_ulnbr_base(t_ul nbr, char *base)
{
	t_ul	base_len;	

	base_len = ft_strlen(base);
	if (nbr >= base_len)
	{
		put_ulnbr_base(nbr / base_len, base);
		write(1, base + (nbr % base_len), 1);
	}
	else
		write(1, base + nbr, 1);
}

static size_t	show_allocs(t_alloc *alloc)
{
	size_t	nb_bytes;

	nb_bytes = 0;
	while (alloc)
	{
		nb_bytes += alloc->size;
		write(1, "0x", 2);
		put_ulnbr_base((t_ul)alloc + sizeof(t_alloc), "0123456789ABCDEF");
		write(1, " - 0x", 5);
		put_ulnbr_base((t_ul)alloc + sizeof(t_alloc) + alloc->size, \
			"0123456789ABCDEF");
		write(1, " : ", 3);
		put_ulnbr_base(alloc->size, "0123456789");
		write(1, " bytes\n", 7);
		alloc = alloc->next;
	}
	return (nb_bytes);
}

static size_t	show_pre_allocated(char *type, t_mem_chunk *chunk)
{
	size_t	nb_bytes;

	nb_bytes = 0;
	while (chunk)
	{
		write(1, type, ft_strlen(type));
		write(1, " : 0x", 5);
		put_ulnbr_base((t_ul)chunk, "0123456789ABCDEF");
		write(1, "\n", 1);
		nb_bytes += show_allocs(chunk->first);
		chunk = chunk->next;
	}
	return (nb_bytes);
}

static size_t	show_large(void)
{
	t_alloc	*alloc;
	size_t	total_size;

	alloc = g_allocs.large;
	total_size = 0;
	while (alloc)
	{
		write(1, "LARGE : 0x", 10);
		put_ulnbr_base((t_ul)alloc, "0123456789ABCDEF");
		write(1, "\n", 1);
		write(1, "0x", 2);
		put_ulnbr_base((t_ul)(alloc + 1), "0123456789ABCDEF");
		write(1, " - 0x", 5);
		put_ulnbr_base((t_ul)(alloc + 1) + alloc->size, "0123456789ABCDEF");
		write(1, " : ", 3);
		put_ulnbr_base(alloc->size, "0123456789");
		write(1, " bytes\n", 7);
		total_size += alloc->size;
		alloc = alloc->next;
	}
	return (total_size);
}

void	show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	total += show_pre_allocated("TINY", g_allocs.tiny);
	total += show_pre_allocated("SMALL", g_allocs.small);
	total += show_large();
	write(1, "Total : ", 8);
	put_ulnbr_base(total, "0123456789");
	write(1, " bytes\n", 7);
}
