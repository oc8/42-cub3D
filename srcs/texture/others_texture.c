/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:43:14 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 20:25:43 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_top_texture(t_cub *cub, t_dist *dist)
{
	t_i		i_map;

	i_map.x = dist->pixel.x;
	i_map.y = dist->pixel.y;
	if (i_map.x < cub->pars->nbr_map.x && i_map.y < cub->pars->nbr_map.y &&\
		i_map.x >= 0 && i_map.y >= 0)
	{
		if (cub->pars->map[i_map.y][i_map.x] == '1')
			return (cub->pars->col_sky);
	}
	return (0);
}

unsigned int	ft_floor_texture(t_cub *cub, t_c *pixel)
{
	t_i		index;
	t_img	*img;

	img = &cub->img.floor;
	index.x = (pixel->x - (int)pixel->x) * img->w;
	index.y = (pixel->y - (int)pixel->y) * img->h;
	return (img->pixels[index.y * (img->s_l / 4) + index.x]);
}

unsigned int	ft_win_texture(t_cub *cub, float x, float y)
{
	t_i				i;
	unsigned int	color;
	t_img			*scr;
	t_img			*img;

	scr = &cub->scr;
	img = &cub->img.win;
	i.x = x * img->w / scr->w;
	i.y = y * img->h / scr->h;
	color = img->pixels[i.y * (img->s_l / 4) + (i.x)];
	if (color == img->pixels[0])
		color = 0;
	return (color);
}

void			ft_win_screen(t_cub *cub)
{
	int				x;
	int				y;
	unsigned int	color;
	t_img			*scr;

	scr = &cub->scr;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, cub->mlx.win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, cub->scr.ptr);
	y = -1;
	while (++y < cub->scr.h)
	{
		x = -1;
		while (++x < cub->scr.w)
		{
			color = ft_win_texture(cub, x, y);
			if (color)
				scr->pixels[(int)(y * (scr->s_l / 4) + x)] = color;
		}
	}
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->scr.ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, cub->mlx.win);
}
