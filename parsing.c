/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:14:32 by pcariou           #+#    #+#             */
/*   Updated: 2020/07/27 16:39:18 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int		map_ea(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->EA = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->EA)[k] = line[i];
			k++;
			i++;
		}
		(elem->EA)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_we(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->WE = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->WE)[k] = line[i];
			k++;
			i++;
		}
		(elem->WE)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_so(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->SO = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->SO)[k] = line[i];
			k++;
			i++;
		}
		(elem->SO)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_no(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->NO = malloc(ft_strlen(line) - i + 2)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->NO)[k] = line[i];
			k++;
			i++;
		}
		(elem->NO)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		x_y_fill(map_list *elem, char *line, int i, char *x_y)
{
	int		k;
	char	c;

	k = 0;
	c = (i == 2) ? 'x' : 'y';
	while (line[i] == ' ')
		i++;
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

int		map_x_y(map_list *elem, char *line, int i)
{
	char	*x;
	char	*y;

	if (line[0] == 'R' && line[1] == ' ')
	{
		if (!(x = malloc(5)))
			return (0);
		if (!(y = malloc(5)))
			return (0);
		if (x_y_fill(elem, line, i, y) == 0 ||
			x_y_fill(elem, line, x_y_fill(elem, line, i, y), y) == 0)
		{
			free(x);
			free(y);
			return (0);
		}
		free(x);
		free(y);
		return (1);
	}
	else
		return (0);
}
