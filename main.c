/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 08:54:40 by pcariou           #+#    #+#             */
/*   Updated: 2020/07/27 03:26:13 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int		wallsbetween(map_list *elem)
{
	double distwall1;
	double distwall2;
	double dist;

	distwall1 = finding_v(elem);
	distwall2 = finding_h(elem);
	dist = (distwall1 <= distwall2) ? distwall1 : distwall2;
	if (dist <= sqrt(pow(elem->posx - (elem->posx + cos(elem->rad) * 5), 2) +
				pow(elem->posy - (elem->posy - sin(elem->rad) * 5), 2)) *
			cos(elem->cr - elem->rad))
		return (1);
	return (0);
}

void	key_action_bis(map_list *elem)
{
	if (elem->key_down[119])
	{
		if ((elem->map[(int)((elem->posy - sin(elem->rad) * 5) / 64)]
			[(int)((elem->posx + cos(elem->rad) * 5) / 64)] != '1')
			&& sqrt(pow((elem->posx + cos(elem->rad) * 5) -
			elem->sprites[0].x, 2) + pow((elem->posy - sin(elem->rad) * 5)
			- elem->sprites[0].y, 2)) * 0.9 >= (elem->cubs / 6)
			&& wallsbetween(elem) == 0)
		{
			elem->posx += cos(elem->rad) * 5;
			elem->posy -= sin(elem->rad) * 5;
		}
	}
	if (elem->key_down[115])
	{
		if ((elem->map[(int)((elem->posy + sin(elem->rad) * 6) / 64)]
			[(int)((elem->posx - cos(elem->rad) * 5) / 64)] != '1')
			&& sqrt(pow((elem->posx - cos(elem->rad) * 5) -
			elem->sprites[0].x, 2) + pow((elem->posy + sin(elem->rad) * 5)
			- elem->sprites[0].y, 2)) * 0.9 >= (elem->cubs / 6))
		{
			elem->posx -= cos(elem->rad) * 5;
			elem->posy += sin(elem->rad) * 5;
		}
	}
}

void	key_action(map_list *elem)
{
	if (elem->key_down[97])
	{
		if ((elem->map[(int)((elem->posy - sin(elem->rad + M_PI_2) * 5) / 64)]
			[(int)((elem->posx + cos(elem->rad + M_PI_2) * 5) / 64)] != '1')
			&& (sqrt(pow((elem->posx + cos(elem->rad + M_PI_2) * 5) -
			elem->sprites[0].x, 2) + pow((elem->posy - sin(elem->rad
			+ M_PI_2) * 5) - elem->sprites[0].y, 2)) * 0.9 >=
			(elem->cubs / 6)))
		{
			elem->posx += cos(elem->rad + M_PI_2) * 5;
			elem->posy -= sin(elem->rad + M_PI_2) * 5;
		}
	}
	if (elem->key_down[65363])
		elem->rad -= 0.04;
	key_action_bis(elem);
	key_action1(elem);
}

int		loop(map_list *elem)
{
	key_action(elem);
	elem->cr = elem->rad;
	if (elem->cr < 0)
		elem->cr += 2 * M_PI;
	else if (elem->cr > 2 * M_PI)
		elem->cr -= 2 * M_PI;
	call_all_rays(elem);
	if (elem->key_down[65307])
		close_w(elem);
	return (0);
}

int		key_press_hook(int key, map_list *elem)
{
	elem->key_down[key] = 1;
	return (0);
}

int		key_release_hook(int key, map_list *elem)
{
	elem->key_down[key] = 0;
	return (0);
}

int		close_w(map_list *elem)
{
	(void)elem;
	exit(0);
	return (0);
}

int	map_errors(map_list *elem, int e)
{
	(void)elem;
	if (e != 0)
	{
		write(1, "Error\n", 6);
		if (e == 1)
			write(1, "Please close the map\n", 21);
		else if (e == 2)
			write(1, "Wrong characters in the map\n", 28);
		else if (e == 3)
			write(1, "This is not a map\n", 18);
		else if (e == 4)
			write(1, "I can't play doom without a doom guy\n", 37);
		else if (e == 5)
			write(1, "XPM file not found\n", 19);
		else if (e == 6)
			write(1, "Wrong line\n", 11);
		else if (e == 7)
			write(1, "Missing information\n", 20);
		else if (e == 8)
			write(1, "Empty line in/after map or info repetition\n", 43);
		else if (e == 9)
			write(1, "RGB colors needs to be into 0-255 range\n", 40);
		return (1);
	}
	return (0);
}

void	raw_pixel_data(map_list *elem, int fd)
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

void	img_info_data(map_list *elem, int fd)
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

void	save_bmp(map_list *elem)
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

int		save(map_list *elem)
{
	if (elem->argc >= 2)
	{
		if (ft_strlen(elem->argv) == 6)
		{
			if (ft_strncmp(elem->argv, "--save", 6) == 0)
				return (1);
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	map_list	elem;
	map_coor	*coor;
	int i;

	i = 0;
	elem.argc = argc;
	if (argc >= 2)
	{
		if (!(elem.argv = malloc(ft_strlen(argv[1]) + 1)))
			return (0);
		while (argv[1][i])
		{
			elem.argv[i] = argv[1][i];
			i++;
		}
		elem.argv[i] = 0;
	}
	else
		elem.argv = NULL;
	if (!(coor = malloc(16)))
		return (0);
	coor->line = NULL;
	if (map_errors(&elem, read_file(&elem, coor)) == 1)
	{
		close_w(&elem);
		return (0);
	}
	elem.cubs = elem.y / 5;
	if (map_errors(&elem, create_map(coor, &elem)) == 1)
	{
		close_w(&elem);
		return (0);
	}
	init_dist_ratios(&elem);
	map_infos(&elem);
	elem.abr = (M_PI / 3) / elem.x;
	elem.ptr[0] = mlx_init();
	//mlx_get_screen_size(elem.ptr[0], &(elem.sizex), &(elem.sizey));
	if (map_errors(&elem, new_texture(&elem)) == 1)
	{
		close_w(&elem);
		return (0);
	}
	if (!(save(&elem)))
		elem.ptr[1] = mlx_new_window(elem.ptr[0], elem.x, elem.y, "Cub3D");
	else
	{
		loop(&elem);
		return (0);
	}
	mlx_hook(elem.ptr[1], 2, (1L << 0), key_press_hook, &elem);
	mlx_hook(elem.ptr[1], 3, (1L << 1), key_release_hook, &elem);
	// mlx_hook(elem.ptr[0], 4, 1L<<5, close, &elem);
	mlx_hook(elem.ptr[1], 17, (1L << 17), close_w, &elem);
	mlx_loop_hook(elem.ptr[0], loop, &elem);
	mlx_loop(elem.ptr[0]);
	return (0);
}
