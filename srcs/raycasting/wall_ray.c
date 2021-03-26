/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:10:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 19:18:21 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ft_is_wall_x(t_cub *cub, t_c *pixel, t_vector dir, t_plan *p)
{
	t_i			i_map;

	pixel->z = cub->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < S_W)
	{
		pixel->y = cub->player.pos.y + dir.y * p->t;
		i_map.x = p->d * -1;
		if (dir.x < 0)
			i_map.x -= 1;
		i_map.y = floor(pixel->y);
		return (ft_check_index_map(cub, i_map));
	}
	return (0);
}

static char	ft_is_wall_y(t_cub *cub, t_c *pixel, t_vector dir, t_plan *p)
{
	t_i			i_map;

	pixel->z = cub->player.pos.z + dir.z * p->t;
	if (pixel->z > 0 && pixel->z < S_W)
	{
		pixel->x = cub->player.pos.x + dir.x * p->t;
		i_map.y = p->d * -1;
		if (dir.y < 0)
			i_map.y -= 1;
		i_map.x = floor(pixel->x);
		return (ft_check_index_map(cub, i_map));
	}
	return (0);
}

static int	ft_init_index(float pos, float dir, int nbr_plan)
{
	int	i;

	i = floor(pos);
	if (dir > 0)
		i += 1;
	if (i < 0)
		i = 0;
	if (i >= nbr_plan)
		i = nbr_plan - 1;
	return (i);
}

t_dist		ft_ray_x(t_cub *cub, t_vector dir, t_plan *p)
{
	t_dist			dist;
	int				i;
	int				nbr_plan;

	nbr_plan = cub->pars->nbr_map.x;
	i = ft_init_index((int)cub->player.pos.x, dir.x, nbr_plan);
	while (i >= 0 && i <= nbr_plan)
	{
		if (ft_calc_dist(&p[i], dir))
		{
			dist.t = p[i].t;
			if (ft_is_wall_x(cub, &dist.pixel, dir, &p[i]))
				return (dist);
		}
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
	int				i;
	int				nbr_plan;

	nbr_plan = cub->pars->nbr_map.y;
	i = ft_init_index((int)cub->player.pos.y, dir.y, nbr_plan);
	while (i >= 0 && i <= nbr_plan)
	{
		if (ft_calc_dist(&p[i], dir))
		{
			dist.t = p[i].t;
			if (ft_is_wall_y(cub, &dist.pixel, dir, &p[i]))
				return (dist);
		}
		if (dir.y > 0)
			i++;
		else
			i--;
	}
	dist.t = 0;
	return (dist);
}
