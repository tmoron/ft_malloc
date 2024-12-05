/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:20:54 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/04 18:52:46 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

size_t	align(size_t nb, size_t align_nb)
{
	if (nb % align_nb)
		nb = nb + (align_nb - (nb % align_nb));
	return (nb);
}

void	invalid_pointer(char *fnc)
{
	write(2, fnc, ft_strlen(fnc));
	write(2, "(): invalid pointer\n", 21);
}
