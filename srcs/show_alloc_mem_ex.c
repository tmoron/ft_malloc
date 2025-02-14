/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:26:41 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/14 17:48:53 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void show_alloc_mem_ex(void)
{
	size_t	total;

	total = 0;
	pthread_mutex_lock(&g_mallock);
	total += show_pre_allocated("TINY", g_allocs.tiny, 1);
	total += show_pre_allocated("SMALL", g_allocs.small, 1);
	total += show_large(1);
	pthread_mutex_unlock(&g_mallock);
	write(1, "Total : ", 8);
	put_ulnbr_base(total, "0123456789");
	write(1, " bytes\n", 7);
}
