/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:26:31 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/04 23:26:36 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	key_action1(t_map *elem)
{
	if (elem->key_down[100])
	{
		if ((elem->map[(int)((elem->posy + sin(elem->rad + M_PI_2) * 5) / 64)]
				[(int)((elem->posx - cos(elem->rad + M_PI_2) * 5) / 64)] != '1')
				&& (sqrt(pow((elem->posx - cos(elem->rad + M_PI_2) * 5) -
				elem->sprites[0].x, 2) + pow((elem->posy + sin(elem->rad
				+ M_PI_2) * 5) - elem->sprites[0].y, 2)) * 0.9 >=
				(elem->cubs / 6)))
		{
			elem->posx -= cos(elem->rad + M_PI_2) * 5;
			elem->posy += sin(elem->rad + M_PI_2) * 5;
		}
	}
	if (elem->key_down[65361])
		elem->rad += 0.04;
}

int		wallsbetween(t_map *elem)
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

void	key_action_bis(t_map *elem)
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

void	key_action(t_map *elem)
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
