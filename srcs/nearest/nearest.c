/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/15 19:20:11 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_dist	ft_ray_y(t_ptr *ptr, t_vector dir)
{
	t_axe	axe;
	t_dist	dist;

	axe.axe = 'y';
	axe.dir = dir.y;
	axe.pos = (int)ptr->player.pos.y;
	axe.nbr_plan = ptr->pars->nbr_map.y;
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
	dist.t = 0;
	if (dir.x > 0)
		dist = ft_ray(ptr, ptr->pars->plans_ea, dir, &axe);
	else if (dir.x < 0)
		dist = ft_ray(ptr, ptr->pars->plans_we, dir, &axe);
	return (dist);
}

static t_dist	ft_floor(t_ptr *ptr, t_vector dir)
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

static t_dist	ft_top(t_ptr *ptr, t_vector dir)
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

static t_dist	ft_sprite_nearest(t_ptr *ptr, t_vector dir, t_dist dist_x, t_dist dist_y)
{
	t_dist			dist_sprite;

	if (dist_x.t && dist_y.t)
	{
		if (dist_x.t < dist_y.t)
			dist_sprite.t = ft_ray_sprite(ptr, dir, &dist_sprite, dist_x.t);
		else
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

static void		ft_dist(t_ptr *ptr, t_dist dist[6], t_vector dir)
{
	ft_ray_ea(ptr, dir);
	dist[0] = ft_ray_y(ptr, dir);
	dist[1] = ft_ray_x(ptr, dir);
	dist[2] = ft_sprite_nearest(ptr, dir, dist[0], dist[1]);
	dist[3] = ft_top(ptr, dir);
	dist[4] = ft_floor(ptr, dir);
	dist[5].color = ft_skybox(ptr, dir);
	dist[5].t = 9999998;
}

unsigned int	ft_nearest(t_ptr *ptr, t_vector dir)
{
	t_dist			dist[6];
	int				i;
	float			small_dist;
	int				nearest;

	ft_dist(ptr, dist, dir);
	small_dist = 9999999;
	i = -1;
	while (++i < 6)
	{
		if (dist[i].t && dist[i].t < small_dist)
		{
			small_dist = dist[i].t;
			nearest = i;
		}
	}
	if (nearest == 0 || nearest == 1)
	{
		if (dir.x < 0)
			dist[1].color = ft_wall_texture(dist[1].pixel, ptr->we, 'x');
		else
			dist[1].color = ft_wall_texture(dist[1].pixel, ptr->ea, 'x');
		if (dir.y < 0)
			dist[0].color = ft_wall_texture(dist[0].pixel, ptr->no, 'y');
		else
			dist[0].color = ft_wall_texture(dist[0].pixel, ptr->so, 'y');
	}
	return (dist[nearest].color);
}
