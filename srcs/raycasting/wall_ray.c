/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:10:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:22:07 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ft_is_wall_x(t_cub *cub, t_c *pixel, t_vector dir, t_plan *p)
{
	t_i			i_map;

	pixel->z = cub->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		pixel->y = cub->player.pos.y + dir.y * p->t;
		i_map.x = p->d * -1;
		if (dir.x < 0)
			i_map.x -= 1;
		i_map.y = (int)pixel->y;
		pixel->x = cub->player.pos.x + dir.x * p->t;
		return (ft_check_index_map(cub, i_map));
	}
	return (0);
}

static char	ft_is_wall_y(t_cub *cub, t_c *pixel, t_vector dir, t_plan *p)
{
	t_i			i_map;

	pixel->z = cub->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		pixel->x = cub->player.pos.x + dir.x * p->t;
		i_map.y = p->d * -1;
		if (dir.y < 0)
			i_map.y -= 1;
		i_map.x = (int)pixel->x;
		pixel->y = cub->player.pos.y + dir.y * p->t;
		return (ft_check_index_map(cub, i_map));
	}
	return (0);
}

t_dist		ft_ray_x(t_cub *cub, t_vector dir, t_plan *p)
{
	t_dist			dist;
	unsigned int	i;

	i = (int)cub->player.pos.x;
	if (dir.x > 0)
		i += 1;
	if (i < 0)
		i = 0;
	if (i >= cub->pars->nbr_map.x)
		i = cub->pars->nbr_map.x - 1;
	if (dir.x != 0)
		while (i >= 0 && i <= cub->pars->nbr_map.x)
		{
			dist.t = ft_calc_dist(&p[i], dir);
			p[i].t = dist.t;
			if (dist.t && ft_is_wall_x(cub, &dist.pixel, dir, &p[i]))
				return (dist);
			if (dir.x > 0)
				i++;
			else
				i--;
		}
	dist.t = 0;
	return (dist);
}

t_dist		ft_ray_y(t_cub *cub, t_vector dir, t_plan *p)
{
	t_dist			dist;
	unsigned int	i;

	i = (int)cub->player.pos.y;
	if (dir.y > 0)
		i += 1;
	if (i < 0)
		i = 0;
	if (i >= cub->pars->nbr_map.y)
		i = cub->pars->nbr_map.y - 1;
	if (dir.y != 0)
		while (i >= 0 && i <= cub->pars->nbr_map.y)
		{
			dist.t = ft_calc_dist(&p[i], dir);
			p[i].t = dist.t;
			if (dist.t && ft_is_wall_y(cub, &dist.pixel, dir, &p[i]))
				return (dist);
			if (dir.y > 0)
				i++;
			else
				i--;
		}
	dist.t = 0;
	return (dist);
}
