/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:24:48 by pcariou           #+#    #+#             */
/*   Updated: 2020/06/11 15:17:58 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	lst_new(char *line_coor, map_coor	*coor)
{
	map_coor	*new_coor;

	if (!(coor->line))
	{
		coor->line = line_coor;
		coor->next = 0;
	}
	else
	{
		if (!(new_coor = malloc(16)))
			return ;
		new_coor->line = line_coor;
		new_coor->next = 0;
		while (coor->next)
			coor = coor->next;
		coor->next = new_coor;
	}
}

int		read_coor(map_coor *coor, char *line)
{
	int		i;
	int		k;
	char	*line_coor;

	i = 0;
	k = 0;
	while (line[k] == ' ')
		k++;
	if (line[k] == '1')
	{
		k = 0;
		if (!(line_coor = malloc(ft_strlen(line) + 1)))
			return (0);
		while (line[k])
		{
			if (line[k] == '1' || line[k] == '0' || line[k] == '2' ||
					line[k] == 'N' || line[k] == 'S' || line[k] == 'O' ||
					line[k] == 'E' || line[k] == ' ')
			{
				line_coor[i] = line[k];
				if (line_coor[i] == ' ')
					line_coor[i] = '1';
				i++;
			}
			k++;
		}
		if (line[k - 1] != '1')
			return (1);
		line_coor[i] = 0;
		lst_new(line_coor, coor);
	}
	else if (line[k] != 'R' && line[k] != 'N' && line[k] != 'S' && line[k] != 'W'
		&& line[k] != 'E' && line[k] != 'F' && line[k] != 'C' && line[0])
		return (1);
	return (0);
}

int		read_file(map_list	*elem, map_coor *coor)
{
	int			fd;
	char		*line;
	int			i;
	int			k;

	i = 2;
	k = 0;
	if (!(elem->F = malloc(sizeof(char *) * 3)))
		return (0);
	if (!(elem->C = malloc(sizeof(char *) * 3)))
		return (0);
	if (!(elem->F_color = malloc(sizeof(unsigned int) * 3)))
		return (0);
	if (!(elem->C_color = malloc(sizeof(unsigned int) * 3)))
		return (0);
	fd = open("./map.cub", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		map_x_y(elem, line, i, k);
		map_no(elem, line, i, k);
		map_so(elem, line, i, k);
		map_we(elem, line, i, k);
		map_ea(elem, line, i, k);
		map_s(elem, line, i, k);
		map_f(elem, line, i, k);
		map_c(elem, line, i, k);
		if (read_coor(coor, line) == 1)
			return (1);
		free(line);
	}
	return (0);
}
