/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:54:11 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 16:58:07 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	ft_wall_texture(t_c pixel, t_img img, char axe)
{
	t_i_signed	index;

	if (axe == 'y')
		index.x = (int)((pixel.x - (int)pixel.x) * img.w);
	else
		index.x = (int)((pixel.y - (int)pixel.y) * img.w);
	index.y = (int)((1 - pixel.z - (int)pixel.z) * img.h);
	if (!(index.x >= img.w || index.y >= img.h || index.x < 0 || index.y < 0))
		return (img.pixels[index.y * (img.s_l / 4) + index.x]);
	return (0);
}

unsigned int	ft_floor_texture(t_ptr *ptr, t_c *pixel)
{
	t_i		index;
	t_img	*img;

	img = &ptr->floor;
	index.x = (int)((pixel->x - (int)pixel->x) * img->w);
	index.y = (int)((pixel->y - (int)pixel->y) * img->h);
	return (img->pixels[index.y * (img->s_l / 4) + index.x]);
}

unsigned int	ft_top_texture(t_ptr *ptr, t_dist *dist)
{
	t_i		i_map;

	i_map.x = (int)dist->pixel.x;
	i_map.y = (int)dist->pixel.y;
	if (i_map.x < ptr->pars->nbr_map.x && i_map.y < ptr->pars->nbr_map.y &&\
		i_map.x >= 0 && i_map.y >= 0)
	{
		if (ptr->pars->map[i_map.y][i_map.x] == '1')
			return (ptr->pars->col_sky);
	}
	return (0);
}

float			ft_pythagore(t_ptr *ptr, t_sprite *sprite, float ab, float bc)
{
	float	ac;

	if (ab > 0.5 || ab < -0.5 || bc > 0.5 || bc < -0.5)
		return (0);
	ac = bc * bc + ab * ab;
	ac = sqrt(ac);
	if (ptr->player.pos.y > sprite->pos.y)
	{
		if (ab >= 0)
			ac += 0.5;
		else
			ac = 0.5 - ac;
	}
	else if (!ab)
	{
		if (bc < 0)
			ac = 0.5 - ac;
		else
			ac += 0.5;
	}
	else
	{
		if (ab >= 0)
			ac = 0.5 - ac;
		else
			ac += 0.5;
	}
	return (ac);
}

unsigned int	ft_sprite_texture(t_ptr *ptr, t_img *img, t_c *pixel, t_sprite *sprite)
{
	t_i_signed	i_img;
	unsigned int	rs;
	float			ac;

	i_img.y = (int)((2 - pixel->z) * (img->h * 0.5));
	if (i_img.y >= (img->h * 2) || i_img.y < 0)
		return (0);
	ac = ft_pythagore(ptr, sprite, pixel->x - sprite->pos.x, pixel->y - sprite->pos.y);
	i_img.x = (int)(ac * img->w);
	if (i_img.x >= img->w || i_img.x < 0)
		return (0);
	rs = img->pixels[i_img.y * (img->s_l / 4) + i_img.x];
	if (rs != img->pixels[0])
		return (rs);
	return (0);
}

unsigned int	ft_sky_texture_up(t_ptr *ptr, float map, t_vector *dir)
{
	t_i_signed	index;
	t_c			c;
	float		t;

	t = -(ptr->player.pos.z - map + 1) / dir->z;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.y = ptr->player.pos.y + dir->y * t;
		if (!(c.x <= -map || c.x >= map || c.y <= -map || c.y >= map))
		{
			index.x = (c.x + map) / (2 * map) * (ptr->sky.w / 4) + 3 * ptr->sky.w / 4;
			index.y = (c.y + map) / (2 * map) * (ptr->sky.h / 3);
			if (!(index.x >= ptr->sky.w || index.y >= ptr->sky.h))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.w) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_1(t_ptr *ptr, float map, t_vector *dir)
{
	t_i_signed	index;
	t_c			c;
	float		t;

	t = -(ptr->player.pos.x - map) / dir->x;
	if (t > 0)
	{
		c.z = ptr->player.pos.z + dir->z * t;
		c.y = ptr->player.pos.y + dir->y * t;
		if (!(c.z <= -map || c.z >= map || c.y <= -map || c.y >= map))
		{
			index.x = (1 - (c.y + map) / (2 * map)) * (ptr->sky.w / 4);
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.h / 3) + ptr->sky.h / 3;
			if (!(index.x >= ptr->sky.w || index.y >= ptr->sky.h))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.w) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_2(t_ptr *ptr, float map, t_vector *dir)
{
	t_i_signed	index;
	t_c			c;
	float		t;

	t = -(ptr->player.pos.x + map) / dir->x;
	if (t > 0)
	{
		c.z = ptr->player.pos.z + dir->z * t;
		c.y = ptr->player.pos.y + dir->y * t;
		if (!(c.z <= -map || c.z >= map || c.y <= -map || c.y >= map))
		{
			index.x = ((c.y + map) / (2 * map)) * (ptr->sky.w / 4) + 2 * ptr->sky.w / 4;
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.h / 3) + 1 * ptr->sky.h / 3;
			if (!(index.x >= ptr->sky.w || index.y >= ptr->sky.h))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.w) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_3(t_ptr *ptr, float map, t_vector *dir)
{
	t_i_signed		index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.y - map) / dir->y;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.z = ptr->player.pos.z + dir->z * t;
		if (!(c.x <= -map || c.x >= map || c.z <= -map || c.z >= map))
		{
			index.x = ((c.x + map) / (2 * map)) * (ptr->sky.w / 4) + 3 * ptr->sky.w / 4;
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.h / 3) + 1 * ptr->sky.h / 3;
			if (!(index.x >= ptr->sky.w || index.y >= ptr->sky.h))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.w) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_4(t_ptr *ptr, float map, t_vector *dir)
{
	t_i_signed		index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.y + map) / dir->y;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.z = ptr->player.pos.z + dir->z * t;
		if (!(c.x <= -map || c.x >= map || c.z <= -map || c.z >= map))
		{
			index.x = (1 - (c.x + map) / (2 * map)) * (ptr->sky.w / 4) + ptr->sky.w / 4;
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.h / 3) + ptr->sky.h / 3;
			if (!(index.x >= ptr->sky.w || index.y >= ptr->sky.h))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.w) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_down(t_ptr *ptr, float map, t_vector *dir)
{
	t_i_signed		index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.z + map - 1) / dir->z;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.y = ptr->player.pos.y + dir->y * t;
		if (!(c.x <= -map || c.x >= map || c.y <= -map || c.y >= map))
		{
			index.x = ((c.x + map) / (2 * map)) * (ptr->sky.w / 4) + 3 * ptr->sky.w / 4;
			index.y = (1 - (c.y + map) / (2 * map)) * (ptr->sky.h / 3) + 2 * ptr->sky.h / 3;
			if (!(index.x >= ptr->sky.w || index.y >= ptr->sky.h))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.w) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_skybox(t_ptr *ptr, t_vector dir)
{
	float			map;
	unsigned int	color;
	// float			t[6];

	map = 10 * ptr->pars->nbr_map.x;
	// t[0] = -(ptr->player.pos.z - map + 1) / dir.z;
	// t[1] = -(ptr->player.pos.x - map) / dir.x;
	// t[2] = -(ptr->player.pos.x + map) / dir.x;
	// t[3] = -(ptr->player.pos.y - map) / dir.y;
	// t[4] = -(ptr->player.pos.y + map) / dir.y;
	// t[5] = -(ptr->player.pos.z + map - 1) / dir.z;
	color = ft_sky_texture_up(ptr, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_1(ptr, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_2(ptr, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_3(ptr, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_4(ptr, map, &dir);
	if (color)
		return (color);
	color = ft_sky_texture_down(ptr, map, &dir);
	if (color)
		return (color);
	return (0);
}
