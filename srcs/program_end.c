/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:11:27 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/14 17:24:02 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void __attribute__((destructor))	malloc_end(void)
{
	if (get_settings()->show_leaks)
	{
		ft_putstr_fd("\n\033[31m\033[1mMALLOC_SHOW_LEAKS is defined, here is \
the leak report\n", 1);
		show_alloc_mem();
		ft_putstr_fd("\033[0m", 1);
	}
}
