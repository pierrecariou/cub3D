/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:21:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/07/27 02:29:00 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	count_map(map_coor *coor, map_list *elem)
{
	int			lines;
	map_coor	*cp;

	lines = 0;
	cp = coor;
	while (cp)
	{
		lines++;
		cp = cp->next;
	}
	elem->lines = lines;
}

int 	check_map(map_list *elem)
{
	int i;
	int k;
	int lp;
	int ln;
	int l;
	int c;

	i = 0;
	k = 0;
	c = 0;
	while (elem->map[i])
	{
		k = ft_strlen(elem->map[i]) - 1;
		while (elem->map[i][k] == ' ')
			k--;
		if (elem->map[i][k] != '1')
			return (1);
		i++;
	}
	if (i < 3)
		return (3);
	i = 0;
	k = 0;
	while (elem->map[i])
	{
		while (elem->map[i][k])
		{
			if ((elem->map[i][k] == ' ' && elem->map[i][k + 1] && (elem->map[i][k + 1] != ' ' && elem->map[i][k + 1] != '1')) || (elem->map[i][k] == ' ' && k != 0 && (elem->map[i][k - 1] != ' ' && elem->map[i][k - 1] != '1')))
				return (1);
			if ((elem->map[i][k] == ' ' && elem->map[i + 1] && elem->map[i + 1][k] && (elem->map[i + 1][k] != ' ' && elem->map[i + 1][k] != '1')) || (elem->map[i][k] == ' ' && i != 0 && elem->map[i - 1][k] && (elem->map[i - 1][k] != ' ' && elem->map[i - 1][k] != '1')))
				return (1);
			k++;
		}
		k = 0;
		i++;
	}
	i = 0;
	k = 0;
	while (elem->map[i])
	{
		if (i == 0)
			l = ft_strlen(elem->map[i + 1]);
		else if (!elem->map[i + 1])
			l = ft_strlen(elem->map[i - 1]);
		else
		{
			lp = ft_strlen(elem->map[i - 1]);
			ln = ft_strlen(elem->map[i + 1]);
			l = lp <= ln ? lp : ln;
		}
		while (elem->map[i][k])
		{
			if (elem->map[i][k] == ' ')
				elem->map[i][k] = '1';
			if (elem->map[i][k] == 'N' || elem->map[i][k] == 'W' || elem->map[i][k] == 'S' || elem->map[i][k] == 'E')
				c++;
			if ((i == 0 || !elem->map[i + 1]) && elem->map[i][k] != '1')
				return (1);
			if (k > l - 1 && elem->map[i][k] != '1')
				return (1);
			k++;
		}
		k = 0;
		i++;
	}
	if (c == 0)
		return (4);
	if (c > 1)
		return (2);
	return (0);
}

int		create_map(map_coor *coor, map_list *elem)
{
	map_coor	*cp;
	int			i;
	int			k;
	int 		length;

	i = 0;
	k = 0;
	cp = coor;
	count_map(coor, elem);
	elem->map = malloc(sizeof(char *) * (elem->lines + 1));
	while (k < elem->lines)
	{
		length = ft_strlen(cp->line);
		elem->map[k] = malloc(length + 1);
		while (i < length)
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
	return (check_map(elem));
}

int		map_c(map_list *elem, char *line, int i, int k)
{
	int l;

	l = 0;
	if (line[0] == 'C' && line[1] == ' ')
	{
		while (line[i] == ' ')
			i++;
		while (line[i])
		{
			if (!((elem->C)[l] = malloc(4)))
				return (0);
			while (line[i] != ',' && line[i])
			{
				if (k > 2 || !(ft_isdigit(line[i])))
					return (0);
				(elem->C)[l][k] = line[i];
				k++;
				i++;
			}
			(elem->C)[l][k] = 0;
			k = 0;
			l++;
			i++;
		}
		i = -1;
		while (++i < 3)
			elem->C_color[i] = ft_atoi(elem->C[i]);
		return (1);
	}
	else
		return (0);
}

int		map_f(map_list *elem, char *line, int i, int k)
{
	int l;

	l = 0;
	if (line[0] == 'F' && line[1] == ' ')
	{
		while (line[i] == ' ')
			i++;
		while (line[i])
		{
			if (!((elem->F)[l] = malloc(4)))
				return (0);
			while (line[i] != ',' && line[i])
			{
				if (k > 2 || !(ft_isdigit(line[i])))
					return (0);
				(elem->F)[l][k] = line[i];
				k++;
				i++;
			}
			(elem->F)[l][k] = 0;
			k = 0;
			l++;
			i++;
		}
		i = -1;
		while (++i < 3)
			elem->F_color[i] = ft_atoi(elem->F[i]);
		return (1);
	}
	else
		return (0);
}

int		map_s(map_list *elem, char *line, int i, int k)
{
	if (line[0] == 'S' && line[1] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(elem->S = malloc(ft_strlen(line) - i + 1)))
			return (0);
		while (line[i] != ' ' && line[i])
		{
			(elem->S)[k] = line[i];
			k++;
			i++;
		}
		(elem->S)[k] = 0;
		return (1);
	}
	else
		return (0);
}
