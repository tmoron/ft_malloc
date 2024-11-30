/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:19:34 by tomoron           #+#    #+#             */
/*   Updated: 2024/11/30 15:50:14 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void put_ulnbr_base(unsigned long nbr, char *base)
{
	unsigned long base_len;	

	base_len = ft_strlen(base);
	if(nbr >= base_len)
	{
		put_ulnbr_base(nbr / base_len, base);
		write(1, base + (nbr % base_len), 1);
	}
	else
		write(1, base + nbr, 1);
}

size_t show_allocs(t_alloc *alloc)
{
	size_t nb_bytes;
	
	nb_bytes = 0;
	while(alloc)
	{
		nb_bytes += alloc->size;
		write(1, "0x", 2);
		put_ulnbr_base((unsigned long)alloc + sizeof(t_alloc), "0123456789ABCDEF");
		write(1, " - 0x", 5);
		put_ulnbr_base((unsigned long)alloc +sizeof(t_alloc) + alloc->size, "0123456789ABCDEF");
		write(1, " : ", 3);
		put_ulnbr_base(alloc->size, "0123456789");
		write(1, " bytes\n", 7);
		alloc = alloc->next;
	}
	return(nb_bytes);
}

size_t show_pre_allocated(char *type, t_mem_bloc *bloc)
{
	size_t nb_bytes;

	nb_bytes = 0;
	while(bloc)
	{
		write(1, type, ft_strlen(type));
		write(1, " : 0x", 5);
		put_ulnbr_base((unsigned long)bloc, "0123456789ABCDEF");
		write(1, "\n", 1);
		nb_bytes += show_allocs((t_alloc *)(bloc + 1));
		bloc = bloc->next;
	}
	return(nb_bytes);
}

size_t show_large()
{
	t_mem_bloc *bloc;
	size_t total_size;

	bloc = g_allocs.large;
	total_size = 0;
	while(bloc)	
	{
		write(1, "LARGE : 0x", 10);
		put_ulnbr_base((unsigned long)bloc, "0123456789ABCDEF");
		write(1,"\n", 1);
		write(1, "0x", 2);
		put_ulnbr_base((unsigned long)(bloc + 1), "0123456789ABCDEF");
		write(1, " - 0x", 5);
		put_ulnbr_base((unsigned long)(bloc + 1) + bloc->space_left, "0123456789ABCDEF");
		write(1, " : ", 3);
		put_ulnbr_base(bloc->space_left, "0123456789");
		write(1, " bytes\n", 7);
		total_size += bloc->space_left;
		bloc = bloc->next;
	}
	return(total_size);
}

void show_alloc_mem()
{
	size_t total;

	total = 0;
	total += show_pre_allocated("TINY", g_allocs.tiny);
	total += show_pre_allocated("SMALL", g_allocs.small);
	total += show_large();
	write(1, "Total : ", 8);
	put_ulnbr_base(total, "0123456789");
	write(1, " bytes\n", 6);
}
