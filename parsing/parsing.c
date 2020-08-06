/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:55:19 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 00:55:23 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		check_map_file(char **argv, int argc)
{
	int l;

	if (argc >= 2)
		l = ft_strlen(argv[1]);
	else
		return (-1);
	if (l > 4)
	{
		if (argv[1][l - 1] != 'b' || argv[1][l - 2] != 'u' ||
				argv[1][l - 3] != 'c' || argv[1][l - 4] != '.')
			return (-1);
	}
	else
		return (-1);
	return (0);
}

void	init(t_map *elem, int k)
{
	if (!(elem->e = malloc(sizeof(int) * 8)))
		return ;
	while (k < 8)
	{
		elem->e[k] = 0;
		k++;
	}
	if (!(elem->f = malloc(sizeof(char *) * 3)))
		return ;
	if (!(elem->c = malloc(sizeof(char *) * 3)))
		return ;
	if (!(elem->f_color = malloc(sizeof(unsigned int) * 3)))
		return ;
	if (!(elem->c_color = malloc(sizeof(unsigned int) * 3)))
		return ;
}

int		call_inits(t_map *elem, char *line, int *v)
{
	if (elem->e[0] == 0)
		v[4] += (elem->e[0] = map_x_y(elem, line, v[1]));
	if (elem->e[1] == 0)
		v[4] += (elem->e[1] = map_no(elem, line, v[1], v[2]));
	if (elem->e[2] == 0)
		v[4] += (elem->e[2] = map_so(elem, line, v[1], v[2]));
	if (elem->e[3] == 0)
		v[4] += (elem->e[3] = map_we(elem, line, v[1], v[2]));
	if (elem->e[4] == 0)
		v[4] += (elem->e[4] = map_ea(elem, line, v[1], v[2]));
	if (elem->e[5] == 0)
		v[4] += (elem->e[5] = map_s(elem, line, v[1], v[2]));
	if (elem->e[6] == 0)
		v[4] += (elem->e[6] = map_f(elem, line, v[1], v[2]));
	if (elem->e[7] == 0)
		v[4] += (elem->e[7] = map_c(elem, line, v[1], v[2]));
	return (v[4]);
}

int		call_gnl(t_map *elem, t_coor *coor, char *line, int *v)
{
	while (get_next_line(v[0], &line) == 1)
	{
		if (v[4] < 8)
		{
			if (check_repet(line) || check_repet1(line, elem))
			{
				free(line);
				return (6);
			}
			v[4] = call_inits(elem, line, v);
		}
		else if (v[4] == 8 && line[0] == 0)
			v[4] = 8;
		else
		{
			if ((v[3] = read_coor(coor, line)) != 0)
			{
				free(line);
				return (v[3]);
			}
			v[4]++;
		}
		free(line);
	}
	return (v[4] <= 8) ? 7 : 0;
}

/*
** v[0] = fd
** v[1] = i
** v[2] = k
** v[3] = r
** v[4] = elems
*/

int		read_file(t_map *elem, t_coor *coor, int argc, char **argv)
{
	char	*line;
	int		v[5];

	v[1] = 2;
	v[2] = 0;
	v[4] = 0;
	line = NULL;
	v[3] = 0;
	if ((check_map_file(argv, argc) == -1) ||
		((v[0] = open(argv[1], O_RDONLY)) == -1))
		return (10);
	init(elem, v[2]);
	if ((v[3] = call_gnl(elem, coor, line, v)) != 0)
		return (v[3]);
	v[3] = (check_rgb(elem->f_color)) ? 9 : 0;
	if (v[3] == 0)
		v[3] = (check_rgb(elem->c_color)) ? 9 : 0;
	return (v[3]);
}
