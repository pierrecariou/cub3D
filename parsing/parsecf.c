/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:30:12 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 00:30:16 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		c_fill(t_map *elem, char *line, int i, int k)
{
	int l;

	l = 0;
	while (line[i] && l < 3)
	{
		if (!((elem->c)[l] = malloc(4)))
			return (0);
		if (l > 0 && line[i - 1] != ',')
			return (0);
		while (line[i] != ',' && ft_isdigit(line[i]))
		{
			if (k == 3)
				return (0);
			(elem->c)[l][k] = line[i];
			k++;
			i++;
		}
		if (k == 0)
			return (0);
		(elem->c)[l][k] = 0;
		k = 0;
		l++;
		i++;
	}
	return (l < 3) ? 0 : 1;
}

int		map_c(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'C' && line[1] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(c_fill(elem, line, i, k)))
			return (-100);
		i = -1;
		while (++i < 3)
			elem->c_color[i] = ft_atoi(elem->c[i]);
		return (1);
	}
	else
		return (0);
}

int		f_fill(t_map *elem, char *line, int i, int k)
{
	int l;

	l = 0;
	while (line[i] && l < 3)
	{
		if (!((elem->f)[l] = malloc(4)))
			return (0);
		if (l > 0 && line[i - 1] != ',')
			return (0);
		while (line[i] != ',' && ft_isdigit(line[i]))
		{
			if (k == 3)
				return (0);
			(elem->f)[l][k] = line[i];
			k++;
			i++;
		}
		if (k == 0)
			return (0);
		(elem->f)[l][k] = 0;
		k = 0;
		l++;
		i++;
	}
	return (l < 3) ? 0 : 1;
}

int		map_f(t_map *elem, char *line, int i, int k)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (!(f_fill(elem, line, i, k)))
			return (-100);
		i = -1;
		while (++i < 3)
			elem->f_color[i] = ft_atoi(elem->f[i]);
		return (1);
	}
	else
		return (0);
}
