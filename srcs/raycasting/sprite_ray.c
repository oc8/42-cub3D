/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:57:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 20:34:05 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_is_sprite(t_cub *cub, t_c *pixel, t_vector dir, t_sprite *p)
{
	unsigned int	color;

	pixel->z = cub->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < S_S)
	{
		pixel->x = cub->player.pos.x + dir.x * p->t;
		pixel->y = cub->player.pos.y + dir.y * p->t;
		color = ft_sprite_texture(cub, &cub->img.sprite, pixel, p);
		if (color)
			return (color);
	}
	return (0);
}

char			ft_calc_dist_sprite(t_sprite *p, t_vector dir)
{
	float		rs_dir;

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

float			ft_sprite_ray(t_cub *cub, t_vector dir, t_dist *dist)
{
	t_sprite		*p;
	unsigned int	i;

	i = 0;
	while (i < cub->pars->nbr_sprite)
	{
		p = &cub->pars->plans_sprite[i];
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
