/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:54:11 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/11 16:29:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	ft_wall_texture(t_c pixel, t_img img, char axe)
{
	t_i		index;

	if (axe == 'y')
		index.x = (int)((pixel.x - (int)pixel.x) * img.width);
	else
		index.x = (int)((pixel.y - (int)pixel.y) * img.width);
	index.y = (int)((1 - pixel.z - (int)pixel.z) * img.height);
	if (!(index.x >= img.width || index.y >= img.height || index.x < 0 || index.y < 0))
		return (img.pixels[index.y * (int)(img.s_l * 0.25) + index.x]);
	return (0);
}

unsigned int	ft_sprite_texture(t_ptr *ptr, t_img *sprite, t_c *pixel, t_i index)
{
	t_i		i_img;
	unsigned int		rs;
	float	ab;
	float	bc;
	float	ac;
	// center & z -> ok
	// trouver x / y
	(void)index;
	// (void)sprite;
	// (void)pixel;
	// printf("x = %f, y = %f, z = %f\n", pixel->x, pixel->y, pixel->z);
	i_img.y = (int)((2 - pixel->z) * (sprite->height * 0.5));
	if (i_img.y >= (sprite->height * 2) || i_img.y < 0)
		return (0);
	ab = pixel->x - (index.x + 0.5);
	bc = pixel->y - (index.y + 0.5);
	// printf("ab = %f, bc = %f\n", ab, bc);
	if (ab > 0.5 || ab < -0.5 || bc > 0.5 || bc < -0.5)
		return (0);
	ac = bc * bc + ab * ab;
	ac = sqrt(ac);
	if (ptr->player.pos.y > (index.y + 0.5))
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
	i_img.x = (int)(ac * sprite->width);
	if (i_img.x >= sprite->width || i_img.x < 0)
		return (0);
	// printf("x = %d, y = %d\n", i_img.x, i_img.y);
	rs = sprite->pixels[i_img.y * (sprite->s_l / 4) + i_img.x];
	// printf("AC = %f, rs = %d\n", (sqrt(ac) + test), rs);
	// printf("rs = %d\n", rs);
	if (rs != sprite->pixels[0])
		return (rs);
	return (0);
}

unsigned int	ft_sky_texture_up(t_ptr *ptr, float map, t_vector *dir)
{
	t_i				index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.z - map + 1) / dir->z;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.y = ptr->player.pos.y + dir->y * t;
		map = 10 * ptr->pars->nbr_map.x;
		if (!(c.x <= -map || c.x >= map || c.y <= -map || c.y >= map))
		{
			index.x = (c.x + map) / (2 * map) * (ptr->sky.width / 4) + 3 * ptr->sky.width / 4;
			index.y = (c.y + map) / (2 * map) * (ptr->sky.height / 3);
			if (!(index.x >= ptr->sky.width || index.y >= ptr->sky.height))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.width) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_1(t_ptr *ptr, float map, t_vector *dir)
{
	t_i				index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.x - map) / dir->x;
	if (t > 0)
	{
		c.z = ptr->player.pos.z + dir->z * t;
		c.y = ptr->player.pos.y + dir->y * t;
		map = 10 * ptr->pars->nbr_map.x;
		if (!(c.z <= -map || c.z >= map || c.y <= -map || c.y >= map))
		{
			index.x = (1 - (c.y + map) / (2 * map)) * (ptr->sky.width / 4);
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.height / 3) + ptr->sky.height / 3;
			if (!(index.x >= ptr->sky.width || index.y >= ptr->sky.height))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.width) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_2(t_ptr *ptr, float map, t_vector *dir)
{
	t_i				index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.x + map) / dir->x;
	if (t > 0)
	{
		c.z = ptr->player.pos.z + dir->z * t;
		c.y = ptr->player.pos.y + dir->y * t;
		map = 10 * ptr->pars->nbr_map.x;
		if (!(c.z <= -map || c.z >= map || c.y <= -map || c.y >= map))
		{
			index.x = ((c.y + map) / (2 * map)) * (ptr->sky.width / 4) + 2 * ptr->sky.width / 4;
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.height / 3) + 1 * ptr->sky.height / 3;
			if (!(index.x >= ptr->sky.width || index.y >= ptr->sky.height))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.width) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_3(t_ptr *ptr, float map, t_vector *dir)
{
	t_i				index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.y - map) / dir->y;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.z = ptr->player.pos.z + dir->z * t;
		map = 10 * ptr->pars->nbr_map.x;
		if (!(c.x <= -map || c.x >= map || c.z <= -map || c.z >= map))
		{
			index.x = ((c.x + map) / (2 * map)) * (ptr->sky.width / 4) + 3 * ptr->sky.width / 4;
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.height / 3) + 1 * ptr->sky.height / 3;
			if (!(index.x >= ptr->sky.width || index.y >= ptr->sky.height))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.width) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_4(t_ptr *ptr, float map, t_vector *dir)
{
	t_i				index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.y - map) / dir->y;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.z = ptr->player.pos.z + dir->z * t;
		map = 10 * ptr->pars->nbr_map.x;
		if (!(c.x <= -map || c.x >= map || c.z <= -map || c.z >= map))
		{
			index.x = (1 - (c.x + map) / (2 * map)) * (ptr->sky.width / 4) + 1 * ptr->sky.width / 4;
			index.y = (1 - (c.z + map) / (2 * map)) * (ptr->sky.height / 3) + 1 * ptr->sky.height / 3;
			if (!(index.x >= ptr->sky.width || index.y >= ptr->sky.height))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.width) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_down(t_ptr *ptr, float map, t_vector *dir)
{
	t_i				index;
	t_c				c;
	float			t;

	t = -(ptr->player.pos.z + map - 1) / dir->z;
	if (t > 0)
	{
		c.x = ptr->player.pos.x + dir->x * t;
		c.y = ptr->player.pos.y + dir->y * t;
		map = 10 * ptr->pars->nbr_map.x;
		if (!(c.x <= -map || c.x >= map || c.y <= -map || c.y >= map))
		{
			index.x = ((c.x + map) / (2 * map)) * (ptr->sky.width / 4) + 3 * ptr->sky.width / 4;
			index.y = (1 - (c.y + map) / (2 * map)) * (ptr->sky.height / 3) + 2 * ptr->sky.height / 3;
			if (!(index.x >= ptr->sky.width || index.y >= ptr->sky.height))
				return (ptr->sky.pixels[(int)(index.y * (ptr->sky.width) + index.x)]);
		}
	}
	return (0);
}

unsigned int	ft_skybox(t_ptr *ptr, t_vector dir)
{
	float			map;
	unsigned int	color;

	map = 10 * ptr->pars->nbr_map.x;
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
