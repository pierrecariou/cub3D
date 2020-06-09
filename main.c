/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 08:54:40 by pcariou           #+#    #+#             */
/*   Updated: 2020/06/09 18:55:48 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	key_action(map_list *elem)
{
	if (elem->key_down[119])
	{
		if ((elem->map[(int)((elem->posy - sin(elem->rad) * 10) / 64)]
				[(int)((elem->posx + cos(elem->rad) * 10) / 64)] != '1')
			&& sqrt(pow((elem->posx + cos(elem->rad) * 5) - elem->sprites[0].x, 2) +
			pow((elem->posy - sin(elem->rad) * 5) -
			elem->sprites[0].y, 2)) * 0.9 >= (elem->cubs / 6))
		{
			elem->posx += cos(elem->rad) * 5;
			elem->posy -= sin(elem->rad) * 5;
		}
	}
	if (elem->key_down[115])
	{
		if ((elem->map[(int)((elem->posy + sin(elem->rad) * 10) / 64)]
				[(int)((elem->posx - cos(elem->rad) * 10) / 64)] != '1')
			&& sqrt(pow((elem->posx - cos(elem->rad) * 5) - elem->sprites[0].x, 2) 
			+ pow((elem->posy + sin(elem->rad) * 5)  -
			elem->sprites[0].y, 2)) * 0.9 >= (elem->cubs / 6))
		{
			elem->posx -= cos(elem->rad) * 5;
			elem->posy += sin(elem->rad) * 5;
		}
	}
	if (elem->key_down[65363])
	{
		elem->rad -= 0.04;
	}
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
	close_win(elem);
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
	map_infos(&elem);
	elem.abr = (M_PI / 3) / elem.x;
	elem.ptr[0] = mlx_init();
	elem.ptr[1] = mlx_new_window(elem.ptr[0], elem.x, elem.y, "Cub3D");
	new_texture(&elem);
	mlx_hook(elem.ptr[1], 2, (1L << 0), key_press_hook, &elem);
	mlx_hook(elem.ptr[1], 3, (1L << 1), key_release_hook, &elem);

	mlx_loop_hook(elem.ptr[0], loop, &elem);
	mlx_loop(elem.ptr[0]);
	return (0);
}
