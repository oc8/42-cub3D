/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/29 14:45:56 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dist		ft_raycast_y(t_cub *cub, t_vector dir)
{
	t_dist	dist;

	dist.t = 0;
	if (dir.y > 0)
		dist = ft_ray_y(cub, dir, cub->pars->plans_so);
	else if (dir.y < 0)
		dist = ft_ray_y(cub, dir, cub->pars->plans_no);
	return (dist);
}

t_dist		ft_raycast_x(t_cub *cub, t_vector dir)
{
	t_dist	dist;

	dist.t = 0;
	if (dir.x > 0)
		dist = ft_ray_x(cub, dir, cub->pars->plans_ea);
	else if (dir.x < 0)
		dist = ft_ray_x(cub, dir, cub->pars->plans_we);
	return (dist);
}

static void	ft_nearest_wall(t_cub *cub, t_dist dist[7], int nbr, t_vector dir)
{
	if (nbr == 0)
	{
		if (dir.y < 0)
			dist[0].color = ft_wall_texture(dist[0].pixel, cub->img.no, 'y');
		else
			dist[0].color = ft_wall_texture(dist[0].pixel, cub->img.so, 'y');
	}
	else if (nbr == 1)
	{
		if (dir.x < 0)
			dist[1].color = ft_wall_texture(dist[1].pixel, cub->img.we, 'x');
		else
			dist[1].color = ft_wall_texture(dist[1].pixel, cub->img.ea, 'x');
	}
}

static void	ft_dist(t_cub *cub, t_dist dist[7], t_vector dir)
{
	dist[0].t = 0;
	dist[1].t = 0;
	dist[2].t = 0;
	dist[3].t = 0;
	dist[4].t = 0;
	dist[5].t = 0;
	dist[6].t = 0;
	dist[0] = ft_raycast_y(cub, dir);
	dist[1] = ft_raycast_x(cub, dir);
	dist[2] = ft_sprite_ray(cub, dir);
	if (cub->flag_finish)
		dist[6] = ft_finish_ray(cub, dir);
	dist[3] = ft_top(cub, dir);
	dist[4] = ft_floor(cub, dir);
	if (dist[3].t || dist[4].t || dist[0].t || dist[1].t || dist[2].t \
			|| dist[6].t)
		return ;
	dist[5].color = ft_skybox(cub, dir);
	if (dist[5].color)
		dist[5].t = 9999998;
}

t_dist		ft_nearest(t_cub *cub, t_vector dir)
{
	t_dist	dist[7];
	int		i;
	float	small_dist;
	int		nearest;

	ft_dist(cub, dist, dir);
	small_dist = 9999999;
	nearest = 0;
	dist[0].color = 0;
	i = -1;
	while (++i < 7)
	{
		if (dist[i].t && dist[i].t < small_dist)
		{
			small_dist = dist[i].t;
			nearest = i;
		}
	}
	ft_nearest_wall(cub, dist, nearest, dir);
	return (dist[nearest]);
}
