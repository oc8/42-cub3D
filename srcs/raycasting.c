/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:56:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/23 15:59:03 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	ft_texture(t_c pixel, t_img img, char axe)
{
	t_i		i_img;

	if (axe == 'y')
		i_img.x = (int)((pixel.x - (int)pixel.x) * img.width);
	else
		i_img.x = (int)((pixel.y - (int)pixel.y) * img.width);
	i_img.y = (int)((pixel.z - (int)pixel.z) * img.height);
	// printf("x = %d\ny = %d\n\n", i_img.x, i_img.y);
	return (img.pixels[i_img.y * (int)(img.s_l * 0.25) + i_img.x]);
}

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

static float	ft_ray_axe_(t_ptr *ptr, t_p *plans, t_c dir, t_c *pixel, t_axe *axe)
{
	float		t;
	int			i;

	i = axe->pos;
	if (dir.x > 0)
		i += 1;// ?
	if (i < 0)
		i = 0;
	if (i >= axe->nbr_plan)
		i = axe->nbr_plan - 1;
	if (axe->dir != 0)
		while (i >= 0 && i < axe->nbr_plan)
		{
			t = ft_ray_wall(ptr, &plans[i], pixel, dir, axe->rs_plans[i], axe);
			if (t)
				return (t);
			if (plans->nbr)
			{
				t = ft_ray_sprite(ptr, dir, pixel, &plans[i]); //
				if (t)
					return (t);
			}
			if (axe->dir > 0)
				i++;
			else
				i--;
		}
		return (0);
}

int		ft_ray(t_ptr *ptr, t_c dir)
{
	float	t_x;
	float	t_y;
	t_c		pixel_x;
	t_c		pixel_y;
	t_axe	axe;

	t_x = 0;
	t_y = 0;
	axe.axe = 'y';
	axe.dir = dir.y;
	axe.pos = (int)ptr->pos.y;
	axe.nbr_plan = ptr->pars->nbr_map.y;
	axe.rs_plans = ptr->rs_plans_y;
	// dir.z limit ?
	if (dir.y > 0)
		t_y = ft_ray_axe_(ptr, ptr->pars->plans_so, dir, &pixel_y, &axe);
	else if (dir.y < 0)
		t_y = ft_ray_axe_(ptr, ptr->pars->plans_no, dir, &pixel_y, &axe);
	axe.axe = 'x';
	axe.dir = dir.x;
	axe.pos = (int)ptr->pos.x;
	axe.nbr_plan = ptr->pars->nbr_map.x;
	axe.rs_plans = ptr->rs_plans_x;
	if (dir.x > 0)
		t_x = ft_ray_axe_(ptr, ptr->pars->plans_ea, dir, &pixel_x, &axe);
	else if (dir.x < 0)
		t_x = ft_ray_axe_(ptr, ptr->pars->plans_we, dir, &pixel_x, &axe);

	if (t_x && t_y)
	{
		if (t_x < t_y)
		{
			if (dir.x < 0)
				return (ft_texture(pixel_x, ptr->we, 'x'));
			else
				return (ft_texture(pixel_x, ptr->ea, 'x'));
		}
		else // if (t_y < t_x)
		{
			if (dir.y < 0)
				return (ft_texture(pixel_y, ptr->no, 'y'));
			else
				return (ft_texture(pixel_y, ptr->so, 'y'));
		}
	}
	else if (t_y)
	{
		if (dir.y < 0)
			return (ft_texture(pixel_y, ptr->no, 'y'));
		else
			return (ft_texture(pixel_y, ptr->so, 'y'));
	}
	else if (t_x)
	{
		if (dir.x < 0)
			return (ft_texture(pixel_x, ptr->we, 'x'));
		else
			return (ft_texture(pixel_x, ptr->ea, 'x'));
	}
	if (pixel_x.z > 0.5 || pixel_y.z > 0.5)
		return (0x000f00);
	return (0xffffff);
}
