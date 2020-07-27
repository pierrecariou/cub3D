/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:15:16 by pcariou           #+#    #+#             */
/*   Updated: 2020/07/27 03:26:39 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	map_infos(map_list *elem)
{
	int x;
	int y;
	int k;

	x = 0;
	y = 0;
	k = 0;
	while (elem->map[x])
	{
		while (elem->map[x][y])
		{
			if (elem->map[x][y] == '2')
				elem->count_s += 1;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	if (!(elem->sprites = malloc(sizeof(data_s) * elem->count_s)))
		return ;
	map_infos1(elem, x, y, k);
}

void	call_all_rays(map_list *elem)
{
	int		i;
	double	h;
	double	v;

	i = 0;
	elem->rad += (M_PI / 6);
	while (i < elem->x)
	{
		if (elem->rad < 0)
			elem->rad += 2 * M_PI;
		else if (elem->rad > 2 * M_PI)
			elem->rad -= 2 * M_PI;
		h = finding_h(elem);
		v = finding_v(elem);
		choose_dist(h, v, i, elem);
		elem->rad -= elem->abr;
		i++;
	}
	elem->rad = elem->cr;
	trace_rays(elem);
}

void	init_dist_ratios(map_list *elem)
{
	int i;

	i = 0;
	if (!(elem->dist = malloc(sizeof(double) * elem->x)))
		return ;
	if (!(elem->sizes = malloc(sizeof(double) * elem->x)))
		return ;
	if (!(elem->ratios = malloc(sizeof(double) * elem->x)))
		return ;
	if (!(elem->orient = malloc(sizeof(char) * elem->x)))
		return ;
	if (!(elem->key_down = malloc(sizeof(int) * 66000)))
		return ;
	while (i < 66000)
	{
		elem->key_down[i] = 0;
		i++;
	}
	elem->count_s = 0;
}

void	key_action1(map_list *elem)
{
	if (elem->key_down[100])
	{
		if ((elem->map[(int)((elem->posy + sin(elem->rad + M_PI_2) * 5) / 64)]
				[(int)((elem->posx - cos(elem->rad + M_PI_2) * 5) / 64)] != '1')
				&& (sqrt(pow((elem->posx - cos(elem->rad + M_PI_2) * 5) -
				elem->sprites[0].x, 2) + pow((elem->posy + sin(elem->rad
				+ M_PI_2) * 5) - elem->sprites[0].y, 2)) * 0.9 >=
				(elem->cubs / 6)))
		{
			elem->posx -= cos(elem->rad + M_PI_2) * 5;
			elem->posy += sin(elem->rad + M_PI_2) * 5;
		}
	}
	if (elem->key_down[65361])
		elem->rad += 0.04;
}
