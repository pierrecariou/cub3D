/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:21:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/02/28 15:13:08 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	count_map(map_coor *coor, map_list *elem)
{
	int			lines;
	int			length;
	map_coor	*cp;

	lines = 0;
	length = 0;
	cp = coor;
	while ((coor->line)[length])
		length++;
	while (cp)
	{
		lines++;
		cp = cp->next;
	}
	elem->lines = lines;
	elem->length = length;
}

void	create_map(map_coor *coor, map_list *elem)
{
	map_coor	*cp;
	int			i;
	int			k;

	i = 0;
	k = 0;
	cp = coor;
	count_map(coor, elem);
	elem->map = malloc(sizeof(char *) * (elem->lines + 1));
	while (k < elem->lines)
	{
		elem->map[k] = malloc(elem->length + 1);
		while (i < elem->length)
		{
			elem->map[k][i] = (cp->line)[i];
			i++;
		}
		elem->map[k][i] = 0;
		i = 0;
		k++;
		cp = cp->next;
	}
	elem->map[k] = 0;
}

void	map_c(map_list *elem, char *line, int i, int k)
{
	int l;

	l = 0;
	if (line[0] == 'C' && line[1] == ' ')
	{
		while (line[i])
		{
			if (!((elem->C)[l] = malloc(4)))
				return ;
			while (line[i] != ',' && line[i])
			{
				(elem->C)[l][k] = line[i];
				k++;
				i++;
			}
			(elem->C)[l][k] = 0;
			k = 0;
			l++;
			i++;
		}
	}
}

void	map_f(map_list *elem, char *line, int i, int k)
{
	int l;

	l = 0;
	if (line[0] == 'F' && line[1] == ' ')
	{
		while (line[i])
		{
			if (!((elem->F)[l] = malloc(4)))
				return ;
			while (line[i] != ',' && line[i])
			{
				(elem->F)[l][k] = line[i];
				k++;
				i++;
			}
			(elem->F)[l][k] = 0;
			k = 0;
			l++;
			i++;
		}
	}
}

void	map_s(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'S' && line[1] == ' ')
	{
		if (!(elem->S = malloc(ft_strlen(line) - 1)))
			return ;
		while (line[i] != ' ' && line[i])
		{
			(elem->S)[k] = line[i];
			k++;
			i++;
		}
		(elem->S)[k] = 0;
	}
}
