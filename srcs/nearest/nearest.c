/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/10 13:04:17 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_witch_texture_x(t_ptr *ptr, t_c pixel, t_vector dir, t_dist dist)
{
	if (dist.flag == 's')
		return (dist.color_sprite);
	if (dir.x < 0)
		return (ft_wall_texture(pixel, ptr->we, 'x'));
	else
		return (ft_wall_texture(pixel, ptr->ea, 'x'));
}

int		ft_witch_texture_y(t_ptr *ptr, t_c pixel, t_vector dir, t_dist dist)
{
	if (dist.flag == 's')
		return (dist.color_sprite);
	if (dir.y < 0)
		return (ft_wall_texture(pixel, ptr->no, 'y'));
	else
		return (ft_wall_texture(pixel, ptr->so, 'y'));
}

// ft_skybox(t_ptr *ptr);

t_dist	ft_ray_y(t_ptr *ptr, t_vector dir)
{
	t_axe	axe;
	t_dist	dist;

	axe.axe = 'y';
	axe.dir = dir.y;
	axe.pos = (int)ptr->pos.y;
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
	axe.pos = (int)ptr->pos.x;
	axe.nbr_plan = ptr->pars->nbr_map.x;
	axe.rs_plans = ptr->rs_plans_x;
	dist.t = 0;
	if (dir.x > 0)
		dist = ft_ray(ptr, ptr->pars->plans_ea, dir, &axe);
	else if (dir.x < 0)
		dist = ft_ray(ptr, ptr->pars->plans_we, dir, &axe);
	return (dist);
}

unsigned int	ft_nearest(t_ptr *ptr, t_vector dir)
{
	t_dist	dist_x;
	t_dist	dist_y;

	dist_y = ft_ray_y(ptr, dir);
	dist_x = ft_ray_x(ptr, dir);
	if (dist_x.flag && dist_y.flag)
	{
		if (dist_x.t < dist_y.t)
			return (ft_witch_texture_x(ptr, dist_x.pixel, dir, dist_x));
		else // if (dist_y < dist_x.t)
			return (ft_witch_texture_y(ptr, dist_y.pixel, dir, dist_y));
	}
	else if (dist_y.flag)
		return (ft_witch_texture_y(ptr, dist_y.pixel, dir, dist_y));
	else if (dist_x.flag)
		return (ft_witch_texture_x(ptr, dist_x.pixel, dir, dist_x));

	if ((dist_x.t = -(ptr->pos.z) / dir.z) > 0)
	{
		dist_x.pixel.x = ptr->pos.x + dir.x * dist_x.t;
		if (dist_x.pixel.x >= 0 && dist_x.pixel.x <= ptr->pars->nbr_map.x)
		{
			dist_x.pixel.y = ptr->pos.y + dir.y * dist_x.t;
			if (dist_x.pixel.y >= 0 && dist_x.pixel.y <= ptr->pars->nbr_map.y)
				return (ptr->pars->col_floor);
		}
	}
	// ft_sky_box(ptr);
	unsigned int	color;
	float map = 10 * ptr->pars->nbr_map.x;
	if ((dist_x.t = -(ptr->pos.z - map + 1) / dir.z) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.y + dir.y * dist_x.t, 1)))
			return (color);
	else if ((dist_x.t = -(ptr->pos.x - map) / dir.x) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.y + dir.y * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 2)))
			return (color);
	else if ((dist_x.t = -(ptr->pos.x + map) / dir.x) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.y + dir.y * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 3)))
			return (color);
	else if ((dist_x.t = -(ptr->pos.y - map) / dir.y) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 4)))
			return (color);
	else if ((dist_x.t = -(ptr->pos.y + map) / dir.y) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 5)))
			return (color);
	else if ((dist_x.t = -(ptr->pos.z + map - 1) / dir.z) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.y + dir.y * dist_x.t, 6)))
			return (color);
	return (0);
}
