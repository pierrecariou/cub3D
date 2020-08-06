/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:37:15 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/04 23:37:23 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		check_rgb(unsigned int *color)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if (color[i] > 255)
			return (1);
	}
	return (0);
}

int		key_press_hook(int key, t_map *elem)
{
	elem->key_down[key] = 1;
	return (0);
}

int		key_release_hook(int key, t_map *elem)
{
	elem->key_down[key] = 0;
	return (0);
}

int		close_w(t_map *elem)
{
	(void)elem;
	exit(0);
	return (0);
}
