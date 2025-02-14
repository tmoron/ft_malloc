/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:03:26 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/14 19:38:12 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

static void hex_dump_show_address(long unsigned addr)
{
	i
}

static void hex_dump_show_line(char *addr, int len)
{
	hex_dump_show_address((long unsigned)addr);
}

void hex_dump(char *addr, size_t nb)
{
	char buf[16];
	size_t cur;
	
	cur = 0;
	while (cur < nb)
	{
		if(cur && !ft_memcmp(buf, addr + cur, 16))
		{
			cur += 16;
			continue;
		}
		ft_memcpy(buf, addr + cur, 16);
		if(nb - cur < 16)
			hex_dump_show_line(addr + cur, nb - cur);
		else
			hex_dump_show_line(addr + cur, 16);
		cur += 16;
	}
}
