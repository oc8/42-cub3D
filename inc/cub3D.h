/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:10:09 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 15:19:09 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**	min 1
*/
# define S_W 1.8
# define S_S 2.5
# define SPEED 4
# define SPEED_S 1
# define SENSIBILITY 1
# define FOV 80
# define THREAD 4

# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_ESC 53
# define KEY_W 13
# define KEY_AL 123
# define KEY_AR 124
# define KEY_AU 126
# define KEY_AD 125
# define KEY_UP 18
# define KEY_DOWN 19
# define KEY_M 46
# define KEY_CTRL 256
# define KEY_MAJ 257
# define KEY_SPACE 49

# include "mlx.h"
# include "libft.h"

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <pthread.h>
# include <sys/time.h>

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct	s_c
{
	float	x;
	float	y;
	float	z;
}				t_c;

typedef struct	s_line
{
	char			*ptr;
	unsigned int	*i_ptr;
	unsigned int	i;
}				t_line;

typedef struct	s_i
{
	unsigned int	x;
	unsigned int	y;
}				t_i;

typedef struct	s_i_singed
{
	int	x;
	int	y;
	int	z;
}				t_i_signed;

typedef struct	s_key
{
	char	al;
	char	ar;
	char	w;
	char	s;
	char	a;
	char	d;
	char	ad;
	char	au;
	char	up;
	char	down;
	char	m;
	char	ctrl;
	char	maj;
	char	space;
}				t_key;

typedef struct	s_sprite
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	rs;
	t_c		pos;
	float	t;
}				t_sprite;

typedef struct	s_plan
{
	int		a;
	int		b;
	int		c;
	int		d;
	float	rs;
	float	t;
}				t_plan;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*pixels;
	int				w;
	int				h;
	int				bpp;
	int				s_l;
	int				endian;
}				t_img;

typedef struct	s_agl
{
	float	cos_hor;
	float	cos_vrt;
	float	sin_hor;
	float	sin_vrt;
}				t_agl;

typedef struct	s_dist
{
	float			t;
	unsigned int	color;
	t_c				pixel;
}				t_dist;

typedef struct	s_axe
{
	char	axe;
	float	dir;
	int		pos;
	int		nbr_plan;
}				t_axe;

typedef struct	s_pars
{
	char			**map;
	t_i				nbr_map;
	t_plan			*plans_no;
	t_plan			*plans_so;
	t_plan			*plans_ea;
	t_plan			*plans_we;
	t_sprite		*plans_sprite;
	unsigned int	nbr_sprite;
	t_i				finish;
	char			*path_we;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_sprite;
	int				col_floor;
	int				col_sky;
}				t_pars;

typedef struct	s_player
{
	float		speed;
	float		agl_hor;
	float		agl_vrt;
	t_c			pos;
	t_vector	*dir;
}				t_player;

typedef struct	s_cub
{
	t_pars			*pars;
	t_player		player;
	t_list			*malloc_lst;
	t_list			*mlx_lst;
	t_mlx			mlx;
	t_img			scr;
	t_img			we;
	t_img			no;
	t_img			so;
	t_img			ea;
	t_img			sprite;
	t_img			sky;
	t_img			floor;
	t_img			win;
	t_img			save;
	t_key			key;
	int				nbr_life;
	float			fov;
	char			flag_save;
	char			flag_win;
	struct timeval	time;
	struct timeval	last_second;
	pthread_t		thread[THREAD];
	t_agl			agl;
	int				epars;
	float			delta;
}				t_cub;

typedef struct	s_thread
{
	t_cub	*cub;
	int		id;
}				t_thread;

typedef enum	e_pars
{
	e_FIRST_DIR = 1,
	e_R = 2,
	e_NO = 4,
	e_SO = 8,
	e_WE = 16,
	e_EA = 32,
	e_S = 64,
	e_F = 128,
	e_C = 256,
	e_FINISH = 512
}				t_e_pars;

/*
**	parsing
*/
t_plan			ft_new_plan(char x_y, int c);
int				ft_parsing(char *path, t_cub *cub);
void			ft_parsing_map(t_cub *cub, char *line, int j);
int				ft_malloc_map(t_cub *cub, char *path);
char			ft_check_map(t_cub *cub, char **map, int i, int j);
void			ft_malloc_sprite(t_cub *cub);
int				ft_atoi_nbr(t_cub *cub, char *line, unsigned int *i);
char			*ft_copy_str(t_cub *cub, char *line, unsigned int *i);
int				ft_atoi_color_util(t_cub *cub, char *line, unsigned int *i, int flag);
int				ft_atoi_color(t_cub *cub, char *line, unsigned int *i);
int				ft_parsing_criteria(t_cub *cub, t_line line);

/*
**	plan
*/
int				ft_create_plan(t_cub *cub);
void			ft_create_plans_x(t_cub *cub);
void			ft_create_plans_y(t_cub *cub);
void			ft_create_plan_sprite(t_cub *cub);

/*
**	display
*/
void			ft_edit_img(t_cub *cub);
struct timeval	ft_time_now(void);
struct timeval	ft_time(t_cub *cub, char *str, int *count);

/*
**	move
*/
t_vector		ft_rotation(t_vector dir, const t_agl *agl);
void			ft_check_new_pos(t_cub *cub, t_c new_pos);
void			ft_pos_sprite(t_cub *cub);
void			ft_check_new_pos_sprite(t_cub *cub, t_sprite *p);
void			ft_mlx_init(t_cub *cub);
int				ft_loop(t_cub *cub);
int				ft_mouse(int x, int y, t_cub *cub);
int				ft_key(int key, t_cub *cub);
int				ft_key_release(int key, t_cub *cub);
void			ft_check_wall(t_cub *cub, t_i new_pos_i, t_c new_pos, t_c *pos);
void			ft_fly(t_cub *cub);
void			ft_fly_move(t_cub *cub, t_dist dist);

/*
**	raycasting
*/
void			ft_ray_screen(t_cub *cub);
t_dist			ft_ray_x(t_cub *cub, t_vector dir, t_plan *p);
t_dist			ft_ray_y(t_cub *cub, t_vector dir, t_plan *p);
float			ft_calc_dist(t_plan *p, t_vector dir);
void			ft_threads(t_cub *cub);
float			ft_ray_sprite(t_cub *cub, t_vector dir, t_dist *dist);
float			ft_calc_rs(t_cub *cub, t_plan *p);
void			ft_before_calc(t_cub *cub);
t_dist			ft_top(t_cub *cub, t_vector dir);
t_dist			ft_floor(t_cub *cub, t_vector dir);

/*
**	nearest
*/
t_dist			ft_nearest(t_cub *cub, t_vector dir);

/*
**	texture
*/
unsigned int	ft_wall_texture(t_c pixel, t_img img, char axe);
unsigned int	ft_sprite_texture(t_cub *cub, t_img *img, t_c *pixel, \
	t_sprite *sprite);
unsigned int	ft_floor_texture(t_cub *cub, t_c *pixel);
unsigned int	ft_top_texture(t_cub *cub, t_dist *dist);
unsigned int	ft_skybox(t_cub *cub, t_vector dir);
unsigned int	ft_sky_texture_up(t_cub *cub, float map, t_vector *dir);
unsigned int	ft_sky_texture_1(t_cub *cub, float map, t_vector *dir);
unsigned int	ft_sky_texture_2(t_cub *cub, float map, t_vector *dir);
unsigned int	ft_sky_texture_3(t_cub *cub, float map, t_vector *dir);
unsigned int	ft_sky_texture_4(t_cub *cub, float map, t_vector *dir);
unsigned int	ft_sky_texture_down(t_cub *cub, float map, t_vector *dir);

/*
**	utils
*/
int				ft_skip_spaces(char *line, unsigned int i);
void			*ft_calloc_lst(t_cub *cub, size_t nbr, size_t size);
int				ft_init_struct(t_cub *cub);
int				create_trgb(int t, int r, int g, int b);
int				ft_in_map(t_cub *cub, t_i coordinate);
void			ft_add_to_lst(t_cub *cub, void *add_ptr);
void			ft_lstclear_mlx(t_list **lst, int (*del)(void*, void*), \
	t_cub *cub);
void			ft_save_bmp(const char *filename, t_cub *cub);
char			ft_check_index_map(t_cub *cub, t_i map);
unsigned int	ft_is_sprite(t_cub *cub, t_c *pixel, t_vector dir, t_sprite *sprite);

/*
**	close
*/
int				ft_quit_x(t_cub *cub);
void			ft_close(t_cub *cub, int error, const char *str);

#endif
