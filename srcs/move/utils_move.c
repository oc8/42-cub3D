/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:30:37 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/18 15:55:58 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_wall(t_ptr *ptr, t_i new_pos_i, t_c new_pos, t_c *pos)
{
	t_i		pos_i;

	pos_i.x = (unsigned int)pos->x;
	pos_i.y = (unsigned int)pos->y;
	if ((ptr->pars->map[new_pos_i.y][new_pos_i.x] != '1' && \
			ptr->pars->map[new_pos_i.y][pos_i.x] != '1' && \
			ptr->pars->map[pos_i.y][new_pos_i.x] != '1'))
	{
		pos->x = new_pos.x;
		pos->y = new_pos.y;
	}
	else if (ptr->pars->map[new_pos_i.y][pos_i.x] != '1')
		pos->y = new_pos.y;
	else if (ptr->pars->map[pos_i.y][new_pos_i.x] != '1')
		pos->x = new_pos.x;
}

static void	ft_check_all(t_ptr *ptr, t_i new_pos_i, t_c new_pos, t_i pos)
{
	if ((!ptr->pars->map[new_pos_i.y][new_pos_i.x] && \
			!ptr->pars->map[new_pos_i.y][pos.x] && \
			!ptr->pars->map[pos.y][new_pos_i.x]))
	{
		ptr->player.pos.x = new_pos.x;
		ptr->player.pos.y = new_pos.y;
	}
	else if (!ptr->pars->map[new_pos_i.y][pos.x])
		ptr->player.pos.y = new_pos.y;
	else if (!ptr->pars->map[pos.y][new_pos_i.x])
		ptr->player.pos.x = new_pos.x;
}

static void	ft_check(t_ptr *ptr, t_i new_pos_i, t_c new_pos)
{
	t_i		pos;

	pos.x = (unsigned int)ptr->player.pos.x;
	pos.y = (unsigned int)ptr->player.pos.y;
	if (ptr->key.m)
	{
		if (pos.x == ptr->pars->finish.x && pos.y == ptr->pars->finish.y)
			ft_close(ptr, 0, "\033[32mWin !");
		ft_check_wall(ptr, new_pos_i, new_pos, &ptr->player.pos);
	}
	else
		ft_check_all(ptr, new_pos_i, new_pos, pos);
}

static void	ft_check_new_pos_z(t_ptr *ptr, t_c new_pos, t_i new_pos_i)
{
	t_c		*pos;

	pos = &ptr->player.pos;
	if (new_pos.z != pos->z)
	{
		if (ft_in_map(ptr, new_pos_i) && pos->z > -0.2 && pos->z < 1.2)
		{
			if (pos->z < 0.6 && pos->z > 0)
			{
				if (new_pos.z > pos->z)
					pos->z = new_pos.z;
			}
			else if (pos->z < 0 && new_pos.z > pos->z)
				;
			else if (!(ptr->pars->map[new_pos_i.y][new_pos_i.x] == 0) && \
				new_pos.z < pos->z)
				;
			else
				pos->z = new_pos.z;
		}
		else
			pos->z = new_pos.z;
	}
}

void	ft_check_new_pos(t_ptr *ptr, t_c new_pos)
{
	t_i		new_pos_i;
	t_c		*pos;
	t_i		pos_i;

	pos_i.x = (int)ptr->player.pos.x;
	pos_i.y = (int)ptr->player.pos.y;
	pos = &ptr->player.pos;
	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (ft_in_map(ptr, new_pos_i) && ft_in_map(ptr, pos_i) && pos->z > 0 && pos->z < 1)
		ft_check(ptr, new_pos_i, new_pos);
	else
	{
		pos->x = new_pos.x;
		pos->y = new_pos.y;
	}
	ft_create_plan_sprite(ptr);
	ft_check_new_pos_z(ptr, new_pos, new_pos_i);
}
