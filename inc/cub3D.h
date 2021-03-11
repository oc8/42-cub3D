/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:33:04 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/11 16:32:13 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define KEY_CTRL 256
# define KEY_MAJ 257

# include "mlx.h"
# include "libft.h"

# include <limits.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_mlx
{
	void	*ptr;
	void	*window;
	int		width;
	int		height;
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
	char	*ptr;
	int		*i_ptr;
	int		i;
}				t_line;

typedef struct	s_i
{
	int		x;
	int		y;
}				t_i; // unsigned

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
}				t_key;

typedef struct	s_sprite
{
	float	a;
	float	b;
	float	c;
	float	d;
	t_i		index;
}				t_sprite;

typedef struct	s_plan
{
	int				a;
	int				b;
	int				c;
	int				d;
	unsigned int	nbr;
	t_sprite		**sprite;
}				t_plan;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*pixels;
	int				width;
	int				height;
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
	float	t;
	char	flag;
	int		color_sprite;
	t_c		pixel;
}				t_dist;

typedef struct	s_axe
{
	char	axe;
	float	dir;
	int		pos;
	int		nbr_plan;
	float	*rs_plans_x;
	float	*rs_plans_y;
	float	*rs_plans;
}				t_axe;

// typedef struct	s_matrice
// {
// 	float	;
// }				t_matrice;

typedef struct	s_pars
{
	char		**map;
	t_i			nbr_map;
	t_plan		*plans_no;
	t_plan		*plans_so;
	t_plan		*plans_ea;
	t_plan		*plans_we;
	t_sprite	*plans_sprite;
	int			nbr_sprite;
	int			res_hor;
	int			res_ver;
	char		*path_we;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_sprite;
	int			col_floor;
	int			col_sky;
}				t_pars;

typedef struct	s_player
{
	float		speed;
	float		agl_hor;
	float		agl_vrt;
	t_c			pos;
	t_vector	*dir;
}				t_player;

typedef struct	s_ptr
{
	t_pars			*pars;
	t_player		player;
	t_list			*malloc_lst;
	t_list			*mlx_lst;
	t_img			sky;
	t_mlx			mlx;
	t_img			screen;
	t_img			we;
	t_img			no;
	t_img			so;
	t_img			ea;
	t_img			sprite;
	t_key			key;
	struct timeval	time;
	struct timeval	last_second;
	pthread_t		thread[THREAD];
	t_agl			agl;
	int				epars;
	float			*rs_plans_x;
	float			*rs_plans_y;
}				t_ptr;

typedef struct	s_thread
{
	t_ptr	*ptr;
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
	e_C = 256
}				t_e_pars;

t_plan			ft_new_plan(char x_y, int c);
int				ft_create_plan(t_ptr *ptr);
int				ft_parsing(char *path, t_ptr *ptr);
void			ft_parsing_map(t_ptr *ptr, char *line, int j, t_i *first_pos);
int				ft_malloc_map(t_ptr *ptr, char *path);
int				ft_check_map(t_ptr *ptr, char **map, int i, int j);
void			ft_create_plans_x(t_ptr *ptr);
void			ft_create_plans_y(t_ptr *ptr);

void			ft_edit_img(t_ptr *ptr);
unsigned int	ft_nearest(t_ptr *ptr, t_vector dir);
struct timeval	ft_time_now(void);
struct timeval	ft_time(t_ptr *ptr, char *str, int *count);

void			*ft_calloc_lst(t_ptr *ptr, size_t nbr, size_t size);
int				create_trgb(int t, int r, int g, int b);
int				ft_in_map(t_ptr *ptr, t_i coordinate);
void			ft_add_to_lst(t_ptr *ptr, void *add_ptr);
void			ft_lstclear_mlx(t_list **lst, int (*del)(void*, void*), t_ptr *ptr);

t_dist			ft_ray(t_ptr *ptr, t_plan *plans, t_vector dir, t_axe *axe);

int				ft_ray_sprite(t_ptr *ptr, t_vector dir, t_plan *plan, t_dist *dist);
void			ft_create_plan_sprite(t_ptr *ptr);
t_sprite		*ft_search_sprite(t_ptr *ptr, int y, int x);
void			ft_malloc_sprite(t_ptr *ptr);

void			ft_mlx_init(t_ptr *ptr);
int				ft_loop(t_ptr *ptr);
int				ft_mouse(int x, int y, t_ptr *ptr);
int				ft_key(int key, t_ptr *ptr);
int				ft_key_release(int key, t_ptr *ptr);

unsigned int	ft_nearest_wall(t_ptr *ptr, t_vector dir, t_dist x, t_dist y);

int				ft_quit_x(t_ptr *ptr);
void			ft_close(t_ptr *ptr, int error);

unsigned int	ft_wall_texture(t_c pixel, t_img img, char axe);
unsigned int	ft_sky_texture(t_ptr *ptr, float c1, float c2, char face);
unsigned int	ft_sprite_texture(t_ptr *ptr, t_img *sprite, t_c *pixel, t_i index);

#endif
