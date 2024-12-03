/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:20:54 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/03 13:23:31 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

size_t	align(size_t nb, size_t align_nb)
{
	if (nb % align_nb)
		nb = nb + (align_nb - (nb % align_nb));
	return (nb);
}
