/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:54:01 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/22 18:00:39 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_new_pos(t_ptr *ptr, t_c *pos)
{
	if (ptr->key.w)
	{
		pos->x += sin(ptr->player.agl_hor) * ptr->player.speed;
		pos->y -= cos(ptr->player.agl_hor) * ptr->player.speed;
	}
	if (ptr->key.s)
	{
		pos->x -= sin(ptr->player.agl_hor) * ptr->player.speed;
		pos->y += cos(ptr->player.agl_hor) * ptr->player.speed;
	}
	if (ptr->key.a)
	{
		pos->x += sin(ptr->player.agl_hor - M_PI_2) * ptr->player.speed;
		pos->y -= cos(ptr->player.agl_hor - M_PI_2) * ptr->player.speed;
	}
	if (ptr->key.d)
	{
		pos->x += sin(ptr->player.agl_hor + M_PI_2) * ptr->player.speed;
		pos->y -= cos(ptr->player.agl_hor + M_PI_2) * ptr->player.speed;
	}
	if (ptr->key.up)
		pos->z += ptr->player.speed;
	if (ptr->key.down)
		pos->z -= ptr->player.speed;
}

static void	ft_view(t_ptr *ptr)
{
	float	rs;

	if (ptr->key.al)
		ptr->player.agl_hor -= ptr->player.speed;
	if (ptr->key.ar)
		ptr->player.agl_hor += ptr->player.speed;
	if (ptr->key.ad)
	{
		rs = ptr->player.agl_vrt + 0.5 * ptr->player.speed;
		if (rs < M_PI_2 && rs > -M_PI_2)
			ptr->player.agl_vrt = rs;
	}
	if (ptr->key.au)
	{
		rs = ptr->player.agl_vrt - 0.5 * ptr->player.speed;
		if (rs < M_PI_2 && rs > -M_PI_2)
			ptr->player.agl_vrt = rs;
	}
}

static void	ft_move(t_ptr *ptr)
{
	t_c		new_pos;

	ft_fly(ptr);
	new_pos = ptr->player.pos;
	if (new_pos.z > 0.5 && !ptr->key.up)
		new_pos.z = new_pos.z - ((new_pos.z + 0.5) * ptr->delta);
	ft_new_pos(ptr, &new_pos);
	ft_view(ptr);
	ft_check_new_pos(ptr, new_pos);
}

int			ft_loop(t_ptr *ptr)
{
	ft_move(ptr);
	ft_edit_img(ptr);
	return (0);
}
