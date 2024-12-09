/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:16:40 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/09 17:45:45 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdio.h>

t_settings *get_settings()
{
	static t_settings settings;
	char *str;

	if(!settings.initialized)
	{
		if (getenv("MALLOC_SHOW_LEAKS"))
			settings.show_leaks = 0;
		str = getenv("MALLOC_DEBUG_LEVEL");
		if (!str || !ft_strcmp(str, "NONE"))
			settings.debug_level = 0;
		else if (str && !ft_strcmp(str, "ERR"))
			settings.debug_level = 1;
		else if (str && !ft_strcmp(str, "WARN"))
			settings.debug_level = 2;
		else if (str && !ft_strcmp(str, "INFO"))
			settings.debug_level = 3;
		settings.initialized = 1;
	}
	return(&settings);
}
