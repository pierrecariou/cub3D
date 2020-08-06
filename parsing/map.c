/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:16:40 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:25:12 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		check_map_close(t_map *elem, int k, int i)
{
	int c;
	int l;

	c = 0;
	while (elem->map[i])
	{
		l = length_lineba(elem, i);
		while (elem->map[i][k])
		{
			if (elem->map[i][k] == ' ')
				elem->map[i][k] = '1';
			if (elem->map[i][k] == 'N' || elem->map[i][k] == 'W' ||
				elem->map[i][k] == 'S' || elem->map[i][k] == 'E')
				c++;
			if ((i == 0 || !elem->map[i + 1]) && elem->map[i][k] != '1')
				return (-1);
			if (k > l - 1 && elem->map[i][k] != '1')
				return (-1);
			k++;
		}
		k = 0;
		i++;
	}
	return (c);
}

int		check_map_holes(t_map *elem, int i, int k)
{
	while (elem->map[i])
	{
		while (elem->map[i][k])
		{
			if ((elem->map[i][k] == ' ' && elem->map[i][k + 1] &&
				(elem->map[i][k + 1] != ' ' && elem->map[i][k + 1]
				!= '1')) || (elem->map[i][k] == ' ' && k != 0 &&
				(elem->map[i][k - 1] != ' ' && elem->map[i][k - 1] != '1')))
				return (1);
			if ((elem->map[i][k] == ' ' && elem->map[i + 1] && elem->map
				[i + 1][k] && (elem->map[i + 1][k] != ' ' && elem->map
				[i + 1][k] != '1')) || (elem->map[i][k] == ' ' && i != 0
				&& elem->map[i - 1][k] && (elem->map[i - 1][k] != ' ' &&
				elem->map[i - 1][k] != '1')))
				return (1);
			k++;
		}
		k = 0;
		i++;
	}
	return (0);
}

int		close_right(t_map *elem, int i, int k)
{
	while (elem->map[i])
	{
		k = ft_strlen(elem->map[i]) - 1;
		while (elem->map[i][k] == ' ')
			k--;
		if (elem->map[i][k] != '1')
			return (-1);
		i++;
	}
	return (i);
}

int		check_map(t_map *elem)
{
	int i;
	int k;

	i = 0;
	k = 0;
	i = close_right(elem, i, k);
	if (i == -1)
		return (1);
	if (i < 3)
		return (3);
	i = 0;
	if (check_map_holes(elem, i, k))
		return (1);
	k = check_map_close(elem, k, i);
	if (k == 0)
		return (4);
	if (k == -1)
		return (1);
	if (k > 1)
		return (2);
	return (0);
}

int		create_map(t_coor *coor, t_map *elem)
{
	t_coor		*cp;
	int			i;
	int			k;
	int			length;

	i = -1;
	k = 0;
	cp = coor;
	count_map(coor, elem);
	elem->map = malloc(sizeof(char *) * (elem->lines + 1));
	while (k < elem->lines)
	{
		length = ft_strlen(cp->line);
		elem->map[k] = malloc(length + 1);
		while (++i < length)
			elem->map[k][i] = (cp->line)[i];
		elem->map[k][i] = 0;
		i = -1;
		k++;
		cp = cp->next;
	}
	elem->map[k] = 0;
	return (check_map(elem));
}
