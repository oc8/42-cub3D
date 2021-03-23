/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:54:11 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

unsigned int	ft_floor_texture(t_cub *ptr, t_c *pixel)
{
	t_i		index;
	t_img	*img;

	img = &ptr->floor;
	index.x = (int)((pixel->x - (int)pixel->x) * img->w);
	index.y = (int)((pixel->y - (int)pixel->y) * img->h);
	return (img->pixels[index.y * (img->s_l / 4) + index.x]);
}

unsigned int	ft_top_texture(t_cub *ptr, t_dist *dist)
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
