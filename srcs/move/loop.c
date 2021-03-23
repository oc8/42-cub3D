/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:54:01 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 19:18:18 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_new_pos(t_cub *cub, t_c *pos)
{
	if (cub->key.w)
	{
		pos->x += sin(cub->player.agl_hor) * cub->player.speed;
		pos->y -= cos(cub->player.agl_hor) * cub->player.speed;
	}
	if (cub->key.s)
	{
		pos->x -= sin(cub->player.agl_hor) * cub->player.speed;
		pos->y += cos(cub->player.agl_hor) * cub->player.speed;
	}
	if (cub->key.a)
	{
		pos->x += sin(cub->player.agl_hor - M_PI_2) * cub->player.speed;
		pos->y -= cos(cub->player.agl_hor - M_PI_2) * cub->player.speed;
	}
	if (cub->key.d)
	{
		pos->x += sin(cub->player.agl_hor + M_PI_2) * cub->player.speed;
		pos->y -= cos(cub->player.agl_hor + M_PI_2) * cub->player.speed;
	}
	if (cub->key.up)
		pos->z += cub->player.speed;
	if (cub->key.down)
		pos->z -= cub->player.speed;
}

static void	ft_view(t_cub *cub)
{
	float	rs;

	if (cub->key.al)
		cub->player.agl_hor -= cub->player.speed;
	if (cub->key.ar)
		cub->player.agl_hor += cub->player.speed;
	if (cub->key.ad)
	{
		rs = cub->player.agl_vrt + 0.5 * cub->player.speed;
		if (rs < M_PI_2 && rs > -M_PI_2)
			cub->player.agl_vrt = rs;
	}
	if (cub->key.au)
	{
		rs = cub->player.agl_vrt - 0.5 * cub->player.speed;
		if (rs < M_PI_2 && rs > -M_PI_2)
			cub->player.agl_vrt = rs;
	}
}

static void	ft_move(t_cub *cub)
{
	t_c		new_pos;

	ft_fly(cub);
	new_pos = cub->player.pos;
	if (new_pos.z > 0.5 && !cub->key.up)
		new_pos.z = new_pos.z - ((new_pos.z + 0.5) * cub->delta);//
	ft_new_pos(cub, &new_pos);
	ft_view(cub);
	ft_check_new_pos(cub, new_pos);
}

int			ft_loop(t_cub *cub)
{
	ft_move(cub);
	ft_edit_img(cub);
	return (0);
}
