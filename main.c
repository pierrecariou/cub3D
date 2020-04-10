/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 08:54:40 by pcariou           #+#    #+#             */
/*   Updated: 2020/03/12 21:50:15 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	color_c(char *data_img, map_list *elem, int size_line, int *c)
{
	data_img[c[0] * 4 + size_line * c[1]] = (unsigned int)ft_atoi(elem->C[2]);
	data_img[c[0] * 4 + size_line * c[1] + 1] = (unsigned int)ft_atoi(elem->C[1]);
	data_img[c[0] * 4 + size_line * c[1] + 2] = (unsigned int)ft_atoi(elem->C[0]);
}

void	color_f(char *data_img, map_list *elem, int size_line, int *c)
{
	data_img[c[0] * 4 + size_line * c[1]] = (unsigned int)ft_atoi(elem->F[2]);
	data_img[c[0] * 4 + size_line * c[1] + 1] = (unsigned int)ft_atoi(elem->F[1]);
	data_img[c[0] * 4 + size_line * c[1] + 2] = (unsigned int)ft_atoi(elem->F[0]);
}

void	insert_sprite(map_list	*elem, int *data_bi, int j)
{
	//int i;
	//int k;
	int x;
	int y;
	double left;
	double top;
	double ratio_v;
	double ratio_h;

	x = 0;
	y = 0;
	//i = 0;
	//k = 0;
	left = elem->sprites[j].x_begin;
	top = (elem->y / 2) - (elem->sprites[j].height / 2);
	//printf("%f  %f\n", left, top);
	/*
	   while (x < elem->x)
	   {
	   while (y < elem->y)
	   {
	   ratio_v = (i / elem->sprites[0].size) * elem->sprite.height;
	   ratio_h = (k / elem->sprites[0].size) * elem->sprite.width;
	//printf("HELLO%f/%f\n", ratio_v, ratio_h);
	if (x > left && x < left + elem->sprites[0].size && y > top && y < top + elem->sprites[0].size)
	{
	if (elem->sprite.data_img[(int)ratio_h + elem->sprite.width * (int)ratio_v] != elem->sprite.data_img[0])
	data_bi[x + elem->x * y] = elem->sprite.data_img[(int)ratio_h + elem->sprite.width * (int)ratio_v];
	i++;
	}
	y++;
	}
	i = 0;
	if (x > left)
	k++;
	y = 0;
	x++;
	}
	 */
	while (x < elem->sprites[j].height)
	{
		ratio_h = (x / elem->sprites[j].height) * elem->sprite.height;
		while (y < elem->sprites[j].height && top < elem->y)
		{
			ratio_v = (y / elem->sprites[j].height) * elem->sprite.height;
			if (elem->sprite.data_img[(int)ratio_h + elem->sprite.width * (int)ratio_v] != elem->sprite.data_img[j])
			{
				if ((int)top + 5 < elem->y)
					data_bi[((int)left + elem->x * (int)top)] = elem->sprite.data_img[(int)ratio_h + elem->sprite.width * (int)ratio_v];
			}
			top++;
			y++;
		}
		left++;
		top = (elem->y / 2) + (elem->sprites[j].height / 2);
		y = 0;
		x++;
	}
	//mlx_put_image_to_window(elem->ptr[0], elem->ptr[1], elem->sprite.img_ptr, 0,  0);	
}	

void	insert_texture(map_list *elem, int *p, int *data_bi, double ratio_v)
{
	//printf("%f/%f\n", elem->ratios[p[0]], elem->ratios[p[0]] / 64);
	if (elem->orient[p[0]] == 'N')
		data_bi[p[0] + elem->x * p[1]] = elem->t1.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t1.width) + ((int)(ratio_v) * elem->t1.width)];
	if (elem->orient[p[0]] == 'S')
		data_bi[p[0] + elem->x * p[1]] = elem->t2.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t2.width) + ((int)(ratio_v) * elem->t2.width)];
	if (elem->orient[p[0]] == 'E')
		data_bi[p[0] + elem->x * p[1]] = elem->t3.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t3.width) + ((int)(ratio_v) * elem->t3.width)];
	if (elem->orient[p[0]] == 'W')
		data_bi[p[0] + elem->x * p[1]] = elem->t4.data_img[(int)((elem->ratios[p[0]] / 64) * elem->t4.width) + ((int)(ratio_v) * elem->t4.width)];
}

void	new_texture(map_list *elem)
{
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
	//printf("bpp%d\nsize%d\nendian%d\n", elem->sprite.bits_per_pixel, elem->sprite.size_line, elem->sprite.endian);
	//printf("width%d\nheight%d\n", elem->sprite.width, elem->sprite.height);
}

void	sort_sprites(map_list *elem)
{
	int i;
	int k;
	data_s	cp;

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

void	dist_player(map_list *elem)
{
	int i;

	i =  0;
	//double degrees;
	//double leftangle;
	while (i < elem->count_s)
	{
		elem->sprites[i].dist = sqrt(pow(elem->posx - elem->sprites[i].x, 2) + pow(elem->posy - elem->sprites[i].y, 2));
		//elem->sprites[i].rad = atan2(elem->sprites[i].y - elem->y, elem->sprites[i].x - elem->x);
		elem->sprites[i].height = ceil((elem->cubs) / elem->sprites[i].dist * 255);
		i++;
	}
	sort_sprites(elem);
}

void	trace_rays(map_list *elem)
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data_img;
	double ratio_v;
	int p[2];
	int i;

	p[0] = 0;
	p[1] = 0;
	i = 0;
	img_ptr = mlx_new_image(elem->ptr[0], elem->x, elem->y);
	data_img = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	while (p[0] < elem->x)
	{
		//printf("%c\n%f\n%d\n", elem->orient[p[0]], elem->ratios[p[0]], p[0]);
		while (p[1] < elem->y)
		{
			if (p[1] <= (elem->y / 2) - (ceil(elem->cubs / elem->dist[p[0]] * 255) / 2))
				color_c(data_img, elem, size_line, p);
			else if (p[1] > (elem->y / 2) - (ceil(elem->cubs / elem->dist[p[0]] * 255) / 2) && p[1] < (elem->y / 2) + (ceil(elem->cubs / elem->dist[p[0]] * 255) / 2))
			{
				if (p[1] == 0)
					i = ((elem->y / 2) - ((elem->cubs / elem->dist[p[0]] * 255) / 2)) * -1; 
				if (elem->orient[p[0]] == 'N')
					ratio_v = (i / (elem->cubs / elem->dist[p[0]] * 255)) * elem->t1.height;
				else if (elem->orient[p[0]] == 'S')
					ratio_v = (i / (elem->cubs / elem->dist[p[0]] * 255)) * elem->t2.height;
				else if (elem->orient[p[0]] == 'E')
					ratio_v = (i / (elem->cubs / elem->dist[p[0]] * 255)) * elem->t3.height;
				else if (elem->orient[p[0]] == 'W')
					ratio_v = (i / (elem->cubs / elem->dist[p[0]] * 255)) * elem->t4.height;
				insert_texture(elem, p, (int *)data_img, ratio_v);
				//((int *)data_img)[p[0] + elem->x * p[1]] = ((int *)data)[0];
				//color_red(data_img, size_line, p);
				i++;
			}
			else
				color_f(data_img, elem, size_line, p);
			p[1]++;
		}
		i = 0;
		p[1] = 0;
		p[0]++;
	}
	while (i < elem->count_s)
	{
		if (elem->sprites[i].visible)
			insert_sprite(elem, (int *)data_img, i);
		i++;
	}
	mlx_put_image_to_window(elem->ptr[0], elem->ptr[1], img_ptr,  0,  0);
}

void	choose_dist(double h, double v, int i, map_list *elem)
{
	int k;

	k = 0;
	//printf("%d - %d", elem->vh, elem->vv);
	if (h <= v)
	{
		elem->dist[i] = h;
		if (elem->ratio_h > 64)
		{
			elem->ratios[i] = elem->ratio_v;
			if (elem->vv != 0)
			{
				while (k < elem->vv)
				{
					if (!(elem->sprites[elem->countv[k]].visible))
					{
						elem->sprites[elem->countv[k]].visible = 1;
						elem->sprites[elem->countv[k]].x_begin = i;
					}
					elem->sprites[elem->countv[k]].x_end = i;
					k++;
				}
			}
			if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
				elem->orient[i] = 'E';
			else
				elem->orient[i] = 'W';
		}
		else
		{
			if (elem->vh != 0)
			{
				while (k < elem->vh)
				{
					if (!(elem->sprites[elem->counth[k]].visible))
					{
						elem->sprites[elem->counth[k]].visible = 1;
						elem->sprites[elem->counth[k]].x_begin = i;
					}
					elem->sprites[elem->counth[k]].x_end = i;
					k++;
				}
			}
			elem->ratios[i] = elem->ratio_h;
			if (elem->rad < M_PI)
				elem->orient[i] = 'N';
			else
				elem->orient[i] = 'S';
		}
	}
	else
	{
		if (elem->vv != 0)
		{
			while (k < elem->vv)
			{
				if (!(elem->sprites[elem->countv[k]].visible))
				{
					elem->sprites[elem->countv[k]].visible = 1;
					elem->sprites[elem->countv[k]].x_begin = i;
				}
				elem->sprites[elem->countv[k]].x_end = i;
				k++;
			}
		}
		elem->dist[i] = v;
		elem->ratios[i] = elem->ratio_v;
		if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
			elem->orient[i] = 'E';
		else
			elem->orient[i] = 'W';
	}
	k = 0;
	while (k < elem->vh)
	{
		elem->counth[k] = 0;
		k++;
	}
	k = 0;
	while (k < elem->vv)
	{
		elem->countv[k] = 0;
		k++;
	}
	elem->vh = 0;
	elem->vv = 0;
	//printf("ratio%d\n", elem->ratios[i]);
}

double	finding_v(map_list *elem)
{
	double y;
	double x;
	int xg;
	int yg;
	int i;
	//int xgrid;
	//int ygrid;
	i = 0;
	xg = elem->posx / 64;
	yg = elem->posy / 64;
	//xgrid = xg;
	//ygrid = yg;
	if (elem->rad < M_PI_2 || elem->rad  > 3 * M_PI_2)
		x = floor(elem->posx / 64) * 64 + 64;
	else
		x = floor(elem->posx / 64) * 64 - 0.0001;
	y = elem->posy + (elem->posx - x) * tan(elem->rad);
	xg = x / 64;
	yg = y / 64;

	if ((unsigned int)yg >= (unsigned int)elem->lines || (unsigned int)xg >= (unsigned int)elem->length)
	{
		elem->ratio_v = 65;
		elem->vv = 0;
		return (finding_h(elem));
	}
	if (elem->map[yg][xg] == '2')
	{
		while (i < elem->count_s)
		{
			if (elem->sprites[i].cox == yg && elem->sprites[i].coy == xg)
			{
				elem->countv[elem->vv] = i;
				elem->vv += 1;
				break ;
			}
			else
				i += 1;
		}
	}
	while (yg > 0 && elem->map[yg][xg] && elem->map[yg][xg] != '1')
	{
		if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
		{
			x += 64;
			y -= 64 * tan(elem->rad);
		}
		else
		{
			x -= 64;
			y += 64 * tan(elem->rad);
		}
		xg = x / 64;
		yg = y / 64;
		if ((unsigned int)yg >= (unsigned int)elem->lines || (unsigned int)xg >= (unsigned int)elem->length)
		{
			elem->ratio_v = 65;
			elem->vv = 0;
			return (finding_h(elem));
		}
		if (elem->map[yg][xg] == '2')
		{
			while (i < elem->count_s)
			{
				if (elem->sprites[i].cox == yg && elem->sprites[i].coy == xg)
				{
					elem->countv[elem->vv] = i;
					elem->vv += 1;
					break ;
				}
				else
					i += 1;;
			}
		}

	}
	if (elem->rad < M_PI_2 || elem->rad > 3 * M_PI_2)
		elem->ratio_v = fmod(y, 64);
	else
		elem->ratio_v = 64 - fmod(y, 64);
	return (sqrt(pow(elem->posx - x, 2) + pow(elem->posy - y, 2))) * cos(elem->cr - elem->rad);
}

double	finding_h(map_list *elem)
{
	double y;
	double x;
	int xg;
	int yg;
	int i;
	i = 0;
	xg = elem->posx / 64;
	yg = elem->posy / 64;
	if (elem->rad < 0)
		elem->rad += 2 * M_PI;
	else if (elem->rad > 2 * M_PI)
		elem->rad -= 2 * M_PI;
	if (elem->rad  > M_PI)
		y = floor(elem->posy / 64) * 64 + 64;
	else
		y = floor(elem->posy / 64) * 64 - 0.000001;
	x = elem->posx + (elem->posy - y) / tan(elem->rad);
	xg = x / 64;
	yg = y / 64;
	if ((unsigned int)yg >= (unsigned int)elem->lines || (unsigned int)xg >= (unsigned int)elem->length)
	{
		elem->ratio_h = 65;
		elem->vh = 0;
		return (finding_v(elem));
	}
	if (elem->map[yg][xg] == '2')
	{
		while (i < elem->count_s)
		{
			if (elem->sprites[i].cox == yg && elem->sprites[i].coy == xg)
			{
				elem->counth[elem->vh] = i;
				elem->vh += 1;
				break ;
			}
			else
				i += 1;
		}
	}
	while (xg > 0 && elem->map[yg][xg] && elem->map[yg][xg] != '1')
	{
		if (elem->rad > M_PI)
		{
			x -= 64 / tan(elem->rad);
			y += 64;
		}
		else
		{
			x += 64 / tan(elem->rad);
			y -= 64;
		}
		xg = x / 64;
		yg = y / 64;	
		if ((unsigned int)yg >= (unsigned int)elem->lines || (unsigned int)xg >= (unsigned int)elem->length)
		{
			elem->ratio_h = 65;
			elem->vh = 0;
			return (finding_v(elem));
		}
		if (elem->map[yg][xg] == '2')
		{
			while (i < elem->count_s)
			{
				if (elem->sprites[i].cox == yg && elem->sprites[i].coy == xg)
				{
					elem->counth[elem->vh] = i;
					elem->vh += 1;
					break ;
				}
				else
					i += 1;
			}
		}
	}
	if (elem->rad < M_PI)
		elem->ratio_h = fmod(x, 64);
	else
		elem->ratio_h = 64 - fmod(x, 64);
	return (sqrt(pow(elem->posx - x, 2) + pow(elem->posy - y, 2))) * cos(elem->cr - elem->rad);
}

/*
   void	put_square(char coor, int x, int y, map_list *elem)
   {
   void	*img_ptr;
   int		bits_per_pixel;
   int		size_line;
   int		endian;
   char	*data_img;
   int p[2];
   p[0] = 0;
   p[1] = 0;
   img_ptr = mlx_new_image(elem->ptr[0], 64, 64);
   data_img = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
   while (p[0] < 64)
   {
   while (p[1] < 64)
   {
   if (coor == '1')
   color_red(data_img, size_line, p);
   else if (coor == '0' || coor == '2')
   color_green(data_img, size_line, p);
   else if (coor == 'N' || coor == 'W' || coor == 'E' || coor == 'S' )
   color_green(data_img, size_line, p);
   p[1]++;
   }
   p[1] = 0;
   p[0]++;
   }
   mlx_put_image_to_window(elem->ptr[0], elem->ptr[1], img_ptr,  y * 64,  x * 64);
   }
 */

void	put_map(map_list *elem)
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
	printf("HELLO%d\n", elem->count_s);
	x = 0;
	y = 0;
	if (!(elem->sprites = malloc(sizeof(data_s) * elem->count_s)))
		return ;
	while (elem->map[x])
	{
		while (elem->map[x][y])
		{
			//put_square(elem->map[x][y], x, y, elem);
			if (elem->map[x][y] == 'N')
			{
				elem->posx = y * 64 + 32;
				elem->posy = x * 64 + 32;
				elem->rad = M_PI_2;
				elem->cr= M_PI_2;
				elem->map[x][y] = '0';
			}
			else if (elem->map[x][y] == '2')
			{
				elem->sprites[k].x = x * 64  + 32; 
				elem->sprites[k].y = y * 64  + 32;
				elem->sprites[k].cox = x;
				elem->sprites[k].coy = y;
				//printf("%d / %d \n", elem->sprites[k].cox, elem->sprites[k].coy);
				k++;
			}
			y++;
		}
		y = 0;
		x++;
	}
	//mlx_pixel_put(elem->ptr[0], elem->ptr[1], elem->posx, elem->posy, 16777215);
}

void	call_all_rays(map_list *elem)
{
	int i;
	double h;
	double v;

	i = 0;
	elem->cr = elem->rad;
	elem->rad -= (M_PI / 6);
	while (i < elem->x)
	{
		h = finding_h(elem);
		v = finding_v(elem);
		choose_dist(h, v, i, elem);
		elem->rad += elem->abr;
		i++;
	}
	elem->rad = elem->cr;
	trace_rays(elem);
}

int	close_win(int key, map_list *elem)
{
	(void)elem;
	if (key == 53)
	{
		//mlx_destroy_window(&ptr[0], &ptr[1]);
		exit(0);
	}	
	return (0);
}

void	init_dist_ratios(map_list *elem)
{
	int i;

	i = 0;
	if (!(elem->dist = malloc(sizeof(double) * elem->x)))
		return ;
	if (!(elem->ratios = malloc(sizeof(double) * elem->x)))
		return ;
	if (!(elem->orient = malloc(sizeof(char) * elem->x)))
		return ;
	if (!(elem->key_down = malloc(sizeof(int) * 2000)))
		return ;
	if (!(elem->countv = malloc(sizeof(int) * 100)))
		return ;
	if (!(elem->counth = malloc(sizeof(int) * 100)))
		return ;
	while (i < 100)
	{
		elem->countv[i] = 0;
		i++;
	}
	i = 0;
	while (i < 100)
	{
		elem->counth[i] = 0;
		i++;
	}
	i = 0;
	while (i < 2000)
	{
		elem->key_down[i] = 0;
		i++;
	}
	elem->vh = 0;
	elem->vv = 0;
	elem->count_s = 0;
}

void		key_action(map_list *elem)
{
	if (elem->key_down[119])
	{
		if (elem->map[(int)((elem->posy - sin(elem->rad) * 10) / 64)][(int)((elem->posx + cos(elem->rad) * 10) / 64)] != '1')
		{
			elem->posx += cos(elem->rad) * 10;
			elem->posy -= sin(elem->rad) * 10;
		}
	}
	if (elem->key_down[115])
	{
		if (elem->map[(int)((elem->posy + sin(elem->rad) * 10) / 64)][(int)((elem->posx - cos(elem->rad) * 10) / 64)] != '1')
		{
			elem->posx -= cos(elem->rad) * 10;
			elem->posy += sin(elem->rad) * 10;
		}
	}
	if (elem->key_down[100])
	{
		if (elem->map[(int)((elem->posy - sin(elem->rad + M_PI_2) * 10) / 64)][(int)((elem->posx + cos(elem->rad + M_PI_2) * 10) / 64)] != '1')
		{

			elem->posx += cos(elem->rad + M_PI_2) * 10;
			elem->posy -= sin(elem->rad + M_PI_2) * 10;
			//right
		}
	}
	if (elem->key_down[97])
	{
		if (elem->map[(int)((elem->posy + sin(elem->rad + M_PI_2) * 10) / 64)][(int)((elem->posx - cos(elem->rad + M_PI_2) * 10) / 64)] != '1')
		{
			elem->posx -= cos(elem->rad + M_PI_2) * 10;
			elem->posy += sin(elem->rad + M_PI_2) * 10;
			//left
		}
	}
	if (elem->key_down[65361])
	{
		elem->rad -= 0.08;
	}
	if (elem->key_down[65363])
	{
		elem->rad += 0.08;
	}
	//printf("%d\n", key);
}

int		loop(map_list *elem)
{
	int i = 0;
	key_action(elem);
	dist_player(elem);
	call_all_rays(elem);
	//elem->count = 0;
	while (i < elem->count_s)
	{
		printf("%d - %d\n", i, elem->sprites[i].visible);
		//	printf("%d / %d \n", elem->sprites[i].coy, elem->sprites[i].cox);
		elem->sprites[i].visible = 0;
		i++;
	}
	//mlx_put_image_to_window(elem->ptr[0], elem->ptr[1], elem->sprite.img_ptr, 0,  0);
	return (0);
}

int	key_press_hook(int key, map_list *elem)
{
	elem->key_down[key] = 1;
	return (0);
}

int	key_release_hook(int key, map_list *elem)
{
	elem->key_down[key] = 0;
	return (0);
}

int		main(void)
{
	map_list	elem;
	map_coor	*coor;

	if (!(coor = malloc(16)))
		return (0);
	coor->line = NULL;
	read_file(&elem, coor);
	elem.cubs = elem.y / 5;
	init_dist_ratios(&elem);
	create_map(coor, &elem);
	put_map(&elem);
	elem.abr = (M_PI / 3) / elem.x;
	elem.ptr[0] = mlx_init();
	elem.ptr[1] = mlx_new_window(elem.ptr[0], elem.x, elem.y, "Cub3D");	
	new_texture(&elem);
	//mlx_key_hook(elem.ptr[1], close_win, &elem);
	mlx_hook(elem.ptr[1], 2, (1L << 0), key_press_hook, &elem);
	mlx_hook(elem.ptr[1], 3, (1L << 1), key_release_hook, &elem);
	mlx_loop_hook(elem.ptr[0], loop, &elem);
	//printf("sizeof%lu\n", sizeof(elem));
	mlx_loop(elem.ptr[0]);
	return (0);
}
