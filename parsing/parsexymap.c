/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexymap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:48:35 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 00:48:38 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	lst_new(char *line_coor, t_coor *coor)
{
	t_coor	*new_coor;

	if (!(coor->line))
	{
		coor->line = line_coor;
		coor->next = 0;
	}
	else
	{
		if (!(new_coor = malloc(16)))
			return ;
		new_coor->line = line_coor;
		new_coor->next = 0;
		while (coor->next)
			coor = coor->next;
		coor->next = new_coor;
	}
}

int		fill_line(t_coor *coor, char *line, int i, char *line_coor)
{
	int k;

	k = 0;
	if (!(line_coor = malloc(ft_strlen(line) + 1)))
		return (0);
	while (line[k])
	{
		if (line[k] == '1' || line[k] == '0' || line[k] == '2' ||
				line[k] == 'N' || line[k] == 'S' || line[k] == 'W' ||
				line[k] == 'E' || line[k] == ' ')
		{
			line_coor[i] = line[k];
			i++;
		}
		else
		{
			free(line_coor);
			return (2);
		}
		k++;
	}
	line_coor[i] = 0;
	lst_new(line_coor, coor);
	return (0);
}

int		read_coor(t_coor *coor, char *line)
{
	int		i;
	int		k;
	char	*line_coor;

	i = 0;
	k = 0;
	line_coor = NULL;
	while (line[k] == ' ')
		k++;
	if (line[k] == '1')
	{
		if (fill_line(coor, line, i, line_coor) == 2)
			return (2);
	}
	else if (line[k] != 'R' && line[k] != 'N' && line[k] != 'S' &&
			line[k] != 'W' && line[k] != 'E' && line[k] != 'F' &&
			line[k] != 'C' && line[0])
		return (6);
	else
		return (8);
	return (0);
}

int		x_y_fill(t_map *elem, char *line, int i, char *x_y)
{
	int		k;
	char	c;

	k = 0;
	c = (i == 2) ? 'x' : 'y';
	while (line[i] == ' ')
		i++;
	if (!(ft_isdigit(line[i])))
		return (0);
	while (line[i] && line[i] != ' ')
	{
		if (!(ft_isdigit(line[i])))
			return (0);
		x_y[k] = line[i];
		k++;
		i++;
	}
	x_y[k] = 0;
	if (c == 'x')
		elem->x = ft_atoi(x_y);
	else
		elem->y = ft_atoi(x_y);
	return (i);
}

int		map_x_y(t_map *elem, char *line, int i)
{
	char	*x_y;
	int		k;

	if (line[0] == 'R' && line[1] == ' ')
	{
		if (!(x_y = malloc(5)))
			return (0);
		k = x_y_fill(elem, line, i, x_y);
		if (k == 0 ||
			x_y_fill(elem, line, k, x_y) == 0)
		{
			free(x_y);
			return (0);
		}
		free(x_y);
		mlx_get_screen_size(elem->ptr[0], &(elem->sizex), &(elem->sizey));
		elem->x = (elem->x > elem->sizex) ? elem->sizex : elem->x;
		elem->y = (elem->y > elem->sizey) ? elem->sizey : elem->y;
		return (1);
	}
	return (0);
}
