/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:34:51 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 19:20:05 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	ft_is_sprite_win(t_cub *cub, t_c *pixel, t_vector dir, \
	t_sprite *p)
{
	unsigned int	color;

	pixel->z = cub->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < S_S)
	{
		pixel->x = cub->player.pos.x + dir.x * p->t;
		pixel->y = cub->player.pos.y + dir.y * p->t;
		color = ft_sprite_texture(cub, &cub->img.win, pixel, p);
		if (color)
			return (color);
	}
	return (0);
}

t_dist	ft_win_ray(t_cub *cub, t_vector dir)
{
	t_sprite	*p;
	t_dist		dist;

	dist.t = 0;
	p = &cub->pars->plan_win;
	if (ft_calc_dist_sprite(p, dir))
	{
		dist.color = ft_is_sprite_win(cub, &dist.pixel, dir, p);
		if (dist.color)
			dist.t = p->t;
	}
	return (dist);
}

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
	if ((dist.t = -(cub->player.pos.z - S_W) / dir.z) > 0)
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
