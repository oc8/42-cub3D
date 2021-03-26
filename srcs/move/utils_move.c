/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:30:37 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 18:00:50 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_check_wall(t_cub *cub, t_i new_pos_i, t_c new_pos, t_c *pos)
{
	t_i		pos_i;
	char	**map;
	float	lst[1];

	lst[0] = '1';
	pos_i.x = (unsigned int)pos->x;
	pos_i.y = (unsigned int)pos->y;
	map = cub->pars->map;
	if (ft_cmp_dif_flt(map[new_pos_i.y][new_pos_i.x], lst, 1) && \
			ft_cmp_dif_flt(map[new_pos_i.y][pos_i.x], lst, 1) && \
			ft_cmp_dif_flt(map[pos_i.y][new_pos_i.x], lst, 1))
	{
		pos->x = new_pos.x;
		pos->y = new_pos.y;
	}
	else if (ft_cmp_dif_flt(map[new_pos_i.y][pos_i.x], lst, 1))
		pos->y = new_pos.y;
	else if (ft_cmp_dif_flt(map[pos_i.y][new_pos_i.x], lst, 1))
		pos->x = new_pos.x;
}

static void	ft_check_all(t_cub *cub, t_i npos_i, t_c npos, t_i pos)
{
	char	**map;
	float	lst[2];

	lst[0] = 0;
	lst[1] = '0';
	map = cub->pars->map;
	if (ft_cmp_equal_flt(map[npos_i.y][npos_i.x], lst, 2) && \
		ft_cmp_equal_flt(map[npos_i.y][pos.x], lst, 2) && \
		ft_cmp_equal_flt(map[pos.y][npos_i.x], lst, 2))
	{
		cub->player.pos.x = npos.x;
		cub->player.pos.y = npos.y;
	}
	else if (ft_cmp_equal_flt(map[npos_i.y][pos.x], lst, 2))
		cub->player.pos.y = npos.y;
	else if (ft_cmp_equal_flt(map[pos.y][npos_i.x], lst, 2))
		cub->player.pos.x = npos.x;
}

static void	ft_check(t_cub *cub, t_i new_pos_i, t_c new_pos)
{
	t_i		pos;

	pos.x = (unsigned int)cub->player.pos.x;
	pos.y = (unsigned int)cub->player.pos.y;
	if (cub->key.m)
	{
		if (pos.x == cub->pars->finish.x && pos.y == cub->pars->finish.y)
			cub->flag_win = 1;
		ft_check_wall(cub, new_pos_i, new_pos, &cub->player.pos);
	}
	else
		ft_check_all(cub, new_pos_i, new_pos, pos);
}

static void	ft_check_new_pos_z(t_cub *cub, t_c new_pos, t_i new_pos_i)
{
	t_c		*pos;

	(void)new_pos_i;
	pos = &cub->player.pos;
	if (pos->z < S_P + 0.1 && pos->z > 0 && new_pos.z > pos->z)
		pos->z = new_pos.z;
	else if (pos->z < 0 && new_pos.z > pos->z)
		;
	else
		pos->z = new_pos.z;
}

void		ft_check_new_pos(t_cub *cub, t_c new_pos)
{
	t_i		new_pos_i;
	t_c		*pos;
	t_i		pos_i;

	pos_i.x = (int)cub->player.pos.x;
	pos_i.y = (int)cub->player.pos.y;
	pos = &cub->player.pos;
	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (ft_in_map(cub, new_pos_i) && pos->z > 0 && pos->z < S_W + S_P)
	{
		if (cub->pars->map[pos_i.y][pos_i.x] == '1')
			new_pos.z = S_W + S_P;
		ft_check(cub, new_pos_i, new_pos);
		ft_check_new_pos_z(cub, new_pos, new_pos_i);
	}
	else
	{
		pos->x = new_pos.x;
		pos->y = new_pos.y;
		pos->z = new_pos.z;
	}
	ft_create_plan_sprite(cub);
}
