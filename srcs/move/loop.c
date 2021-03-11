/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:54:01 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/11 16:29:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_check(t_ptr *ptr, t_i new_pos_i, t_c new_pos)
{
	t_i		pos;

	pos.x = (int)ptr->player.pos.x;
	pos.y = (int)ptr->player.pos.y;
	if ((!ptr->pars->map[new_pos_i.y][new_pos_i.x] &&\
			!ptr->pars->map[new_pos_i.y][pos.x] && !ptr->pars->map[pos.y]\
				[new_pos_i.x]) || ptr->player.pos.z > 1 || ptr->player.pos.z < -0.5)
	{
		ptr->player.pos.x = new_pos.x;
		ptr->player.pos.y = new_pos.y;
	}
	else if (!ptr->pars->map[new_pos_i.y][pos.x])
		ptr->player.pos.y = new_pos.y;
	else if (!ptr->pars->map[pos.y][new_pos_i.x])
		ptr->player.pos.x = new_pos.x;
	ft_create_plan_sprite(ptr);
}

static void	ft_check_new_pos(t_ptr *ptr, t_c new_pos)
{
	t_i		new_pos_i;

	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (ft_in_map(ptr, new_pos_i))
		ft_check(ptr, new_pos_i, new_pos);
	else if (ptr->player.pos.x != new_pos.x || ptr->player.pos.y != new_pos.y)
	{
		ptr->player.pos.x = new_pos.x;
		ptr->player.pos.y = new_pos.y;
		ft_create_plan_sprite(ptr);
	}
}

static void	ft_new_pos(t_ptr *ptr, char key, t_c *pos)
{
	if (key == 'w')
	{
		pos->x += sin(ptr->player.agl_hor) * ptr->player.speed;
		pos->y -= cos(ptr->player.agl_hor) * ptr->player.speed;
	}
	else if (key == 's')
	{
		pos->x -= sin(ptr->player.agl_hor) * ptr->player.speed;
		pos->y += cos(ptr->player.agl_hor) * ptr->player.speed;
	}
	else if (key == 'a')
	{
		pos->x += sin(ptr->player.agl_hor - M_PI_2) * ptr->player.speed;
		pos->y -= cos(ptr->player.agl_hor - M_PI_2) * ptr->player.speed;
	}
	else
	{
		pos->x += sin(ptr->player.agl_hor + M_PI_2) * ptr->player.speed;
		pos->y -= cos(ptr->player.agl_hor + M_PI_2) * ptr->player.speed;
	}
}

static void	ft_move(t_ptr *ptr)
{
	t_c		new_pos;

	new_pos.x = ptr->player.pos.x;
	new_pos.y = ptr->player.pos.y;
	if (ptr->key.al)
		ptr->player.agl_hor -= ptr->player.speed;
	if (ptr->key.ar)
		ptr->player.agl_hor += ptr->player.speed;
	if (ptr->key.w)
		ft_new_pos(ptr, 'w', &new_pos);
	if (ptr->key.s)
		ft_new_pos(ptr, 's', &new_pos);
	if (ptr->key.a)
		ft_new_pos(ptr, 'a', &new_pos);
	if (ptr->key.d)
		ft_new_pos(ptr, 'd', &new_pos);
	if (ptr->key.ad)
		ptr->player.agl_vrt += 0.5 * ptr->player.speed;
	if (ptr->key.au)
		ptr->player.agl_vrt -= 0.5 * ptr->player.speed;
	if (ptr->key.up)
		ptr->player.pos.z += ptr->player.speed;
	if (ptr->key.down)
		ptr->player.pos.z -= ptr->player.speed;
	ft_check_new_pos(ptr, new_pos);
}

int		ft_loop(t_ptr *ptr)
{
	ft_move(ptr);
	ft_edit_img(ptr);
	return (0);
}
