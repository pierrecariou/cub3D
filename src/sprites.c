/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:46:51 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:23:03 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_sprite(t_map *elem, int *data_bi, double *v, int j)
{
	if (elem->sprite.data_img[(int)v[2] + elem->sprite.width
		* (int)v[1]] != elem->sprite.data_img[0])
	{
		if ((int)elem->sprites[j].left >= 0 && elem->dist
			[(int)elem->sprites[j].left] > elem->sprites[j].dist)
			data_bi[((int)elem->sprites[j].left + elem->x * (int)v[0])] =
			elem->sprite.data_img[(int)v[2] + elem->sprite.width *
			(int)v[1]];
	}
}

/*
** top = v[0]
** ratio_v = v[1]
** ratio_h = v[2]
*/

void	insert_sprite(t_map *elem, int *data_bi, int j)
{
	int		x;
	int		y;
	double	v[3];

	x = 0;
	y = 0;
	v[0] = (elem->y / 2);
	while (x < elem->sprites[j].height && (int)elem->sprites[j].left < elem->x)
	{
		v[2] = (x / elem->sprites[j].height) * elem->sprite.width;
		while (y < elem->sprites[j].height && (int)v[0] < elem->y)
		{
			v[1] = (y / elem->sprites[j].height) * elem->sprite.height;
			draw_sprite(elem, data_bi, v, j);
			v[0]++;
			y++;
		}
		elem->sprites[j].left++;
		v[0] = (elem->y / 2);
		y = 0;
		x++;
	}
}

void	sort_sprites(t_map *elem)
{
	int		i;
	int		k;
	t_spri	cp;

	i = 0;
	k = 0;
	while (k < elem->count_s)
	{
		i = 0;
		while (i < elem->count_s - 1)
		{
			if (elem->sprites[i].dist > elem->sprites[i + 1].dist)
			{
				cp = elem->sprites[i];
				elem->sprites[i] = elem->sprites[i + 1];
				elem->sprites[i + 1] = cp;
			}
			i++;
		}
		k++;
	}
}

void	data_sprites(t_map *elem, double radb, int i)
{
	elem->sprites[i].dist = sqrt(pow(elem->posx - elem->sprites[i].x, 2) +
	pow(elem->posy - elem->sprites[i].y, 2)) * 0.9;
	elem->sprites[i].height = ceil((elem->cubs / 2) /
	elem->sprites[i].dist * 255);
	elem->sprites[i].rad = atan2(-(elem->sprites[i].y - elem->posy),
	elem->sprites[i].x - elem->posx) - (elem->sprites[i].height / 2)
	* elem->abr;
	if (elem->sprites[i].rad < 0)
		elem->sprites[i].rad += 2 * M_PI;
	else if (elem->sprites[i].rad > 2 * M_PI)
		elem->sprites[i].rad -= 2 * M_PI;
	if (radb < elem->sprites[i].rad)
		elem->sprites[i].right = (((radb + (2 * M_PI)) -
		elem->sprites[i].rad) / elem->abr);
	else
		elem->sprites[i].right = ((radb - elem->sprites[i].rad)
		/ elem->abr);
	elem->sprites[i].left = elem->sprites[i].right -
	(elem->sprites[i].height);
}

void	dist_player(t_map *elem)
{
	double	radb;
	int		i;

	i = 0;
	radb = elem->cr + M_PI / 6;
	if (radb < 0)
		radb += 2 * M_PI;
	else if (radb > 2 * M_PI)
		radb -= 2 * M_PI;
	while (i < elem->count_s)
	{
		data_sprites(elem, radb, i);
		i++;
	}
	sort_sprites(elem);
}
