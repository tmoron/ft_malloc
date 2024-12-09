/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:24:29 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/09 17:24:33 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putulnbr_fd(unsigned long nb, int fd)
{
	if (nb >= 10)
		ft_putulnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + 48, fd);
}
