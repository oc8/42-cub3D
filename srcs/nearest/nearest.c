/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dist		ft_raycast_y(t_cub *ptr, t_vector dir)
{
	t_dist	dist;

	dist.t = 0;
	if (dir.y > 0)
		dist = ft_ray_y(ptr, dir, ptr->pars->plans_so);
	else if (dir.y < 0)
		dist = ft_ray_y(ptr, dir, ptr->pars->plans_no);
	return (dist);
}

t_dist		ft_raycast_x(t_cub *ptr, t_vector dir)
{
	t_dist	dist;

	dist.t = 0;
	if (dir.x > 0)
		dist = ft_ray_x(ptr, dir, ptr->pars->plans_ea);
	else if (dir.x < 0)
		dist = ft_ray_x(ptr, dir, ptr->pars->plans_we);
	return (dist);
}

static void	ft_nearest_wall(t_cub *ptr, t_dist dist[6], int nearest, t_vector dir)
{
	if (nearest == 0)
	{
		if (dir.y < 0)
			dist[0].color = ft_wall_texture(dist[0].pixel, ptr->no, 'y');
		else
			dist[0].color = ft_wall_texture(dist[0].pixel, ptr->so, 'y');
	}
	else if (nearest == 1)
	{
		if (dir.x < 0)
			dist[1].color = ft_wall_texture(dist[1].pixel, ptr->we, 'x');
		else
			dist[1].color = ft_wall_texture(dist[1].pixel, ptr->ea, 'x');
	}
}

static void	ft_dist(t_cub *ptr, t_dist dist[6], t_vector dir)
{
	dist[0] = ft_raycast_y(ptr, dir);
	dist[1] = ft_raycast_x(ptr, dir);
	dist[2].t = ft_ray_sprite(ptr, dir, &dist[2]);
	dist[3] = ft_top(ptr, dir);
	dist[4] = ft_floor(ptr, dir);
	if (dist[3].t || dist[4].t || dist[0].t || dist[1].t || dist[2].t)
		return ;
	dist[5].color = ft_skybox(ptr, dir);
	dist[5].t = 9999998;
}

t_dist		ft_nearest(t_cub *ptr, t_vector dir)
{
	t_dist	dist[6];
	int		i;
	float	small_dist;
	int		nearest;

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
	ft_nearest_wall(ptr, dist, nearest, dir);
	return (dist[nearest]);
}
