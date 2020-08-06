/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:53:49 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:23:59 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	sky_wall_floor(t_map *elem, int *p)
{
	int i;

	i = 0;
	while (p[0] < elem->x)
	{
		while (p[1] < elem->y)
		{
			if (p[1] <= (elem->y / 2) - (elem->sizes[p[0]] / 2))
				color_c(elem, (char *)elem->screen.data_img, p);
			else if (p[1] > (elem->y / 2) - (elem->sizes[p[0]] / 2) &&
				p[1] < (elem->y / 2) + (elem->sizes[p[0]] / 2))
			{
				if (p[1] == 0)
					i = ((elem->y / 2) - (elem->sizes[p[0]] / 2)) * -1;
				insert_texture(elem, p, elem->screen.data_img, i);
				i++;
			}
			else
				color_f(elem, (char *)elem->screen.data_img, p);
			p[1]++;
		}
		i = 0;
		p[1] = 0;
		p[0]++;
	}
}

void	trace_rays(t_map *elem)
{
	int		p[2];
	int		i;
	void	*ptr;

	p[0] = 0;
	p[1] = 0;
	ptr = mlx_new_image(elem->ptr[0], elem->x, elem->y);
	elem->screen.data_img = (int *)mlx_get_data_addr(ptr,
	&elem->screen.bits_per_pixel, &elem->screen.size_line,
	&elem->screen.endian);
	sky_wall_floor(elem, p);
	dist_player(elem);
	i = elem->count_s - 1;
	while (i >= 0)
	{
		if (((int)elem->sprites[i].left > 0 && (int)elem->sprites[i].right
			<= elem->x) || ((int)elem->sprites[i].right >= 0 &&
			(int)elem->sprites[i].left < elem->x))
			insert_sprite(elem, (int *)elem->screen.data_img, i);
		i--;
	}
	if (save(elem))
		save_bmp(elem);
	mlx_put_image_to_window(elem->ptr[0], elem->ptr[1], ptr, 0, 0);
	mlx_destroy_image(elem->ptr[0], ptr);
}

void	choose_dist(double h, double v, int i, t_map *elem)
{
	if (h <= v)
	{
		elem->dist[i] = h;
		if (elem->ratio_h > 64)
		{
			elem->ratios[i] = elem->ratio_v;
			elem->orient[i] = (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
			? 'E' : 'W';
		}
		else
		{
			elem->ratios[i] = elem->ratio_h;
			elem->orient[i] = (elem->rad < M_PI) ? 'N' : 'S';
		}
	}
	else
	{
		elem->dist[i] = v;
		elem->ratios[i] = elem->ratio_v;
		elem->orient[i] = (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
		? 'E' : 'W';
	}
	elem->sizes[i] = ceil(elem->cubs / elem->dist[i] * 255);
}

int		map_out(t_map *elem, unsigned int *map, int v)
{
	if (v == 1 && (map[1] >= (unsigned int)elem->lines || map[0] >=
		(unsigned int)ft_strlen(elem->map[map[1]])))
	{
		elem->ratio_v = 65;
		return (1);
	}
	else if (v == 0 && (map[1] >= (unsigned int)elem->lines || map[0] >=
		(unsigned int)ft_strlen(elem->map[map[1]])))
	{
		elem->ratio_h = 65;
		return (1);
	}
	return (0);
}

void	computation_v(t_map *elem, unsigned int *map, double *coor)
{
	if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
	{
		coor[0] += 64;
		coor[1] -= 64 * tan(elem->rad);
	}
	else
	{
		coor[0] -= 64;
		coor[1] += 64 * tan(elem->rad);
	}
	map[0] = coor[0] / 64;
	map[1] = coor[1] / 64;
}
