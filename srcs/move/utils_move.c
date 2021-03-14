/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:30:37 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/14 16:30:54 by odroz-ba         ###   ########lyon.fr   */
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
			[new_pos_i.x]) || ptr->player.pos.z > 1 || ptr->player.pos.z < 0)
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
			else if (!ptr->pars->map[new_pos_i.y][new_pos_i.x])
				pos->z = new_pos.z;
		}
		else
			pos->z = new_pos.z;
	}
}

void		ft_check_new_pos(t_ptr *ptr, t_c new_pos)
{
	t_i		new_pos_i;
	t_c		*pos;

	pos = &ptr->player.pos;
	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (ft_in_map(ptr, new_pos_i))
		ft_check(ptr, new_pos_i, new_pos);
	else if (pos->x != new_pos.x || pos->y != new_pos.y)
	{
		pos->x = new_pos.x;
		pos->y = new_pos.y;
		ft_create_plan_sprite(ptr);
	}
	ft_check_new_pos_z(ptr, new_pos, new_pos_i);
}