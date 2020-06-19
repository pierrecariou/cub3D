/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:31:53 by pcariou           #+#    #+#             */
/*   Updated: 2020/06/18 19:03:45 by pcariou          ###   ########.fr       */
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
	double dist;
	double height;
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
	char 	**F;
	char	**C;
	unsigned int		*F_color;
	unsigned int		*C_color;
	int		lines;
	//int 	length;
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
	double 	*sizes;
	int		cubs;
	int		count_s;
	void	*ptr[2];
	int		*key_down;
	//int		b;
	int		sizex;
	int		sizey;
	data_s  *sprites;
	data	t1;
	data	t2;
	data	t3;
	data	t4;
	data	sprite;
	data	screen;
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
int		read_coor(map_coor *coor, char *line);
int		read_file(map_list	*elem, map_coor *coor);
int		create_map(map_coor *coor, map_list *elem);
double	finding_h(map_list *elem);
void	map_infos1(map_list *elem, int x, int y, int k);
double	finding_v(map_list *elem);
void	new_texture(map_list *elem);
void    choose_dist(double h, double v, int i, map_list *elem);
void    trace_rays(map_list *elem);
void	key_action1(map_list *elem);
void	call_all_rays(map_list *elem);
void	init_dist_ratios(map_list *elem);
void	map_infos(map_list *elem);
void    close_win(map_list *elem);
int		map_out(map_list *elem, unsigned int *map, int v);
void	computation_v(map_list *elem, unsigned int *map, double *coor);

#endif
