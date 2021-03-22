/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:37:15 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/22 18:02:36 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fly(t_ptr *ptr)
{
	t_vector		dir;
	static char		flag = 0;
	static t_dist	dist;

	if (!ptr->key.space)
	{
		flag = 0;
		return ;
	}
	if (!flag)
	{
		dir = ptr->player.dir[ptr->screen.h / 2 * ptr->screen.w + ptr->screen.w / 2];
		dir = ft_rotation(dir, &ptr->agl, ptr);
		dist = ft_nearest(ptr, dir);
		if (dist.t > 8 || dist.pixel.z < 0.5)
		{
			ptr->key.space = 0;
			return ;
		}
		flag = 1;
	}
	ft_fly_move(ptr, dist);
}

void	ft_fly_move(t_ptr *ptr, t_dist dist)
{
	t_c		*pos;

	pos = &ptr->player.pos;
	pos->x = pos->x - ((pos->x - dist.pixel.x) * (ptr->delta * 4));
	pos->y = pos->y - ((pos->y - dist.pixel.y) * (ptr->delta * 4));
	pos->z = pos->z - ((pos->z - dist.pixel.z) * (ptr->delta * 4));
	if (fabs(pos->x - dist.pixel.x) < 0.3 && fabs(pos->y - dist.pixel.y) < 0.3 \
		 && fabs(pos->z - dist.pixel.z) < 0.3)
		ptr->key.space = 0;
}
