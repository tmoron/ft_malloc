/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:03:26 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/15 16:19:00 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"


static void put_hex_padded(t_ul addr, int padding, int prefix)
{
	int		len;
	t_ul	tmp;

	len = 1;
	tmp = addr;
	while (tmp >= 16)
	{
		tmp /= 16;
		len++;
	}
	if(prefix)
		write(1, "0x", 2);
	while(len < padding)
	{
		write(1, "0", 1);
		len++;
	}
	put_ulnbr_base(addr, "0123456789abcdef");
}

static void put_char_dot(char c)
{
	if(c >= 32 && c <= 126)
		write(1, &c, 1);
	else
		write(1, ".", 1);
}

static void hex_dump_show_line(char *addr, int len)
{
	int i;

	put_hex_padded((long unsigned)addr, 16, 1);
	write(1, "  ", 2);
	i = 0;
	while(i < 16)
	{
		if(i < len)
			put_hex_padded(addr[i], 2, 0);
		else
			write(1, "  ", 2);
		write(1, " ", 1);
		if(i == 7 || i == 15)
			write(1, " ", 1);
		i++;
	}
	i = 0;
	write(1, "|", 1);
	while(i < len)
	{
		put_char_dot(addr[i]);
		i++;
	}
	write(1, "|", 1);
	write(1, "\n", 1);
	(void)len;
}

void hex_dump(char *addr, size_t nb)
{
	char buf[16];
	size_t cur;
	int		lst_same;
	
	cur = 0;
	lst_same = 0;
	while (cur + 16 < nb)
	{
		if(cur && !ft_memcmp(buf, addr + cur, 16))
		{
			cur += 16;
			if(!lst_same)	
				write(1, "*\n", 2);
			lst_same = 1;
			continue;
		}
		lst_same = 0;
		ft_memcpy(buf, addr + cur, 16);
		hex_dump_show_line(addr + cur, 16);
		cur += 16;
	}
	if(cur < nb)
		hex_dump_show_line(addr + cur, nb - cur);
	put_hex_padded((long unsigned)addr, 16, 1);
	write(1, "\n", 1);
}
