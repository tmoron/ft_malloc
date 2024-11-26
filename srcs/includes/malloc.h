/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:38:01 by tomoron           #+#    #+#             */
/*   Updated: 2024/11/26 20:17:37 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# ifndef DEBUG
#  define DEBUG 1
# endif

#include <stddef.h>
void *malloc(size_t size);

#endif
