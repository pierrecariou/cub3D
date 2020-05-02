/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:31:53 by pcariou           #+#    #+#             */
/*   Updated: 2020/03/12 18:53:37 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 	r_list
{
	double x;
	double y;
	int cox;
	int coy;
	double dist;
	double height;
	double	x_begin;
	double	x_end;
	int		visible;
	double 	m;
	double 	p;
	double 	xl;
	double 	yl;
	double	xr;
	double	yr;
	double	dperp;
	double 	mxb;
	double	pxb;
	double	xz;
	double	yz;
	double ratio_h;
	double rad;
	double center;
	double left;
	double right;
}				data_s;

typedef struct	t_list
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		*data_img;
	int		width;
	int		height;
}				data;

typedef struct	s_list
{
	int		x;
	int		y;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
	char	**F;
	char	**C;
	int		lines;
	int 	length;
	double	rad;
	double	abr;
	double	cr;
	double 	posx;
	double 	posy;
	double	ratio_h;
	double	ratio_v;
	char	**map;
	double	*dist;
	double	*ratios;
	char	*orient;
	int		cubs;
	int		count_s;
	void	*ptr[2];
	int		*key_down;
	data_s  *sprites;
	data	t1;
	data	t2;
	data	t3;
	data	t4;
	data	sprite;
	int 	vh;
	int		vv;
	int		*countv;
	int		*counth;
	double m;
	double p;
}				map_list;

typedef struct	l_list
{
	char			*line;
	struct l_list	*next;

}				map_coor;

int		get_next_line(int fd, char **line);
int		ft_isdigit(int c);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
void	map_ea(map_list *elem, char *line, int i, int k);
void	map_we(map_list *elem, char *line, int i, int k);
void	map_so(map_list *elem, char *line, int i, int k);
void	map_no(map_list *elem, char *line, int i, int k);
void	map_x_y(map_list *elem, char *line, int i, int k);
void	map_c(map_list *elem, char *line, int i, int k);
void	map_f(map_list *elem, char *line, int i, int k);
void	map_s(map_list *elem, char *line, int i, int k);
void	lst_new(char *line_coor, map_coor *coor);
void	read_coor(map_coor *coor, char *line);
void	read_file(map_list	*elem, map_coor *coor);
void	create_map(map_coor *coor, map_list *elem);
double	finding_h(map_list *elem);

#endif
