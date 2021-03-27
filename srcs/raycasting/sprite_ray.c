/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:57:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/27 17:39:24 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int		ft_is_sprite(t_cub *cub, t_dist *dist, t_vector dir, \
	t_sprite *p)
{
	unsigned int	color;

	dist->pixel.z = cub->player.pos.z + dir.z * dist->t;
	if (dist->pixel.z > 0 && dist->pixel.z < S_S)
	{
		dist->pixel.x = cub->player.pos.x + dir.x * dist->t;
		dist->pixel.y = cub->player.pos.y + dir.y * dist->t;
		color = ft_sprite_texture(cub, &cub->img.sprite, &dist->pixel, p);
		if (color)
			return (color);
	}
	return (0);
}

static char			ft_calc_dist_sprite(t_sprite *p, t_vector dir, float *t)
{
	float		rs_dir;

	if (p->t > 0)
	{
		rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
		if (rs_dir)
		{
			*t = p->rs / rs_dir;
			if (*t > 0)
				return (1);
		}
	}
	*t = 0;
	return (0);
}

t_dist				ft_sprite_ray(t_cub *cub, t_vector dir)
{
	t_sprite		*p;
	unsigned int	i;
	t_dist			dist;

	i = 0;
	while (i < cub->pars->nbr_sprite)
	{
		p = &cub->pars->plans_sprite[i];
		if (ft_calc_dist_sprite(p, dir, &dist.t))
		{
			dist.color = ft_is_sprite(cub, &dist, dir, p);
			if (dist.color)
				return (dist);
		}
		i++;
	}
	dist.t = 0;
	return (dist);
}

static unsigned int	ft_is_sprite_finish(t_cub *cub, t_dist *dist, \
	t_vector dir, t_sprite *p)
{
	unsigned int	color;

	dist->pixel.z = cub->player.pos.z + dir.z * dist->t;
	if (dist->pixel.z > 0 && dist->pixel.z < S_S)
	{
		dist->pixel.x = cub->player.pos.x + dir.x * dist->t;
		dist->pixel.y = cub->player.pos.y + dir.y * dist->t;
		color = ft_sprite_texture(cub, &cub->img.finish, &dist->pixel, p);
		if (color)
			return (color);
	}
	return (0);
}

t_dist				ft_finish_ray(t_cub *cub, t_vector dir)
{
	t_sprite	*p;
	t_dist		dist;

	dist.t = 0;
	p = &cub->pars->plan_win;
	if (ft_calc_dist_sprite(p, dir, &dist.t))
	{
		dist.color = ft_is_sprite_finish(cub, &dist, dir, p);
		if (!dist.color)
			dist.t = 0;
	}
	return (dist);
}
