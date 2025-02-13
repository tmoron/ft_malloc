/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:20:54 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/10 18:16:13 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

#include <errno.h>

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

int	log_fd(int closefd)
{
	static int	fd;

	if (closefd)
	{
		if (fd > 0)
			close(fd);
		return (0);
	}
	if (fd == 0)
	{
		fd = open("malloc.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putnbr_fd(errno, 1);
			write(2, "malloc(): can't open log file\n", 37);
		}
	}
	return (fd);
}

void	log_str(char *str, int level, int print_level, int nl)
{
	int	fd;

	if (level > get_settings()->debug_level)
		return ;
	fd = log_fd(0);
	if (fd == -1)
		return ;
	if (print_level && level == 1)
		ft_putstr_fd("[ERR]  ", fd);
	else if (print_level && level == 2)
		ft_putstr_fd("[WARN] ", fd);
	else if (print_level && level == 3)
		ft_putstr_fd("[INFO] ", fd);
	ft_putstr_fd(str, fd);
	if (nl)
		write(fd, "\n", 1);
}

void	log_ul(unsigned long nb, int level, int print_level, int nl)
{
	int	fd;

	if (level > get_settings()->debug_level)
		return ;
	fd = log_fd(0);
	if (fd == -1)
		return ;
	if (print_level && level == 1)
		ft_putstr_fd("[ERR]  ", fd);
	else if (print_level && level == 2)
		ft_putstr_fd("[WARN] ", fd);
	else if (print_level && level == 3)
		ft_putstr_fd("[INFO] ", fd);
	ft_putulnbr_fd(nb, fd);
	if (nl)
		write(fd, "\n", 1);
}
