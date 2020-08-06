/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 01:13:36 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:13:41 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		loop(t_map *elem)
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

void	map_errors1(int e)
{
	if (e == 5)
		write(1, "XPM file not found\n", 19);
	else if (e == 6)
		write(1, "Wrong line\n", 11);
	else if (e == 7)
		write(1, "Missing information\n", 20);
	else if (e == 8)
		write(1, "Empty line in/after map or info repetition\n", 43);
	else if (e == 9)
		write(1, "RGB colors needs to be into 0-255 range\n", 40);
	else if (e == 10)
		write(1, "le premier argument doit etre un fichier de map valide\n",
		55);
}

int		map_errors(int e)
{
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
		map_errors1(e);
		return (1);
	}
	return (0);
}

void	save_or_not(t_map *elem)
{
	if (!(save(elem)))
		elem->ptr[1] = mlx_new_window(elem->ptr[0], elem->x, elem->y, "Cub3D");
	else
	{
		loop(elem);
		exit(0);
	}
}

int		main(int argc, char **argv)
{
	t_map	elem;
	t_coor	*coor;

	fill_argv(argv, argc, &elem);
	if (!(coor = malloc(16)))
		return (0);
	coor->line = NULL;
	elem.ptr[0] = mlx_init();
	if (map_errors(read_file(&elem, coor, argc, argv)) ||
			map_errors(create_map(coor, &elem)))
		close_w(&elem);
	init_dist_ratios(&elem);
	map_infos(&elem);
	elem.abr = (M_PI / 3) / elem.x;
	elem.cubs = elem.y / 5;
	if (map_errors(new_texture(&elem)))
		close_w(&elem);
	save_or_not(&elem);
	mlx_hook(elem.ptr[1], 2, (1L << 0), key_press_hook, &elem);
	mlx_hook(elem.ptr[1], 3, (1L << 1), key_release_hook, &elem);
	mlx_hook(elem.ptr[1], 17, (1L << 17), close_w, &elem);
	mlx_loop_hook(elem.ptr[0], loop, &elem);
	mlx_loop(elem.ptr[0]);
	return (0);
}
