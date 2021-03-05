/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:54:01 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/05 14:57:31 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_travel(t_ptr *ptr, t_c new_pos)
{
	t_i		pos;
	t_i		new_pos_i;

	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	pos.x = (int)ptr->pos.x;
	pos.y = (int)ptr->pos.y;
	if (ft_in_map(ptr, new_pos_i))
	{
		if (ptr->pars->map[new_pos_i.y][new_pos_i.x] == 0 || ptr->pos.z > 1 || ptr->pos.z < -0.5)
		{
			ptr->pos.x = new_pos.x;
			ptr->pos.y = new_pos.y;
		}
		else if (ptr->pars->map[new_pos_i.y][pos.x] == 0)
			ptr->pos.y = new_pos.y;
		else if (ptr->pars->map[pos.y][new_pos_i.x] == 0)
			ptr->pos.x = new_pos.x;
		ft_create_plan_sprite(ptr);
	}
	else if (ptr->pos.x != new_pos.x || ptr->pos.y != new_pos.y)
	{
		ptr->pos.x = new_pos.x;
		ptr->pos.y = new_pos.y;
		ft_create_plan_sprite(ptr);
	}
}

int		ft_loop(t_ptr *ptr)
{
	t_c		new_pos;

	new_pos.x = ptr->pos.x;
	new_pos.y = ptr->pos.y;
	if (ptr->key.al)
		ptr->agl_hor -= 0.2;
	if (ptr->key.ar)
		ptr->agl_hor += 0.2;
	if (ptr->key.w)
	{
		new_pos.x += sin(ptr->agl_hor) * ptr->speed;
		new_pos.y -= cos(ptr->agl_hor) * ptr->speed;
	}
	if (ptr->key.s)
	{
		new_pos.x -= sin(ptr->agl_hor) * ptr->speed;
		new_pos.y += cos(ptr->agl_hor) * ptr->speed;
	}
	if (ptr->key.a)
	{
		new_pos.x += sin(ptr->agl_hor - M_PI_2) * ptr->speed;
		new_pos.y -= cos(ptr->agl_hor - M_PI_2) * ptr->speed;
	}
	if (ptr->key.d)
	{
		new_pos.x += sin(ptr->agl_hor + M_PI_2) * ptr->speed;
		new_pos.y -= cos(ptr->agl_hor + M_PI_2) * ptr->speed;
	}
	if (ptr->key.ad)
		ptr->agl_vrt += 0.1;
	if (ptr->key.au)
		ptr->agl_vrt -= 0.1;
	if (ptr->key.up)
		ptr->pos.z += ptr->speed;
	if (ptr->key.down)
		ptr->pos.z -= ptr->speed;
	ft_travel(ptr, new_pos);
	ft_edit_img(ptr);
	return (0);
}
