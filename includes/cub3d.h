/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 01:33:51 by pcariou           #+#    #+#             */
/*   Updated: 2020/08/05 01:58:21 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	double			height;
	double			rad;
	double			center;
	double			left;
	double			right;
}					t_spri;

typedef struct		s_texture
{
	void			*img_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				*data_img;
	int				width;
	int				height;
}					t_text;

typedef struct		s_list
{
	int				*e;
	int				argc;
	char			*argv;
	int				x;
	int				y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	char			**f;
	char			**c;
	unsigned int	*f_color;
	unsigned int	*c_color;
	int				lines;
	double			rad;
	double			abr;
	double			cr;
	double			posx;
	double			posy;
	double			ratio_h;
	double			ratio_v;
	char			**map;
	double			*dist;
	double			*ratios;
	char			*orient;
	double			*sizes;
	int				cubs;
	int				count_s;
	void			*ptr[2];
	int				*key_down;
	int				sizex;
	int				sizey;
	t_spri			*sprites;
	t_text			t1;
	t_text			t2;
	t_text			t3;
	t_text			t4;
	t_text			sprite;
	t_text			screen;
}					t_map;

typedef struct		s_coor
{
	char			*line;
	struct s_coor	*next;
}					t_coor;

int					get_next_line(int fd, char **line);
int					ft_isdigit(int c);
int					ft_strlen(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
void				ft_putnbr_fd(int n, int fd);
int					map_ea(t_map *elem, char *line, int i, int k);
int					map_we(t_map *elem, char *line, int i, int k);
int					map_so(t_map *elem, char *line, int i, int k);
int					map_no(t_map *elem, char *line, int i, int k);
int					map_x_y(t_map *elem, char *line, int i);
int					map_c(t_map *elem, char *line, int i, int k);
int					map_f(t_map *elem, char *line, int i, int k);
int					map_s(t_map *elem, char *line, int i, int k);
void				lst_new(char *line_coor, t_coor *coor);
int					read_coor(t_coor *coor, char *line);
int					read_file(t_map	*elem, t_coor *coor, int argc, char **argv);
int					create_map(t_coor *coor, t_map *elem);
double				finding_h(t_map *elem);
void				map_infos1(t_map *elem, int x, int y, int k);
double				finding_v(t_map *elem);
int					new_texture(t_map *elem);
void				choose_dist(double h, double v, int i, t_map *elem);
void				trace_rays(t_map *elem);
void				key_action1(t_map *elem);
void				call_all_rays(t_map *elem);
void				init_dist_ratios(t_map *elem);
void				map_infos(t_map *elem);
void				close_win(t_map *elem);
int					map_out(t_map *elem, unsigned int *map, int v);
void				computation_v(t_map *elem, unsigned int *map, double *coor);
int					save(t_map *elem);
void				save_bmp(t_map *elem);
int					close_w(t_map *elem);
void				fill_argv(char **argv, int argc, t_map *elem);
int					loop(t_map *elem);
void				key_action(t_map *elem);
int					key_press_hook(int key, t_map *elem);
int					key_release_hook(int key, t_map *elem);
int					close_w(t_map *elem);
void				dist_player(t_map *elem);
void				insert_sprite(t_map *elem, int *data_bi, int j);
void				color_c(t_map *elem, char *data_img, int *c);
void				color_f(t_map *elem, char *data_img, int *c);
void				insert_texture(t_map *elem, int *p, int *data_bi, int i);
int					length_lineba(t_map *elem, int i);
void				count_map(t_coor *coor, t_map *elem);
int					check_repet(char *line);
int					check_repet1(char *line, t_map *elem);
int					check_rgb(unsigned int *color);

#endif
