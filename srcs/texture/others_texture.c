/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:43:14 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 17:56:32 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_win_texture(t_cub *cub)
{
	float				x;
	float				y;
	unsigned int	color;
	t_img			*scr;
	t_img			*img;
	t_i				i;

	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, cub->mlx.win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, cub->scr.ptr);
	scr = &cub->scr;
	img = &cub->img.win;
	y = 0;
	while (y < cub->scr.h)
	{
		x = 0;
		while (x < cub->scr.w)
		{
			// printf("y = %d, x = %d\n", (int)(y / scr->h * img->h), (int)(x / scr->w * img->w));
			i.x = x / scr->w * img->w;
			i.y = y / scr->h * img->h;
			color = img->pixels[i.y * (img->s_l / 4) + (i.x)];
			// if ((y * (cub->scr.s_l / 4) + x >= 0))
			if (color != img->pixels[0])
				scr->pixels[(int)(y * (scr->s_l / 4) + x)] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->scr.ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, cub->mlx.win);
}
