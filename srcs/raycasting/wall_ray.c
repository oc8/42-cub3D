/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:10:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 15:11:02 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	ft_is_wall_x(t_ptr *ptr, t_c *pixel, t_vector dir, t_plan *p)
{
	t_i			i_map;

	pixel->z = ptr->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		pixel->y = ptr->player.pos.y + dir.y * p->t;
		i_map.x = p->d * -1;
		if (dir.x < 0)
			i_map.x -= 1;
		i_map.y = (int)pixel->y;
		return (ft_check_index_map(ptr, i_map));
	}
	return (0);
}

static char	ft_is_wall_y(t_ptr *ptr, t_c *pixel, t_vector dir, t_plan *p)
{
	t_i			i_map;

	pixel->z = ptr->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		pixel->x = ptr->player.pos.x + dir.x * p->t;
		i_map.y = p->d * -1;
		if (dir.y < 0)
			i_map.y -= 1;
		i_map.x = (int)pixel->x;
		return (ft_check_index_map(ptr, i_map));
	}
	return (0);
}

t_dist	ft_ray_x(t_ptr *ptr, t_vector dir, t_plan *p)
{
	t_dist			dist;
	unsigned int	i;

	i = (int)ptr->player.pos.x;
	if (dir.x > 0)
		i += 1;
	if (i < 0)
		i = 0;
	if (i >= ptr->pars->nbr_map.x)
		i = ptr->pars->nbr_map.x - 1;
	if (dir.x != 0)
		while (i >= 0 && i <= ptr->pars->nbr_map.x)
		{
			dist.t = ft_calc_dist(&p[i], dir);
			p[i].t = dist.t;
			if (dist.t && ft_is_wall_x(ptr, &dist.pixel, dir, &p[i]))
				return (dist);
			if (dir.x > 0)
				i++;
			else
				i--;
		}
	dist.t = 0;
	return (dist);
}

t_dist	ft_ray_y(t_ptr *ptr, t_vector dir, t_plan *p)
{
	t_dist			dist;
	unsigned int	i;

	i = (int)ptr->player.pos.y;
	if (dir.y > 0)
		i += 1;
	if (i < 0)
		i = 0;
	if (i >= ptr->pars->nbr_map.y)
		i = ptr->pars->nbr_map.y - 1;
	if (dir.y != 0)
		while (i >= 0 && i <= ptr->pars->nbr_map.y)
		{
			dist.t = ft_calc_dist(&p[i], dir);
			p[i].t = dist.t;
			if (dist.t && ft_is_wall_y(ptr, &dist.pixel, dir, &p[i]))
				return (dist);
			if (dir.y > 0)
				i++;
			else
				i--;
		}
	dist.t = 0;
	return (dist);
}
