/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:16:40 by tomoron           #+#    #+#             */
/*   Updated: 2025/03/20 16:58:18 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_settings	*get_settings(void)
{
	static t_settings	settings;
	char				*str;

	if (!settings.initialized)
	{
		if (getenv("MALLOC_SHOW_LEAKS"))
			settings.show_leaks = 1;
		if (getenv("MALLOC_NO_UNMAP"))
			settings.no_unmap = 1;
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
	return (&settings);
}
