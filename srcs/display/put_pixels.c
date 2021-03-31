/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:36:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/31 20:38:23 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_scale(t_cub *cub, int x_main, int y_main, unsigned int color)
{
	int				x;
	int				y;
	t_img			*scr;
	unsigned int	pix_main;

	pix_main = y_main * (cub->scr.s_l / 4) + x_main;
	scr = &cub->scr;
	y = -1;
	while (++y < cub->scale && y_main + y < scr->h)
	{
		x = -1;
		while (++x < cub->scale && x_main + x < scr->w)
			scr->pixels[pix_main + (y * (cub->scr.s_l / 4) + x)] = color;
	}
}

static void	ft_put_pixels(t_cub *cub, int thread_nb)
{
	int		x;
	int		y;
	t_dist	dist;

	y = (cub->scr.h / THREAD) * thread_nb;
	while (y < (cub->scr.h / THREAD) * (thread_nb + 1))
	{
		x = 0;
		while (x < cub->scr.w)
		{
			dist = ft_nearest(cub, ft_rotation(cub->player.dir[y * \
				cub->scr.w + x], &cub->agl));
			if ((y * (cub->scr.s_l / 4) + x >= 0))
				ft_scale(cub, x, y, dist.color);
			x += cub->scale;
		}
		y += cub->scale;
	}
}

static void	*ft_thread(void *work)
{
	t_cub			*cub;
	t_thread		*wcub;

	wcub = (t_thread *)work;
	cub = (t_cub *)wcub->cub;
	ft_put_pixels(cub, wcub->id);
	return (cub);
}

void		ft_threads(t_cub *cub)
{
	t_thread	thread[THREAD];
	int			i;

	i = -1;
	while (++i < THREAD)
	{
		thread[i] = (t_thread){cub, i};
		if (pthread_create(&cub->thread[i], 0, &ft_thread, (void *)&thread[i]))
			ft_close(cub, 1, "pthread_creat() error");
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(cub->thread[i], NULL);
}
