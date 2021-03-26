/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:54:01 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 20:48:13 by odroz-ba         ###   ########lyon.fr   */
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
		cub->player.agl_hor -= cub->delta * SENSIBILITY;
	if (cub->key.ar)
		cub->player.agl_hor += cub->delta * SENSIBILITY;
	if (cub->key.ad)
	{
		rs = cub->player.agl_vrt + cub->delta / 2 * SENSIBILITY;
		if (rs < M_PI_2 && rs > -M_PI_2)
			cub->player.agl_vrt = rs;
	}
	if (cub->key.au)
	{
		rs = cub->player.agl_vrt - cub->delta / 2 * SENSIBILITY;
		if (rs < M_PI_2 && rs > -M_PI_2)
			cub->player.agl_vrt = rs;
	}
}

static void	ft_move(t_cub *cub)
{
	t_c				pos;
	t_i				pos_i;
	static float	z_start = 0;

	ft_jump(cub);
	pos = cub->player.pos;
	pos_i.x = (int)pos.x;
	pos_i.y = (int)pos.y;
	if (pos.z > S_P && !cub->key.up && ft_in_map(cub, pos_i) && pos.z < 20)
	{
		if (!z_start)
			z_start = pos.z;
		if (cub->pars->map[pos_i.y][pos_i.x] == '1')
			pos.z -= sqrt(2 * GRAVITY * (z_start - (pos.z - (S_W + S_P)))) * \
					cub->delta;
		else
			pos.z -= sqrt(2 * GRAVITY * (z_start - (pos.z - S_P))) * cub->delta;
	}
	else
		z_start = 0;
	ft_new_pos(cub, &pos);
	ft_view(cub);
	ft_check_new_pos(cub, pos);
}

int			ft_loop(t_cub *cub)
{
	if (cub->flag_win)
	{
		ft_win_screen(cub);
		return (0);
	}
	ft_move(cub);
	ft_edit_img(cub);
	return (0);
}
