/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:53:49 by pcariou           #+#    #+#             */
/*   Updated: 2020/06/19 12:33:36 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void    color_c(map_list *elem, char *data_img, int *c)
{
	data_img[c[0] * 4 + elem->screen.size_line * c[1]] = elem->C_color[2];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 1] = elem->C_color[1];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 2] = elem->C_color[0];
}

void    color_f(map_list *elem, char *data_img, int *c)
{
	data_img[c[0] * 4 + elem->screen.size_line * c[1]] = elem->F_color[2];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 1] = elem->F_color[1];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 2] = elem->F_color[0];
}

void    insert_sprite(map_list  *elem, int *data_bi, int j)
{
	int x;
	int y;
	double top;
	double ratio_v;
	double ratio_h;

	x = 0;
	y = 0;
	top = (elem->y / 2);
	/*
	if ((int)elem->sprites[j].left < 0)
	{
		x = elem->sprites[j].left * -1;
		elem->sprites[j].left = 0;
	}
	*/
	//printf("%d\n", (int)elem->sprites[j].left);
	while (x < elem->sprites[j].height && (int)elem->sprites[j].left < elem->x)
	{
		ratio_h = (x / elem->sprites[j].height) * elem->sprite.width;
		while (y < elem->sprites[j].height && (int)top < elem->y)
		{
			ratio_v = (y / elem->sprites[j].height) * elem->sprite.height;
			if (elem->sprite.data_img[(int)ratio_h + elem->sprite.width * (int)ratio_v] != elem->sprite.data_img[0])
			{
				if ((int)elem->sprites[j].left >= 0 && elem->dist[(int)elem->sprites[j].left] > elem->sprites[j].dist)
					data_bi[((int)elem->sprites[j].left + elem->x * (int)top)] = elem->sprite.data_img[(int)ratio_h + elem->sprite.width * (int)ratio_v];
			}
			top++;
			y++;
		}
		elem->sprites[j].left++;
		top = (elem->y / 2);
		y = 0;
		x++;
	}
}

void    insert_texture(map_list *elem, int *p, int *data_bi, int i)
{
	if (elem->orient[p[0]] == 'N')
		data_bi[p[0] + elem->x * p[1]] = elem->t1.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t1.width) + ((int)(i / (elem->sizes[p[0]]) * elem->t1.height) * elem->t1.width)];
	if (elem->orient[p[0]] == 'S')
		data_bi[p[0] + elem->x * p[1]] = elem->t2.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t2.width) + ((int)(i / (elem->sizes[p[0]]) * elem->t2.height) * elem->t2.width)];
	if (elem->orient[p[0]] == 'E')
		data_bi[p[0] + elem->x * p[1]] = elem->t3.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t3.width) + ((int)(i / (elem->sizes[p[0]]) * elem->t3.height) * elem->t3.width)];
	if (elem->orient[p[0]] == 'W')
		data_bi[p[0] + elem->x * p[1]] = elem->t4.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t4.width) + ((int)(i / (elem->sizes[p[0]]) * elem->t4.height) * elem->t4.width)];
}

void    new_texture(map_list *elem)
{
//	elem->screen.img_ptr = mlx_new_image(elem->ptr[0], elem->x, elem->y);
//	elem->screen.data_img = (int *)mlx_get_data_addr(elem->screen.img_ptr, &elem->screen.bits_per_pixel, &elem->screen.size_line, &elem->screen.endian);
	elem->t1.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->NO, &(elem->t1.width), &(elem->t1.height));
	elem->t1.data_img = (int *)mlx_get_data_addr(elem->t1.img_ptr, &(elem->t1.bits_per_pixel), &(elem->t1.size_line), &(elem->t1.endian));
	elem->t2.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->SO, &(elem->t2.width), &(elem->t2.height));
	elem->t2.data_img = (int *)mlx_get_data_addr(elem->t2.img_ptr, &(elem->t2.bits_per_pixel), &(elem->t2.size_line), &(elem->t2.endian));
	elem->t3.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->EA, &(elem->t3.width), &(elem->t3.height));
	elem->t3.data_img = (int *)mlx_get_data_addr(elem->t3.img_ptr, &(elem->t3.bits_per_pixel), &(elem->t3.size_line), &(elem->t3.endian));
	elem->t4.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->WE, &(elem->t4.width), &(elem->t4.height));
	elem->t4.data_img = (int *)mlx_get_data_addr(elem->t4.img_ptr, &(elem->t4.bits_per_pixel), &(elem->t4.size_line), &(elem->t4.endian));
	elem->sprite.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->S, &(elem->sprite.width), &(elem->sprite.height));
	elem->sprite.data_img = (int *)mlx_get_data_addr(elem->sprite.img_ptr, &(elem->sprite.bits_per_pixel), &(elem->sprite.size_line), &(elem->sprite.endian));	
}

void    sort_sprites(map_list *elem)
{
	int i;
	int k;
	data_s  cp;

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

void    dist_player(map_list *elem)
{
	double radb;

	radb = elem->cr + M_PI / 6;
	if (radb < 0)
		radb += 2 * M_PI;
	else if (radb > 2 * M_PI)
		radb -= 2 * M_PI;

	int i;

	i =  0;
	while (i < elem->count_s)
	{
		elem->sprites[i].dist = sqrt(pow(elem->posx - elem->sprites[i].x, 2) + pow(elem->posy - elem->sprites[i].y, 2)) * 0.9;
		elem->sprites[i].height = ceil((elem->cubs / 2) / elem->sprites[i].dist * 255);
		elem->sprites[i].rad = atan2( - (elem->sprites[i].y - elem->posy), elem->sprites[i].x - elem->posx) - (elem->sprites[i].height / 2) * elem->abr;
		if (elem->sprites[i].rad < 0)
			elem->sprites[i].rad += 2 * M_PI;
		else if (elem->sprites[i].rad > 2 * M_PI)
			elem->sprites[i].rad -= 2 * M_PI;
		if (radb < elem->sprites[i].rad)
			elem->sprites[i].right = (((radb + (2 * M_PI)) - elem->sprites[i].rad) / elem->abr);
		else
			elem->sprites[i].right = ((radb - elem->sprites[i].rad) / elem->abr);
		elem->sprites[i].left = elem->sprites[i].right - (elem->sprites[i].height);
		i++;
	}
	sort_sprites(elem);
}

void    trace_rays(map_list *elem)
{
	int p[2];
	int i;
	void *ptr;

	p[0] = 0;
	p[1] = 0;
	i = 0;
	ptr = mlx_new_image(elem->ptr[0], elem->x, elem->y);
	elem->screen.data_img = (int *)mlx_get_data_addr(ptr, &elem->screen.bits_per_pixel, &elem->screen.size_line, &elem->screen.endian);

	while (p[0] < elem->x)
	{
		while (p[1] < elem->y)
		{
			if (p[1] <= (elem->y / 2) - (elem->sizes[p[0]] / 2))
				color_c(elem, (char *)elem->screen.data_img, p);
			else if (p[1] > (elem->y / 2) - (elem->sizes[p[0]] / 2) && p[1] < (elem->y / 2) + (elem->sizes[p[0]] / 2))
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
	dist_player(elem);
	i = elem->count_s - 1;
	while (i >= 0)
	{
		if (((int)elem->sprites[i].left > 0 && (int)elem->sprites[i].right <= elem->x)
			|| ((int)elem->sprites[i].right >= 0 && (int)elem->sprites[i].left < elem->x))
			insert_sprite(elem, (int *)elem->screen.data_img, i);
		i--;
	}
	mlx_put_image_to_window(elem->ptr[0], elem->ptr[1], ptr,  0,  0);
	mlx_destroy_image (elem->ptr[0], ptr);
}

void	choose_dist(double h, double v, int i, map_list *elem)
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

int		map_out(map_list *elem, unsigned int *map, int v)
{
	if (v == 1 && (map[1] >= (unsigned int)elem->lines || map[0] >= (unsigned int)ft_strlen(elem->map[map[1]])))
	{
		elem->ratio_v = 65;
		return (1);
	}
	else if (v == 0 && (map[1] >= (unsigned int)elem->lines || map[0] >= (unsigned int)ft_strlen(elem->map[map[1]])))
	{
		elem->ratio_h = 65;
		return (1);
	}
	return (0);
}

void    computation_v(map_list *elem, unsigned int *map, double *coor)
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
