/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 08:54:40 by pcariou           #+#    #+#             */
/*   Updated: 2020/06/19 13:04:25 by pcariou          ###   ########.fr       */
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
	if (dist <= sqrt(pow(elem->posx - (elem->posx + cos(elem->rad) * 5), 2) + pow(elem->posy - (elem->posy - sin(elem->rad) * 5), 2)) * cos(elem->cr - elem->rad))	
		return (1);
	return (0);
}

void	key_action(map_list *elem)
{
	if (elem->key_down[119])
	{
		if ((elem->map[(int)((elem->posy - sin(elem->rad) * 5) / 64)]
					[(int)((elem->posx + cos(elem->rad) * 5) / 64)] != '1')
				&& sqrt(pow((elem->posx + cos(elem->rad) * 5) - elem->sprites[0].x, 2) +
					pow((elem->posy - sin(elem->rad) * 5) -
						elem->sprites[0].y, 2)) * 0.9 >= (elem->cubs / 6) && 
				wallsbetween(elem) == 0)
		{
			elem->posx += cos(elem->rad) * 5;
			elem->posy -= sin(elem->rad) * 5;
			//elem->b = 1;
		}
	}
	if (elem->key_down[115])
	{
		if ((elem->map[(int)((elem->posy + sin(elem->rad) * 5) / 64)]
					[(int)((elem->posx - cos(elem->rad) * 5) / 64)] != '1')
				&& sqrt(pow((elem->posx - cos(elem->rad) * 5) - elem->sprites[0].x, 2) 
					+ pow((elem->posy + sin(elem->rad) * 5)  -
						elem->sprites[0].y, 2)) * 0.9 >= (elem->cubs / 6))
		{
			elem->posx -= cos(elem->rad) * 5;
			elem->posy += sin(elem->rad) * 5;
			//elem->b = 1;
		}
	}
	if (elem->key_down[65363])
	{
		elem->rad -= 0.04;
		//elem->b = 1;
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

int close_w(void *param)
{
	write(1, "a", 1);;
	(void)param;
	exit(0);
	return (0);
}
/*
   int 	exit_hook(map_list *elem)
   {
   printf("bye\n");
   key_action(elem);
   exit(0);
   return (0);
   }
 */
void	free_errors(map_list *elem)
{
	int i;

	i = -1;
	free(elem->NO);
	free(elem->SO);
	free(elem->WE);
	free(elem->EA);
	free(elem->S);
	while (++i < 3)
	{
		free(elem->F[i]);
		free(elem->C[i]);
	}
	free(elem->F);
	free(elem->C);
	free(elem->F_color);
	free(elem->C_color);
	i = -1;
	while (elem->map[++i])
		free(elem->map[i]);
	free(elem->map);
}

int	map_errors(map_list *elem, int e)
{
	if (e != 0)
	{
		free_errors(elem);
		write(1, "Error\n", 6);
		if (e == 1)
			write(1, "Please close the map\n", 21);
		else if (e == 2)
			write(1, "Wrong characters in the map\n", 28);
		else if (e == 3)
			write(1, "This is not a map\n", 18);
		else if (e == 4)
			write(1, "I can't play doom without a doom guy\n", 37);
		return (1);
	}
	return (0);
}

int		main(void)
{
	map_list	elem;
	map_coor	*coor;
	//map_coor	*cp;

	//cp = NULL;
	if (!(coor = malloc(16)))
		return (0);
	//cp = coor;
	coor->line = NULL;
	if (map_errors(&elem, read_file(&elem, coor)) == 1)
	{
		while (coor)
		{
			//cp = coor;
			free(coor->line);
			free(coor);
			coor = coor->next;
		}
		return (0);
	}
	elem.cubs = elem.y / 5;
	if (map_errors(&elem, create_map(coor, &elem)) == 1)
	{
		while (coor)
		{
			//cp = coor;
			free(coor->line);
			free(coor);
			coor = coor->next;
		}
		return (0);
	}
	init_dist_ratios(&elem);
	map_infos(&elem);
	elem.abr = (M_PI / 3) / elem.x;
	elem.ptr[0] = mlx_init();
	//mlx_get_screen_size(elem.ptr[0], &(elem.sizex), &(elem.sizey));
	elem.ptr[1] = mlx_new_window(elem.ptr[0], elem.x, elem.y, "Cub3D");
	new_texture(&elem);
	mlx_hook(elem.ptr[1], 2, (1L << 0), key_press_hook, &elem);
	mlx_hook(elem.ptr[1], 3, (1L << 1), key_release_hook, &elem);
	//mlx_hook(elem.ptr[0], 4, 1L<<5, close, &elem);
	mlx_hook(elem.ptr[1], 17, (1L << 17), close_w, &elem);
	mlx_loop_hook(elem.ptr[0], loop, &elem);
	mlx_loop(elem.ptr[0]);
	return (0);
}
