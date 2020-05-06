/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:52:58 by pcariou           #+#    #+#             */
/*   Updated: 2020/05/06 14:23:29 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

double		finding_v(map_list *elem)
{
	double				coor[2];
	unsigned int		map[2];

	if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
		coor[0] = floor(elem->posx / 64) * 64 + 64;
	else
		coor[0] = floor(elem->posx / 64) * 64 - 0.0001;
	coor[1] = elem->posy + (elem->posx - coor[0]) * tan(elem->rad);
	map[0] = coor[0] / 64;
	map[1] = coor[1] / 64;
	if (map_out(elem, map, 1))
		return (finding_h(elem));
	while (map[1] > 0 && elem->map[map[1]][map[0]]
			&& elem->map[map[1]][map[0]] != '1')
	{
		computation_v(elem, map, coor);
		if (map_out(elem, map, 1))
			return (finding_h(elem));
	}
	if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
		elem->ratio_v = fmod(coor[1], 64);
	else
		elem->ratio_v = 64 - fmod(coor[1], 64);
	return (sqrt(pow(elem->posx - coor[0], 2) + pow(elem->posy - coor[1], 2)))
	* cos(elem->cr - elem->rad);
}

void		computation_h(map_list *elem, unsigned int *map, double *coor)
{
	if (elem->rad > M_PI)
	{
		coor[0] -= 64 / tan(elem->rad);
		coor[1] += 64;
	}
	else
	{
		coor[0] += 64 / tan(elem->rad);
		coor[1] -= 64;
	}
	map[0] = coor[0] / 64;
	map[1] = coor[1] / 64;
}

double		finding_h(map_list *elem)
{
	double			coor[2];
	unsigned int	map[2];

	if (elem->rad > M_PI)
		coor[1] = floor(elem->posy / 64) * 64 + 64;
	else
		coor[1] = floor(elem->posy / 64) * 64 - 0.000001;
	coor[0] = elem->posx + (elem->posy - coor[1]) / tan(elem->rad);
	map[0] = coor[0] / 64;
	map[1] = coor[1] / 64;
	if (map_out(elem, map, 0))
		return (finding_v(elem));
	while (map[0] > 0 && elem->map[map[1]][map[0]] &&
			elem->map[map[1]][map[0]] != '1')
	{
		computation_h(elem, map, coor);
		if (map_out(elem, map, 0))
			return (finding_v(elem));
	}
	if (elem->rad < M_PI)
		elem->ratio_h = fmod(coor[0], 64);
	else
		elem->ratio_h = 64 - fmod(coor[0], 64);
	return (sqrt(pow(elem->posx - coor[0], 2) + pow(elem->posy - coor[1], 2)))
	* cos(elem->cr - elem->rad);
}

void		map_infos2(map_list *elem, int x, int y)
{
	elem->posx = y * 64 + 32;
	elem->posy = x * 64 + 32;
	if (elem->map[x][y] == 'N')
	{
		elem->rad = M_PI_2;
		elem->cr = M_PI_2;
	}
	else if (elem->map[x][y] == 'S')
	{
		elem->rad = 3 * M_PI_2;
		elem->cr = 3 * M_PI_2;
	}
	else if (elem->map[x][y] == 'E')
	{
		elem->rad = 2 * M_PI;
		elem->cr = 2 * M_PI;
	}
	else if (elem->map[x][y] == 'W')
	{
		elem->rad = M_PI;
		elem->cr = M_PI;
	}
	elem->map[x][y] = '0';
}

void		map_infos1(map_list *elem, int x, int y, int k)
{
	while (elem->map[x])
	{
		while (elem->map[x][y])
		{
			if (elem->map[x][y] == 'N' || elem->map[x][y] == 'E' ||
					elem->map[x][y] == 'S' || elem->map[x][y] == 'W')
			{
				map_infos2(elem, x, y);
			}
			else if (elem->map[x][y] == '2')
			{
				elem->sprites[k].x = y * 64 + 32;
				elem->sprites[k].y = x * 64 + 32;
				k++;
			}
			y++;
		}
		y = 0;
		x++;
	}
}
