/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/11 18:32:31 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static unsigned int	ft_skybox(t_ptr *ptr, t_vector dir)
{
	float			t;
	float			map;
	unsigned int	color;

	map = 10 * ptr->pars->nbr_map.x;
	if ((t = -(ptr->player.pos.z - map + 1) / dir.z) > 0 && (color = \
		ft_sky_texture(ptr, ptr->player.pos.x + dir.x * t, ptr->player.pos.y + dir.y * t, 1)))
		return (color);
	if ((t = -(ptr->player.pos.x - map) / dir.x) > 0 && (color = \
		ft_sky_texture(ptr, ptr->player.pos.y + dir.y * t, ptr->player.pos.z + dir.z * t, 2)))
		return (color);
	if ((t = -(ptr->player.pos.x + map) / dir.x) > 0 && (color = \
		ft_sky_texture(ptr, ptr->player.pos.y + dir.y * t, ptr->player.pos.z + dir.z * t, 3)))
		return (color);
	if ((t = -(ptr->player.pos.y - map) / dir.y) > 0 && (color = \
		ft_sky_texture(ptr, ptr->player.pos.x + dir.x * t, ptr->player.pos.z + dir.z * t, 4)))
		return (color);
	if ((t = -(ptr->player.pos.y + map) / dir.y) > 0 && (color = \
		ft_sky_texture(ptr, ptr->player.pos.x + dir.x * t, ptr->player.pos.z + dir.z * t, 5)))
		return (color);
	if ((t = -(ptr->player.pos.z + map - 1) / dir.z) > 0 && (color = \
		ft_sky_texture(ptr, ptr->player.pos.x + dir.x * t, ptr->player.pos.y + dir.y * t, 6)))
		return (color);
	return (0);
}

t_dist	ft_ray_y(t_ptr *ptr, t_vector dir)
{
	t_axe	axe;
	t_dist	dist;

	axe.axe = 'y';
	axe.dir = dir.y;
	axe.pos = (int)ptr->player.pos.y;
	axe.nbr_plan = ptr->pars->nbr_map.y;
	axe.rs_plans = ptr->rs_plans_y;
	// dir.z limit ?
	dist.t = 0;
	if (dir.y > 0)
		dist = ft_ray(ptr, ptr->pars->plans_so, dir, &axe);
	else if (dir.y < 0)
		dist = ft_ray(ptr, ptr->pars->plans_no, dir, &axe);
	return (dist);
}

t_dist	ft_ray_x(t_ptr *ptr, t_vector dir)
{
	t_axe	axe;
	t_dist	dist;

	axe.axe = 'x';
	axe.dir = dir.x;
	axe.pos = (int)ptr->player.pos.x;
	axe.nbr_plan = ptr->pars->nbr_map.x;
	axe.rs_plans = ptr->rs_plans_x;
	dist.t = 0;
	if (dir.x > 0)
		dist = ft_ray(ptr, ptr->pars->plans_ea, dir, &axe);
	else if (dir.x < 0)
		dist = ft_ray(ptr, ptr->pars->plans_we, dir, &axe);
	return (dist);
}

static unsigned int	ft_floor(t_ptr *ptr, t_vector dir)
{
	float	t;
	t_c		pixel;

	if ((t = -(ptr->player.pos.z) / dir.z) > 0)
	{
		pixel.x = ptr->player.pos.x + dir.x * t;
		if (pixel.x >= 0 && pixel.x <= ptr->pars->nbr_map.x)
		{
			pixel.y = ptr->player.pos.y + dir.y * t;
			if (pixel.y >= 0 && pixel.y <= ptr->pars->nbr_map.y)
				return (ptr->pars->col_floor);
		}
	}
	return (0);
}

// static unsigned int	ft_check(float v1, float v2, )
// {
	
// }

static t_dist	ft_sprite_nearest(t_ptr *ptr, t_vector dir, t_dist dist_x, t_dist dist_y)
{
	t_dist			dist_sprite;

	if (dist_x.t && dist_y.t)
	{
		if (dist_x.t < dist_y.t)
			dist_sprite.t = ft_ray_sprite(ptr, dir, &dist_sprite, dist_x.t);
		else // if (y < x.t)
			dist_sprite.t = ft_ray_sprite(ptr, dir, &dist_sprite, dist_y.t);
	}
	else if (dist_y.t)
		dist_sprite.t = ft_ray_sprite(ptr, dir, &dist_sprite, dist_y.t);
	else if (dist_x.t)
		dist_sprite.t = ft_ray_sprite(ptr, dir, &dist_sprite, dist_x.t);
	else
		dist_sprite.t = ft_ray_sprite(ptr, dir, &dist_sprite, 999999);
	return (dist_sprite);
}

unsigned int	ft_nearest(t_ptr *ptr, t_vector dir)
{
	t_dist			dist_x;
	t_dist			dist_y;
	t_dist			dist_sprite;
	unsigned int	color;

	dist_y = ft_ray_y(ptr, dir);
	dist_x = ft_ray_x(ptr, dir);
	// ft_check()
	dist_sprite = ft_sprite_nearest(ptr, dir, dist_x, dist_y);
	if (dist_sprite.t)
		return (dist_sprite.color_sprite);
	color = ft_nearest_wall(ptr, dir, dist_x, dist_y);
	if (color)
		return (color);
	color = ft_floor(ptr, dir);
	if (color)
		return (color);
	color = ft_skybox(ptr, dir);
	if (color)
		return (color);
	return (0);
}
