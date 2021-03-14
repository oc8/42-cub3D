/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:47:07 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/14 17:53:42 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** fontion matrice
*/
static t_vector	ft_rotation(t_vector dir, const t_agl *agl, t_ptr *ptr)
{
	t_vector	m_z;
	t_vector	m_x;

	if (ptr->player.agl_hor >= M_PI)
		ptr->player.agl_hor -= 2 * M_PI;
	else if (ptr->player.agl_hor <= -M_PI)
		ptr->player.agl_hor += 2 * M_PI;
	m_x.x = dir.x;
	m_x.y = agl->cos_vrt * dir.y - agl->sin_vrt * dir.z;
	m_x.z = agl->sin_vrt * dir.y + agl->cos_vrt * dir.z;
	m_z.x = agl->cos_hor * m_x.x - agl->sin_hor * m_x.y;
	m_z.y = agl->sin_hor * m_x.x + agl->cos_hor * m_x.y;
	m_z.z = m_x.z;
	return (m_z);
}

static void	ft_put_pixels(t_ptr *ptr, unsigned int *screen, int thread_nb)
{
	int				x;
	int				y;
	unsigned int	color;

	y = (ptr->mlx.height / THREAD) * thread_nb;
	while (y < (ptr->mlx.height / THREAD) * (thread_nb + 1))
	{
		x = 0;
		while (x < ptr->mlx.width)
		{
			color = ft_nearest(ptr, ft_rotation(ptr->player.dir[y * \
				ptr->mlx.width + x], &ptr->agl, ptr));
			if ((y * (int)(ptr->screen.s_l * 0.25) + x >= 0))
			{
				screen[y * (int)(ptr->screen.s_l * 0.25) + x] = color;
				screen[y * (int)(ptr->screen.s_l * 0.25) + (x + 1)] = color;
				screen[(y + 1) * (int)(ptr->screen.s_l * 0.25) + \
					(x + 1)] = color;
				screen[(y + 1) * (int)(ptr->screen.s_l * 0.25) + x] = color;
			}
			x += 2;
		}
		y += 2;
	}
}

void	*ft_thread(void *work)
{
	t_ptr			*ptr;
	t_thread		*wptr;

	wptr = (t_thread*)work;
	ptr = (t_ptr*)wptr->ptr;
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
		pthread_create(&ptr->thread[i], NULL, &ft_thread, (void*)&thread[i]);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(ptr->thread[i], NULL);
}

static void	ft_before_calc_plans(t_ptr *ptr, float *rs, t_plan *p1, t_plan *p2, int nbr)
{
	int		i;
	t_c		pos;

	pos = ptr->player.pos;
	i = -1;
	while (++i < nbr)
	{
		if (p1[i].d)
			rs[i] = -(p1[i].a * pos.x + p1[i].b * pos.y + p1[i].c * pos.z + p1[i].d);
		else if (p2[i].d)
			rs[i] = -(p2[i].a * pos.x + p2[i].b * pos.y + p2[i].c * pos.z + p2[i].d);
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
	ft_before_calc_plans(ptr, ptr->rs_plans_y, ptr->pars->plans_so, \
		ptr->pars->plans_no, ptr->pars->nbr_map.y);
	ft_before_calc_plans(ptr, ptr->rs_plans_x, ptr->pars->plans_ea, \
		ptr->pars->plans_we, ptr->pars->nbr_map.x);
}

void	ft_edit_img(t_ptr *ptr)
{
	char			str[11];
	static int		count_fps = 0;

	ptr->time = ft_time(ptr, str, &count_fps);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, ptr->mlx.window);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, ptr->screen.ptr);
	ft_before_calc(ptr);
	ft_threads(ptr);
	mlx_put_image_to_window(ptr->mlx.ptr, ptr->mlx.window, ptr->screen.ptr, 0, 0);
	mlx_string_put(ptr->mlx.ptr, ptr->mlx.window, 15, 20, 0xffffff, str);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, ptr->mlx.window);
	count_fps++;
}
