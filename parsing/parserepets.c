/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserepets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:51:51 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:25:31 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		check_repet1(char *line, t_map *elem)
{
	if ((line[0] == 'R' && line[1] == ' ' && elem->e[0] == 1) ||
		(line[0] == 'N' && line[1] == 'O' && line[2] == ' ' &&
		elem->e[1] == 1) || (line[0] == 'S' && line[1] == 'O' &&
		line[2] == ' ' && elem->e[2] == 1) || (line[0] == 'W' &&
		line[1] == 'E' && line[2] == ' ' && elem->e[3] == 1) ||
		(line[0] == 'E' && line[1] == 'A' && line[2] == ' ' &&
		elem->e[4] == 1) || (line[0] == 'S' && line[1] == ' ' &&
		elem->e[5] == 1) || (line[0] == 'F' && line[1] == ' ' &&
		elem->e[6] == 1) || (line[0] == 'C' && line[1] == ' ' &&
		elem->e[7] == 1))
		return (1);
	return (0);
}

int		check_repet(char *line)
{
	if (line[0] != 'R' && line[0] != 'N' && line[0] != 'S' &&
			line[0] != 'W' && line[0] != 'E' && line[0] != 'F' &&
			line[0] != 'C' && line[0])
		return (1);
	if ((line[0] == 'R' && line[1] != ' ') || (line[0] == 'F' && line[1] != ' ')
			|| (line[0] == 'S' && (line[1] != ' ' && line[1] != 'O')) ||
			(line[0] == 'S' && line[1] == 'O' && line[2] != ' ') ||
			(line[0] == 'W' && line[1] == 'E' && line[2] != ' ') ||
			(line[0] == 'W' && line[1] != 'E') ||
			(line[0] == 'E' && line[1] == 'A' && line[2] != ' ') ||
			(line[0] == 'E' && line[1] != 'A') ||
			(line[0] == 'N' && line[1] == 'O' && line[2] != ' ') ||
			(line[0] == 'N' && line[1] != 'O') ||
			(line[0] == 'C' && line[1] != ' '))
		return (1);
	return (0);
}
