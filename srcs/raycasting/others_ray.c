/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:34:51 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 19:07:50 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dist	ft_floor(t_cub *cub, t_vector dir)
{
	t_c		*pixel;
	t_dist	dist;

	dist.color = 0;
	pixel = &dist.pixel;
	if ((dist.t = -(cub->player.pos.z) / dir.z) > 0)
	{
		pixel->x = cub->player.pos.x + dir.x * dist.t;
		if (pixel->x >= 0 && pixel->x <= cub->pars->nbr_map.x)
		{
			pixel->y = cub->player.pos.y + dir.y * dist.t;
			if (pixel->y >= 0 && pixel->y <= cub->pars->nbr_map.y)
				dist.color = ft_floor_texture(cub, &dist.pixel);
		}
	}
	if (!dist.color)
		dist.t = 0;
	return (dist);
}

t_dist	ft_top(t_cub *cub, t_vector dir)
{
	t_c		*pixel;
	t_dist	dist;

	dist.color = 0;
	pixel = &dist.pixel;
	if ((dist.t = -(cub->player.pos.z - 1) / dir.z) > 0)
	{
		pixel->x = cub->player.pos.x + dir.x * dist.t;
		if (pixel->x >= 0 && pixel->x <= cub->pars->nbr_map.x)
		{
			pixel->y = cub->player.pos.y + dir.y * dist.t;
			if (pixel->y >= 0 && pixel->y <= cub->pars->nbr_map.y)
				dist.color = ft_top_texture(cub, &dist);
		}
	}
	if (!dist.color)
		dist.t = 0;
	return (dist);
}
