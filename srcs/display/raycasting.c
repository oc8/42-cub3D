/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/04 17:55:15 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	ft_is_wall(t_ptr *ptr, t_c *pixel, t_c dir, t_p *p, float t, char axe)
{
	t_i			i_map;

	pixel->z = ptr->pos.z + dir.z * t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		if (axe == 'x')
		{
			pixel->y = ptr->pos.y + dir.y * t; //
			i_map.x = p->d * -1;
			if (dir.x < 0)
				i_map.x -= 1;
			i_map.y = (int)pixel->y;
		}
		else
		{
			pixel->x = ptr->pos.x + dir.x * t; //
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

static float	ft_ray_wall(t_ptr *ptr, t_p *p, t_c *pixel, t_c dir, float rs_p, t_axe *axe)
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

static t_dist	ft_ray_axe(t_ptr *ptr, t_p *plans, t_c dir, t_c *pixel, t_axe *axe)
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
			dist.t = ft_ray_wall(ptr, &plans[i], pixel, dir, axe->rs_plans[i], axe);
			if (dist.t)
			{
				dist.flag = 'w';
				return (dist);
			}
			if (plans[i].nbr)
			{
				dist.t = ft_ray_sprite(ptr, dir, pixel, &plans[i], &dist); //
				if (dist.t)
				{
					dist.flag = 's';
					return (dist);
				}
			}
			if (axe->dir > 0)
				i++;
			else
				i--;
		}
	dist.flag = 0;
	return (dist);
}
static unsigned int	ft_smallest_distance()
{
	return (0);
}

unsigned int		ft_ray(t_ptr *ptr, t_c dir)
{
	t_dist	dist_x;
	t_dist	dist_y;
	t_c		pixel_x;
	t_c		pixel_y;
	t_axe	axe;

	axe.axe = 'y';
	axe.dir = dir.y;
	axe.pos = (int)ptr->pos.y;
	axe.nbr_plan = ptr->pars->nbr_map.y;
	axe.rs_plans = ptr->rs_plans_y;
	// dir.z limit ?
	if (dir.y > 0)
		dist_y = ft_ray_axe(ptr, ptr->pars->plans_so, dir, &pixel_y, &axe);
	else if (dir.y < 0)
		dist_y = ft_ray_axe(ptr, ptr->pars->plans_no, dir, &pixel_y, &axe);
	axe.axe = 'x';
	axe.dir = dir.x;
	axe.pos = (int)ptr->pos.x;
	axe.nbr_plan = ptr->pars->nbr_map.x;
	axe.rs_plans = ptr->rs_plans_x;
	if (dir.x > 0)
		dist_x = ft_ray_axe(ptr, ptr->pars->plans_ea, dir, &pixel_x, &axe);
	else if (dir.x < 0)
		dist_x = ft_ray_axe(ptr, ptr->pars->plans_we, dir, &pixel_x, &axe);
	ft_smallest_distance();
	if (dist_x.flag && dist_y.flag)
	{
		if (dist_x.t < dist_y.t)
		{
			if (dist_x.flag == 's')
				return (dist_x.color_sprite);
			if (dir.x < 0)
				return (ft_wall_texture(pixel_x, ptr->we, 'x'));
			else
				return (ft_wall_texture(pixel_x, ptr->ea, 'x'));
		}
		else // if (dist_y < dist_x.t)
		{
			if (dist_y.flag == 's')
				return (dist_y.color_sprite);
			if (dir.y < 0)
				return (ft_wall_texture(pixel_y, ptr->no, 'y'));
			else
				return (ft_wall_texture(pixel_y, ptr->so, 'y'));
		}
	}
	else if (dist_y.flag)
	{
		if (dist_y.flag == 's')
			return (dist_y.color_sprite);
		if (dir.y < 0)
			return (ft_wall_texture(pixel_y, ptr->no, 'y'));
		else
			return (ft_wall_texture(pixel_y, ptr->so, 'y'));
	}
	else if (dist_x.flag)
	{
		if (dist_x.flag == 's')
			return (dist_x.color_sprite);
		if (dir.x < 0)
			return (ft_wall_texture(pixel_x, ptr->we, 'x'));
		else
			return (ft_wall_texture(pixel_x, ptr->ea, 'x'));
	}
	if ((dist_x.t = - (ptr->pos.z) / dir.z) > 0)
	{
		pixel_x.x = ptr->pos.x + dir.x * dist_x.t;
		if (pixel_x.x >= 0 && pixel_x.x <= ptr->pars->nbr_map.x)
		{
			pixel_x.y = ptr->pos.y + dir.y * dist_x.t;
			if (pixel_x.y >= 0 && pixel_x.y <= ptr->pars->nbr_map.y)
				return (ptr->pars->col_floor);
		}
	}
	unsigned int	color;
	float map = 10 * ptr->pars->nbr_map.x;
	if ((dist_x.t = - (ptr->pos.z - map + 1) / dir.z) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.y + dir.y * dist_x.t, 1)))
			return (color);
	else if ((dist_x.t = - (ptr->pos.x - map) / dir.x) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.y + dir.y * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 2)))
			return (color);
	else if ((dist_x.t = - (ptr->pos.x + map) / dir.x) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.y + dir.y * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 3)))
			return (color);
	else if ((dist_x.t = - (ptr->pos.y - map) / dir.y) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 4)))
			return (color);
	else if ((dist_x.t = - (ptr->pos.y + map) / dir.y) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.z + dir.z * dist_x.t, 5)))
			return (color);
	else if ((dist_x.t = - (ptr->pos.z + map - 1) / dir.z) > 0
&& (color = ft_sky_texture(ptr, ptr->pos.x + dir.x * dist_x.t, ptr->pos.y + dir.y * dist_x.t, 6)))
			return (color);
	return (0);
}
