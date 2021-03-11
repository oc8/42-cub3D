/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:57:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/11 17:21:26 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_is_wall(t_ptr *ptr, t_c *pixel, t_vector dir, t_plan *p, float t, char axe)
{
	t_i			i_map;

	pixel->z = ptr->player.pos.z + dir.z * t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		if (axe == 'x')
		{
			pixel->y = ptr->player.pos.y + dir.y * t; //
			i_map.x = p->d * -1;
			if (dir.x < 0)
				i_map.x -= 1;
			i_map.y = (int)pixel->y;
		}
		else
		{
			pixel->x = ptr->player.pos.x + dir.x * t; //
			i_map.y = p->d * -1;
			if (dir.y < 0)
				i_map.y -= 1;
			i_map.x = (int)pixel->x;
		}
		if (i_map.x < ptr->pars->nbr_map.x && i_map.y < ptr->pars->nbr_map.y && i_map.x >= 0 && i_map.y >= 0)//////////
		{
			if (ptr->pars->map[i_map.y][i_map.x] == '1')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

static float	ft_ray_wall(t_ptr *ptr, t_plan *p, t_c *pixel, t_vector dir, float rs_p, t_axe *axe)
{
	float		rs_dir;
	float		t;

	if (p->d)
	{
		rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
		if (rs_dir)
		{
			t = rs_p / rs_dir;
			if (t > 0 && ft_is_wall(ptr, pixel, dir, p, t, axe->axe))
				return (t);
		}
	}
	return (0);
}

t_dist	ft_ray(t_ptr *ptr, t_plan *plans, t_vector dir, t_axe *axe)
{
	t_dist		dist;
	int			i;

	i = axe->pos;
	if (dir.x > 0)
		i += 1;
	if (i < 0)
		i = 0;
	if (i >= axe->nbr_plan)
		i = axe->nbr_plan - 1;
	if (axe->dir != 0)
		while (i >= 0 && i < axe->nbr_plan)
		{
			dist.t = ft_ray_wall(ptr, &plans[i], &dist.pixel, dir, axe->rs_plans[i], axe);
			if (dist.t)
			{
				dist.flag = 'w';
				return (dist);
			}
			if (axe->dir > 0)
				i++;
			else
				i--;
		}
	dist.flag = 0;
	return (dist);
}
