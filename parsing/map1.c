/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:19:36 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 00:19:38 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	count_map(t_coor *coor, t_map *elem)
{
	int		lines;
	t_coor	*cp;

	lines = 0;
	cp = coor;
	while (cp)
	{
		lines++;
		cp = cp->next;
	}
	elem->lines = lines;
}

int		length_lineba(t_map *elem, int i)
{
	int l;
	int lp;
	int ln;

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
	return (l);
}
