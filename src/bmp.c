/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:09:22 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/04 23:18:31 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	raw_pixel_data(t_map *elem, int fd)
{
	int i;
	int k;

	i = elem->y - 1;
	k = 0;
	while (i >= 0)
	{
		while (k < elem->x)
		{
			write(fd, &elem->screen.data_img[k + i * elem->x], 4);
			k++;
		}
		k = 0;
		i--;
	}
	close_w(elem);
}

void	img_info_data(t_map *elem, int fd)
{
	unsigned int header_size;
	unsigned int planes_count;
	unsigned int bpp;
	unsigned int zero;

	header_size = 40;
	planes_count = 1;
	bpp = elem->screen.bits_per_pixel;
	zero = 0;
	write(fd, &header_size, 4);
	write(fd, &elem->x, 4);
	write(fd, &elem->y, 4);
	write(fd, &planes_count, 2);
	write(fd, &bpp, 2);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	raw_pixel_data(elem, fd);
}

void	save_bmp(t_map *elem)
{
	int				fd;
	unsigned int	file_size;
	unsigned int	pixel_data_offset;
	unsigned int	zero;

	zero = 0;
	file_size = 58 + (elem->x * elem->y) * (elem->screen.bits_per_pixel / 8);
	pixel_data_offset = 58;
	fd = open("Cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, &zero, 2);
	write(fd, &zero, 2);
	write(fd, &pixel_data_offset, 4);
	img_info_data(elem, fd);
	close(fd);
}

int		save(t_map *elem)
{
	if (elem->argc > 2)
	{
		if (ft_strlen(elem->argv) == 6)
		{
			if (ft_strncmp(elem->argv, "--save", 6) == 0)
				return (1);
		}
	}
	return (0);
}

void	fill_argv(char **argv, int argc, t_map *elem)
{
	int i;

	i = 0;
	elem->argc = argc;
	if (argc > 2)
	{
		if (!(elem->argv = malloc(ft_strlen(argv[2]) + 1)))
			return ;
		while (argv[2][i])
		{
			elem->argv[i] = argv[2][i];
			i++;
		}
		elem->argv[i] = 0;
	}
	else
		elem->argv = NULL;
}
