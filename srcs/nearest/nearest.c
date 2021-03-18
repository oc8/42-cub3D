/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/18 17:35:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dist			ft_raycast_y(t_ptr *ptr, t_vector dir)
{
	t_dist	dist;

	// dir.z limit ?
	dist.t = 0;
	if (dir.y > 0)
		dist = ft_ray_y(ptr, dir, ptr->pars->plans_so);
	else if (dir.y < 0)
		dist = ft_ray_y(ptr, dir, ptr->pars->plans_no);
	return (dist);
}

t_dist			ft_raycast_x(t_ptr *ptr, t_vector dir)
{
	t_dist	dist;

	dist.t = 0;
	if (dir.x > 0)
		dist = ft_ray_x(ptr, dir, ptr->pars->plans_ea);
	else if (dir.x < 0)
		dist = ft_ray_x(ptr, dir, ptr->pars->plans_we);
	return (dist);
}

static void		ft_dist(t_ptr *ptr, t_dist dist[6], t_vector dir)
{
	dist[0] = ft_raycast_y(ptr, dir);
	dist[1] = ft_raycast_x(ptr, dir);
	dist[2].t = ft_ray_sprite(ptr, dir, &dist[2]);
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
