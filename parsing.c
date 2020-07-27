/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:14:32 by pcariou           #+#    #+#             */
/*   Updated: 2020/07/20 22:22:49 by pcariou          ###   ########.fr       */
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

int		map_x_y(map_list *elem, char *line, int i, int k)
{
	char	*x;
	char	*y;

	if (line[0] == 'R' && line[1] == ' ')
	{
		if (!(x = malloc(5)))
			return (0);
		if (!(y = malloc(5)))
			return (0);
		while (line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
		{
			if (!(ft_isdigit(line[i])))
			{
				free(x);
				free(y);
				return(0);
			}
			x[k] = line[i];
			k++;
			i++;
		}
		x[k] = 0;
		elem->x = ft_atoi(x);
		while (line[i] == ' ')
			i++;
		k = 0;
		while (line[i] && line[i] != ' ')
		{
			if (!(ft_isdigit(line[i])))
			{
				free(x);
				free(y);
				return (0);
			}
			y[k] = line[i];
			k++;
			i++;
		}
		y[k] = 0;
		elem->y = ft_atoi(y);
		free(x);
		free(y);
		return (1);
	}
	else
		return (0);
}
