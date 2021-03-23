/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:36:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:23:37 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_put_pixels(t_cub *cub, unsigned int *screen, int thread_nb)
{
	int				x;
	int				y;
	t_dist			dist;

	y = (cub->screen.h / THREAD) * thread_nb;
	while (y < (cub->screen.h / THREAD) * (thread_nb + 1))
	{
		x = 0;
		while (x < cub->screen.w)
		{
			dist = ft_nearest(cub, ft_rotation(cub->player.dir[y * \
				cub->screen.w + x], &cub->agl, cub));
			if ((y * (cub->screen.s_l / 4) + x >= 0))
				screen[y * (cub->screen.s_l / 4) + x] = dist.color;
			x++;
		}
		y++;
	}
}

static void	ft_put_4_pixels(t_cub *cub, unsigned int *scr, int thread_nb)
{
	int				x;
	int				y;
	t_dist			dist;

	y = (cub->screen.h / THREAD) * thread_nb;
	while (y < (cub->screen.h / THREAD) * (thread_nb + 1))
	{
		x = 0;
		while (x < cub->screen.w)
		{
			dist = ft_nearest(cub, ft_rotation(cub->player.dir[y * \
				cub->screen.w + x], &cub->agl, cub));
			if ((y * (int)(cub->screen.s_l * 0.25) + x >= 0))
			{
				scr[y * (int)(cub->screen.s_l * 0.25) + x] = dist.color;
				scr[y * (int)(cub->screen.s_l * 0.25) + (x + 1)] = dist.color;
				scr[(y + 1) * (int)(cub->screen.s_l * 0.25) + \
					(x + 1)] = dist.color;
				scr[(y + 1) * (int)(cub->screen.s_l * 0.25) + x] = dist.color;
			}
			x += 2;
		}
		y += 2;
	}
}

static void	*ft_thread(void *work)
{
	t_cub			*cub;
	t_thread		*wcub;

	wcub = (t_thread *)work;
	cub = (t_cub *)wcub->ptr;
	if ((cub->screen.w > 500 || cub->screen.h > 500) && !cub->flag_save)
		ft_put_4_pixels(cub, cub->screen.pixels, wcub->id);
	else
		ft_put_pixels(cub, cub->screen.pixels, wcub->id);
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
