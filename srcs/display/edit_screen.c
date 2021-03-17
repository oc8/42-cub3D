/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:47:07 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/17 17:09:58 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_put_pixels(t_ptr *ptr, unsigned int *screen, int thread_nb)
{
	int				x;
	int				y;
	unsigned int	color;

	y = (ptr->mlx.h / THREAD) * thread_nb;
	while (y < (ptr->mlx.h / THREAD) * (thread_nb + 1))
	{
		x = 0;
		while (x < ptr->mlx.w)
		{
			color = ft_nearest(ptr, ft_rotation(ptr->player.dir[y * \
				ptr->mlx.w + x], &ptr->agl, ptr));
			if ((y * (int)(ptr->screen.s_l * 0.25) + x >= 0))
				screen[y * (int)(ptr->screen.s_l * 0.25) + x] = color;
			x++;
		}
		y++;
	}
}

static void	ft_put_4_pixels(t_ptr *ptr, unsigned int *screen, int thread_nb)
{
	int				x;
	int				y;
	unsigned int	color;

	y = (ptr->mlx.h / THREAD) * thread_nb;
	while (y < (ptr->mlx.h / THREAD) * (thread_nb + 1))
	{
		x = 0;
		while (x < ptr->mlx.w)
		{
			color = ft_nearest(ptr, ft_rotation(ptr->player.dir[y *\
				ptr->mlx.w + x], &ptr->agl, ptr));
			if ((y * (int)(ptr->screen.s_l * 0.25) + x >= 0))
			{
				screen[y * (int)(ptr->screen.s_l * 0.25) + x] = color;
				screen[y * (int)(ptr->screen.s_l * 0.25) + (x + 1)] = color;
				screen[(y + 1) * (int)(ptr->screen.s_l * 0.25) +\
					(x + 1)] = color;
				screen[(y + 1) * (int)(ptr->screen.s_l * 0.25) + x] = color;
			}
			x += 2;
		}
		y += 2;
	}
}

void		*ft_thread(void *work)
{
	t_ptr			*ptr;
	t_thread		*wptr;

	wptr = (t_thread*)work;
	ptr = (t_ptr*)wptr->ptr;
	if (ptr->mlx.w > 500 || ptr->mlx.h > 500)
		ft_put_4_pixels(ptr, ptr->screen.pixels, wptr->id);
	else
		ft_put_pixels(ptr, ptr->screen.pixels, wptr->id);
	return (ptr);
}

static void	ft_threads(t_ptr *ptr)
{
	t_thread	thread[THREAD];
	int			i;

	i = -1;
	while (++i < THREAD)
	{
		thread[i] = (t_thread){ptr, i};
		if (pthread_create(&ptr->thread[i], NULL, &ft_thread, (void*)&thread[i]))
			ft_close(ptr, 7);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(ptr->thread[i], NULL);
}

static void	ft_before_calc_plans(t_ptr *ptr, t_plan *p1, t_plan *p2, int nbr)
{
	int		i;
	t_c		pos;

	pos = ptr->player.pos;
	i = -1;
	while (++i < nbr)
	{
		if (p1[i].d)
			p1[i].rs = ft_calc_rs(ptr, &p1[i]);
		if (p2[i].d)
			p2[i].rs = ft_calc_rs(ptr, &p2[i]);
	}
}

static void	ft_before_calc(t_ptr *ptr)
{
	t_agl	agl;

	agl.cos_hor = cos(ptr->player.agl_hor);
	agl.sin_hor = sin(ptr->player.agl_hor);
	agl.cos_vrt = cos(ptr->player.agl_vrt);
	agl.sin_vrt = sin(ptr->player.agl_vrt);
	ptr->agl = agl;
	ft_before_calc_plans(ptr, ptr->pars->plans_so, \
		ptr->pars->plans_no, ptr->pars->nbr_map.y);
	ft_before_calc_plans(ptr, ptr->pars->plans_ea, \
		ptr->pars->plans_we, ptr->pars->nbr_map.x);
}

void	ft_edit_img(t_ptr *ptr)
{
	char		fps_str[11];
	char		life_str[5];
	static int	count_fps = 0;

	ptr->time = ft_time(ptr, fps_str, &count_fps);
	if (ptr->nbr_life <= 0)
		ft_close(ptr, -1);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, ptr->mlx.win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, ptr->screen.ptr);
	ft_before_calc(ptr);
	ft_threads(ptr);
	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.win, ptr->screen.ptr, 0, 0);
	mlx_string_put(ptr->mlx.ptr, ptr->mlx.win, 15, 20, 0xffffff, fps_str);
	sprintf(life_str, "%d%%", ptr->nbr_life);
	mlx_string_put(ptr->mlx.ptr, ptr->mlx.win, 15, 40, 0xff0000, life_str);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, ptr->mlx.win);
	count_fps++;
}
