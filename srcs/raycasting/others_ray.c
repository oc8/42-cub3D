/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:34:51 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/18 17:35:22 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dist	ft_floor(t_ptr *ptr, t_vector dir)
{
	t_c		*pixel;
	t_dist	dist;

	dist.color = 0;
	pixel = &dist.pixel;
	if ((dist.t = -(ptr->player.pos.z) / dir.z) > 0)
	{
		pixel->x = ptr->player.pos.x + dir.x * dist.t;
		if (pixel->x >= 0 && pixel->x <= ptr->pars->nbr_map.x)
		{
			pixel->y = ptr->player.pos.y + dir.y * dist.t;
			if (pixel->y >= 0 && pixel->y <= ptr->pars->nbr_map.y)
				dist.color = ft_floor_texture(ptr, &dist.pixel);
		}
	}
	if (!dist.color)
		dist.t = 0;
	return (dist);
}

t_dist	ft_top(t_ptr *ptr, t_vector dir)
{
	t_c		*pixel;
	t_dist	dist;

	dist.color = 0;
	pixel = &dist.pixel;
	if ((dist.t = -(ptr->player.pos.z - 1) / dir.z) > 0)
	{
		pixel->x = ptr->player.pos.x + dir.x * dist.t;
		if (pixel->x >= 0 && pixel->x <= ptr->pars->nbr_map.x)
		{
			pixel->y = ptr->player.pos.y + dir.y * dist.t;
			if (pixel->y >= 0 && pixel->y <= ptr->pars->nbr_map.y)
				dist.color = ft_top_texture(ptr, &dist);
		}
	}
	if (!dist.color)
		dist.t = 0;
	return (dist);
}