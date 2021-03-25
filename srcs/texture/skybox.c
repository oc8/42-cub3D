/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:09:33 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 15:24:26 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_sky_texture_up(t_cub *cub, float map, t_vector *dir)
{
	t_i_signed	i;
	t_c			c;
	float		t;
	t_img		*sky;

	sky = &cub->img.sky;
	t = -(cub->player.pos.z - map + 1) / dir->z;
	if (t > 0)
	{
		c.x = cub->player.pos.x + dir->x * t;
		c.y = cub->player.pos.y + dir->y * t;
		if (!(c.x <= -map || c.x >= map || c.y <= -map || c.y >= map))
		{
			i.x = (c.x + map) / (2 * map) * (sky->w / 4) + 3 * sky->w / 4;
			i.y = (c.y + map) / (2 * map) * (sky->h / 3);
			if (!(i.x >= sky->w || i.y >= sky->h))
				return (sky->pixels[(int)(i.y * (sky->w) + i.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_1(t_cub *cub, float map, t_vector *dir)
{
	t_i_signed	i;
	t_c			c;
	float		t;
	t_img		*sky;

	sky = &cub->img.sky;
	t = -(cub->player.pos.x - map) / dir->x;
	if (t > 0)
	{
		c.z = cub->player.pos.z + dir->z * t;
		c.y = cub->player.pos.y + dir->y * t;
		if (!(c.z <= -map || c.z >= map || c.y <= -map || c.y >= map))
		{
			i.x = (1 - (c.y + map) / (2 * map)) * (sky->w / 4);
			i.y = (1 - (c.z + map) / (2 * map)) * (sky->h / 3) + sky->h / 3;
			if (!(i.x >= sky->w || i.y >= sky->h))
				return (sky->pixels[(int)(i.y * (sky->w) + i.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_2(t_cub *cub, float map, t_vector *dir)
{
	t_i_signed	i;
	t_c			c;
	float		t;
	t_img		*sky;

	sky = &cub->img.sky;
	t = -(cub->player.pos.x + map) / dir->x;
	if (t > 0)
	{
		c.z = cub->player.pos.z + dir->z * t;
		c.y = cub->player.pos.y + dir->y * t;
		if (!(c.z <= -map || c.z >= map || c.y <= -map || c.y >= map))
		{
			i.x = ((c.y + map) / (2 * map)) * (sky->w / 4) + 2 * sky->w / 4;
			i.y = (1 - (c.z + map) / (2 * map)) * (sky->h / 3) + 1 * sky->h / 3;
			if (!(i.x >= sky->w || i.y >= sky->h))
				return (sky->pixels[(int)(i.y * (sky->w) + i.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_3(t_cub *cub, float map, t_vector *dir)
{
	t_i_signed	i;
	t_c			c;
	float		t;
	t_img		*sky;

	sky = &cub->img.sky;
	t = -(cub->player.pos.y - map) / dir->y;
	if (t > 0)
	{
		c.x = cub->player.pos.x + dir->x * t;
		c.z = cub->player.pos.z + dir->z * t;
		if (!(c.x <= -map || c.x >= map || c.z <= -map || c.z >= map))
		{
			i.x = ((c.x + map) / (2 * map)) * (sky->w / 4) + 3 * sky->w / 4;
			i.y = (1 - (c.z + map) / (2 * map)) * (sky->h / 3) + 1 * sky->h / 3;
			if (!(i.x >= sky->w || i.y >= sky->h))
				return (sky->pixels[(int)(i.y * (sky->w) + i.x)]);
		}
	}
	return (0);
}

unsigned int	ft_skybox(t_cub *cub, t_vector dir)
{
	float			map;
	unsigned int	color;

	map = 10 * cub->pars->nbr_map.x;
	color = ft_sky_texture_up(cub, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_1(cub, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_2(cub, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_3(cub, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_4(cub, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_down(cub, map, &dir);
	if (color)
		return (color);
	return (0);
}
