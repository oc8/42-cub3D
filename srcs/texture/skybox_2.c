/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:09:30 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:18:51 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_sky_texture_4(t_cub *cub, float map, t_vector *dir)
{
	t_i_signed	i;
	t_c			c;
	float		t;
	t_img		*sky;

	sky = &cub->sky;
	t = -(cub->player.pos.y + map) / dir->y;
	if (t > 0)
	{
		c.x = cub->player.pos.x + dir->x * t;
		c.z = cub->player.pos.z + dir->z * t;
		if (!(c.x <= -map || c.x >= map || c.z <= -map || c.z >= map))
		{
			i.x = (1 - (c.x + map) / (2 * map)) * (sky->w / 4) + sky->w / 4;
			i.y = (1 - (c.z + map) / (2 * map)) * (sky->h / 3) + sky->h / 3;
			if (!(i.x >= sky->w || i.y >= sky->h))
				return (sky->pixels[(int)(i.y * (sky->w) + i.x)]);
		}
	}
	return (0);
}

unsigned int	ft_sky_texture_down(t_cub *cub, float map, t_vector *dir)
{
	t_i_signed	i;
	t_c			c;
	float		t;
	t_img		*sky;

	sky = &cub->sky;
	t = -(cub->player.pos.z + map - 1) / dir->z;
	if (t > 0)
	{
		c.x = cub->player.pos.x + dir->x * t;
		c.y = cub->player.pos.y + dir->y * t;
		if (!(c.x <= -map || c.x >= map || c.y <= -map || c.y >= map))
		{
			i.x = ((c.x + map) / (2 * map)) * (sky->w / 4) + 3 * sky->w / 4;
			i.y = (1 - (c.y + map) / (2 * map)) * (sky->h / 3) + 2 * sky->h / 3;
			if (!(i.x >= sky->w || i.y >= sky->h))
				return (sky->pixels[(int)(i.y * (sky->w) + i.x)]);
		}
	}
	return (0);
}
