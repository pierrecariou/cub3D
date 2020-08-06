/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textcolo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:08:00 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:24:15 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	color_c(t_map *elem, char *data_img, int *c)
{
	data_img[c[0] * 4 + elem->screen.size_line * c[1]] = elem->c_color[2];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 1] = elem->c_color[1];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 2] = elem->c_color[0];
}

void	color_f(t_map *elem, char *data_img, int *c)
{
	data_img[c[0] * 4 + elem->screen.size_line * c[1]] = elem->f_color[2];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 1] = elem->f_color[1];
	data_img[c[0] * 4 + elem->screen.size_line * c[1] + 2] = elem->f_color[0];
}

void	insert_texture(t_map *elem, int *p, int *data_bi, int i)
{
	if (elem->orient[p[0]] == 'N')
		data_bi[p[0] + elem->x * p[1]] = elem->t1.data_img
		[(int)((elem->ratios[p[0]] / 64) * elem->t1.width) +
		((int)(i / (elem->sizes[p[0]]) * elem->t1.height) * elem->t1.width)];
	else if (elem->orient[p[0]] == 'S')
		data_bi[p[0] + elem->x * p[1]] = elem->t2.data_img
		[(int)((elem->ratios[p[0]] / 64) * elem->t2.width) +
		((int)(i / (elem->sizes[p[0]]) * elem->t2.height) * elem->t2.width)];
	else if (elem->orient[p[0]] == 'E')
		data_bi[p[0] + elem->x * p[1]] = elem->t3.data_img
		[(int)((elem->ratios[p[0]] / 64) * elem->t3.width) +
		((int)(i / (elem->sizes[p[0]]) * elem->t3.height) * elem->t3.width)];
	else if (elem->orient[p[0]] == 'W')
		data_bi[p[0] + elem->x * p[1]] = elem->t4.data_img
		[(int)((elem->ratios[p[0]] / 64) * elem->t4.width) +
		((int)(i / (elem->sizes[p[0]]) * elem->t4.height) * elem->t4.width)];
}

int		new_texture(t_map *elem)
{
	if (!(elem->sprite.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->s,
		&(elem->sprite.width), &(elem->sprite.height))) ||
		!(elem->t1.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->no,
		&(elem->t1.width), &(elem->t1.height))) ||
		!(elem->t2.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->so,
		&(elem->t2.width), &(elem->t2.height))) ||
		!(elem->t3.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->ea,
		&(elem->t3.width), &(elem->t3.height))) ||
		!(elem->t4.img_ptr = mlx_xpm_file_to_image(elem->ptr[0], elem->we,
		&(elem->t4.width), &(elem->t4.height))))
		return (5);
	elem->sprite.data_img = (int *)mlx_get_data_addr(elem->sprite.img_ptr,
	&(elem->sprite.bits_per_pixel), &(elem->sprite.size_line),
	&(elem->sprite.endian));
	elem->t1.data_img = (int *)mlx_get_data_addr(elem->t1.img_ptr,
	&(elem->t1.bits_per_pixel), &(elem->t1.size_line), &(elem->t1.endian));
	elem->t2.data_img = (int *)mlx_get_data_addr(elem->t2.img_ptr,
	&(elem->t2.bits_per_pixel), &(elem->t2.size_line), &(elem->t2.endian));
	elem->t3.data_img = (int *)mlx_get_data_addr(elem->t3.img_ptr,
	&(elem->t3.bits_per_pixel), &(elem->t3.size_line), &(elem->t3.endian));
	elem->t4.data_img = (int *)mlx_get_data_addr(elem->t4.img_ptr,
	&(elem->t4.bits_per_pixel), &(elem->t4.size_line), &(elem->t4.endian));
	return (0);
}
