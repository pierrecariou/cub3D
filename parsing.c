/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:14:32 by pcariou           #+#    #+#             */
/*   Updated: 2020/02/28 18:08:44 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	map_ea(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		i++;
		if (!(elem->EA = malloc(ft_strlen(line) - 2)))
			return ;
		while (line[i] != ' ' && line[i])
		{
			(elem->EA)[k] = line[i];
			k++;
			i++;
		}
		(elem->EA)[k] = 0;
	}
}

void	map_we(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		i++;
		if (!(elem->WE = malloc(ft_strlen(line) - 2)))
			return ;
		while (line[i] != ' ' && line[i])
		{
			(elem->WE)[k] = line[i];
			k++;
			i++;
		}
		(elem->WE)[k] = 0;
	}
}

void	map_so(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		i++;
		if (!(elem->SO = malloc(ft_strlen(line) - 2)))
			return ;
		while (line[i] != ' ' && line[i])
		{
			(elem->SO)[k] = line[i];
			k++;
			i++;
		}
		(elem->SO)[k] = 0;
	}
}

void	map_no(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		i++;
		if (!(elem->NO = malloc(ft_strlen(line) - 2)))
			return ;
		while (line[i] != ' ' && line[i])
		{
			(elem->NO)[k] = line[i];
			k++;
			i++;
		}
		(elem->NO)[k] = 0;
	}
}

void	map_x_y(map_list *elem, char *line, int i, int k)
{
	char	*x;
	char	*y;

	x = malloc(5);
	y = malloc(5);
	if (line[0] == 'R' && line[1] == ' ')
	{
		while (ft_isdigit(line[i]) == 1)
		{
			x[k] = line[i];
			k++;
			i++;
		}
		x[k] = 0;
		elem->x = ft_atoi(x);
		while (line[i] == ' ')
			i++;
		k = 0;
		while (ft_isdigit(line[i]) == 1)
		{
			y[k] = line[i];
			k++;
			i++;
		}
		y[k] = 0;
		elem->y = ft_atoi(y);
	}
}
