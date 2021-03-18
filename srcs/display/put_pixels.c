/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:36:20 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/18 13:39:21 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if ((y * (ptr->screen.s_l / 4) + x >= 0))
				screen[y * (ptr->screen.s_l / 4) + x] = color;
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

static void	*ft_thread(void *work)
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

void		ft_threads(t_ptr *ptr)
{
	t_thread	thread[THREAD];
	int			i;

	i = -1;
	while (++i < THREAD)
	{
		thread[i] = (t_thread){ptr, i};
		if (pthread_create(&ptr->thread[i], 0, &ft_thread, (void*)&thread[i]))
			ft_close(ptr, 1, "pthread_creat() error");
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(ptr->thread[i], NULL);
}
