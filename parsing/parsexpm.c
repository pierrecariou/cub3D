/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:26:09 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:25:42 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		map_s(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'S' && line[1] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->s = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->s)[k] = line[i];
			k++;
			i++;
		}
		(elem->s)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_ea(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->ea = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->ea)[k] = line[i];
			k++;
			i++;
		}
		(elem->ea)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_no(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->no = malloc(ft_strlen(line) - i + 2)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->no)[k] = line[i];
			k++;
			i++;
		}
		(elem->no)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_we(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->we = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->we)[k] = line[i];
			k++;
			i++;
		}
		(elem->we)[k] = 0;
		return (1);
	}
	else
		return (0);
}

int		map_so(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->so = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->so)[k] = line[i];
			k++;
			i++;
		}
		(elem->so)[k] = 0;
		return (1);
	}
	else
		return (0);
}
