/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:57:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/24 19:58:03 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_is_sprite(t_cub *cub, t_c *pixel, t_vector dir, t_sprite *sprite)
{
	t_i				i_map;
	unsigned int	color;

	pixel->z = cub->player.pos.z + dir.z * sprite->t;
	if (pixel->z > 0 && pixel->z < 2)
	{
		pixel->x = cub->player.pos.x + dir.x * sprite->t;
		pixel->y = cub->player.pos.y + dir.y * sprite->t;
		i_map.x = (int)pixel->x;
		i_map.y = (int)pixel->y;
		color = ft_sprite_texture(cub, &cub->sprite, pixel, sprite);
		if (color)
			return (color);
	}
	return (0);
}

static char		ft_calc_dist_sprite(t_sprite *p, t_vector dir)
{
	float			rs_dir;

	if (p->t > 0)
	{
		rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
		if (rs_dir)
		{
			p->t = p->rs / rs_dir;
			if (p->t > 0)
				return (1);
		}
	}
	return (0);
}

float			ft_ray_sprite(t_cub *cub, t_vector dir, t_dist *dist)
{
	t_sprite		*p;
	unsigned int	i;

	i = 0;
	while (i < cub->pars->nbr_sprite)
	{
		p = &cub->pars->plans_sprite[i];
		ft_calc_dist_sprite(p, dir);
		if (ft_calc_dist_sprite(p, dir))
		{
			dist->color = ft_is_sprite(cub, &dist->pixel, dir, p);
			if (dist->color)
				return (p->t);
		}
		i++;
	}
	return (0);
}
