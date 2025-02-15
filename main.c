/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:19:23 by tomoron           #+#    #+#             */
/*   Updated: 2025/02/15 15:00:37 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/malloc.h"
#include <stdio.h>

int	main(void)
{
	void	*ptr;

	printf("%zu\n", SMALL_CHUNK_SIZE);
	ptr = malloc(1203);
	show_alloc_mem();
	ptr = realloc(ptr, 12045);
	show_alloc_mem_ex();
}
