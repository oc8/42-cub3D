/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:37:15 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 18:49:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fly(t_cub *cub)
{
	t_vector		dir;
	static char		flag = 0;
	static t_dist	dist;

	if (cub->key.space && cub->player.pos.z < 0.6)
		cub->player.pos.z += cub->delta * 10;
	return ;
	if (!cub->key.space)
	{
		flag = 0;
		return ;
	}
	if (!flag)
	{
		dir = cub->player.dir[cub->screen.h / 2 * cub->screen.w + \
			cub->screen.w / 2];
		dir = ft_rotation(dir, &cub->agl, cub);
		dist = ft_nearest(cub, dir);
		if (dist.t > 8 || dist.pixel.z < 0.5)
		{
			cub->key.space = 0;
			return ;
		}
		flag = 1;
	}
	ft_fly_move(cub, dist);
}

void	ft_fly_move(t_cub *cub, t_dist dist)
{
	t_c		*pos;

	pos = &cub->player.pos;
	pos->x = pos->x - ((pos->x - dist.pixel.x) * (cub->delta * 4));
	pos->y = pos->y - ((pos->y - dist.pixel.y) * (cub->delta * 4));
	pos->z = pos->z - ((pos->z - dist.pixel.z) * (cub->delta * 4));
	if (fabs(pos->x - dist.pixel.x) < 0.3 && fabs(pos->y - dist.pixel.y) < 0.3 \
		&& fabs(pos->z - dist.pixel.z) < 0.3)
		cub->key.space = 0;
}
