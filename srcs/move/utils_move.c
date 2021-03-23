/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:30:37 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_wall(t_cub *ptr, t_i new_pos_i, t_c new_pos, t_c *pos)
{
	t_i		pos_i;
	char	**map;
	float	lst[1];

	lst[0] = '1';
	pos_i.x = (unsigned int)pos->x;
	pos_i.y = (unsigned int)pos->y;
	map = ptr->pars->map;
	if (ft_cmp_dif_flt(map[new_pos_i.y][new_pos_i.x], lst, 1) && \
			ft_cmp_dif_flt(map[new_pos_i.y][pos_i.x], lst, 1) && \
			ft_cmp_dif_flt(map[pos_i.y][new_pos_i.x] , lst, 1))
	{
		pos->x = new_pos.x;
		pos->y = new_pos.y;
	}
	else if (ft_cmp_dif_flt(map[new_pos_i.y][pos_i.x], lst, 1))
		pos->y = new_pos.y;
	else if (ft_cmp_dif_flt(map[pos_i.y][new_pos_i.x] , lst, 1))
		pos->x = new_pos.x;
}

static void	ft_check_all(t_cub *ptr, t_i npos_i, t_c npos, t_i pos)
{
	char	**map;
	float	lst[2];

	lst[0] = 0;
	lst[1] = '0';
	map = ptr->pars->map;
	if (ft_cmp_equal_flt(map[npos_i.y][npos_i.x], lst, 2) && \
		ft_cmp_equal_flt(map[npos_i.y][pos.x], lst, 2) && \
		ft_cmp_equal_flt(map[pos.y][npos_i.x], lst, 2))
	{
		ptr->player.pos.x = npos.x;
		ptr->player.pos.y = npos.y;
	}
	else if (ft_cmp_equal_flt(map[npos_i.y][pos.x], lst, 2))
		ptr->player.pos.y = npos.y;
	else if (ft_cmp_equal_flt(map[pos.y][npos_i.x], lst, 2))
		ptr->player.pos.x = npos.x;
}

static void	ft_check(t_cub *ptr, t_i new_pos_i, t_c new_pos)
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

static void	ft_check_new_pos_z(t_cub *ptr, t_c new_pos, t_i new_pos_i)
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

void	ft_check_new_pos(t_cub *ptr, t_c new_pos)
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
