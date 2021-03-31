/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:40:42 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/31 18:55:20 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_mouse(int x, int y, t_cub *cub)
{
	float		rs;
	static int	x_temp = 0;
	static int	y_temp = 0;

	if (!x_temp && !y_temp)
	{
		x_temp = x;
		y_temp = y;
		return (0);
	}
	x -= x_temp;
	y -= y_temp - 22;
	cub->player.agl_hor += x / (M_PI * 180);
	rs = cub->player.agl_vrt + y / (M_PI * 180);
	if (rs < M_PI_2 - 0.2 && rs > -M_PI_2 + 0.2)
		cub->player.agl_vrt = rs;
	mlx_mouse_move(cub->mlx.win, cub->scr.w * 0.5, cub->scr.h * 0.5);
	mlx_mouse_get_pos(cub->mlx.win, &x_temp, &y_temp);
	return (0);
}
