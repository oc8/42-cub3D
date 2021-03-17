/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 18:21:25 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_sort(t_ptr *ptr)
{
	t_vector		dir;
	t_sprite		*p;
	unsigned int	i;
	t_sprite		tmp;
	float			t_max;
	unsigned int	j;

	dir = ptr->player.dir[ptr->screen.h / 2 * (ptr->screen.s_l / 4)\
			+ ptr->screen.w / 2];
	dir = ft_rotation(dir, &ptr->agl, ptr);
	p = ptr->pars->plans_sprite;
	t_max = 0;
	i = -1;
	while (++i < ptr->pars->nbr_sprite)
		p[i].t = p[i].a * dir.x + p[i].b * dir.y + p[i].c * dir.z / p[i].rs;
	j = -1;
	while (++j < ptr->pars->nbr_sprite - 1)
	{
		i = -1;
		while (++i < ptr->pars->nbr_sprite - 1)
		{
			if (p[i].t > p[i + 1].t)
			{
				tmp = p[i];
				p[i] = p[i + 1];
				p[i + 1] = tmp;
			}
		}
	}
}

void	ft_create_plan_sprite(t_ptr *ptr)
{
	unsigned int	i;
	t_sprite		*p;
	t_c				*pos;
	t_c				new_pos;

	pos = &ptr->player.pos;
	i = 0;
	while (i < ptr->pars->nbr_sprite)
	{
		p = &ptr->pars->plans_sprite[i];
		new_pos.x = p->pos.x - ((p->pos.x - pos->x) * ptr->delta / 2);
		new_pos.y = p->pos.y - ((p->pos.y - pos->y) * ptr->delta / 2);
		if (ptr->key.m)
			ft_check_new_pos_sprite(ptr, new_pos, p);
		p->a = p->pos.x - pos->x;
		p->b = p->pos.y - pos->y;
		p->c = 0;
		p->d = -p->a * p->pos.x - p->b * p->pos.y;
		p->rs = -(p->a * pos->x + p->b * pos->y + p->c * pos->z + p->d);
		i++;
	}
	if (ptr->pars->nbr_sprite)
		ft_sort(ptr);
}

void	ft_check_new_pos_sprite(t_ptr *ptr, t_c new_pos, t_sprite *sprite)
{
	t_i		i_pos;
	t_i		new_pos_i;
	t_i		pos_player;

	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	i_pos.x = (int)sprite->pos.x;
	i_pos.y = (int)sprite->pos.y;
	if (!(new_pos_i.x < ptr->pars->nbr_map.x && new_pos_i.y < ptr->pars->nbr_map.y &&\
		new_pos_i.x >= 0 && new_pos_i.y >= 0))
		return ;
	if (ptr->pars->map[new_pos_i.y][new_pos_i.x] != '1' &&\
			ptr->pars->map[new_pos_i.y][i_pos.x] != '1' && ptr->pars->map[i_pos.y]\
			[new_pos_i.x] != '1')
	{
		sprite->pos.x = new_pos.x;
		sprite->pos.y = new_pos.y;
	}
	else if (ptr->pars->map[new_pos_i.y][i_pos.x] != '1')
		sprite->pos.y = new_pos.y;
	else if (ptr->pars->map[i_pos.y][new_pos_i.x] != '1')
		sprite->pos.x = new_pos.x;
	pos_player.x = ptr->player.pos.x;
	pos_player.y = ptr->player.pos.y;
	if (new_pos_i.x == pos_player.x && new_pos_i.y == pos_player.y && !(int)ptr->player.pos.z)
		ptr->nbr_life -= (int)(100 * ptr->delta);
}
