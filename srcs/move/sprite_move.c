/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/22 16:00:05 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_switch(t_sprite *p1, t_sprite *p2)
{
	t_sprite		tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static void	ft_sort(t_ptr *ptr)
{
	t_vector		dir;
	t_sprite		*p;
	unsigned int	i;
	float			t_max;
	unsigned int	j;

	dir = ptr->player.dir[ptr->screen.h / 2 * (ptr->screen.s_l / 4) \
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
				ft_switch(&p[i], &p[i + 1]);
		}
	}
}

void	ft_create_plan_sprite(t_ptr *ptr)
{
	unsigned int	i;
	t_sprite		*p;
	t_c				*player_pos;
	t_c				new_pos;

	player_pos = &ptr->player.pos;
	i = 0;
	while (i < ptr->pars->nbr_sprite)
	{
		p = &ptr->pars->plans_sprite[i];
		new_pos.x = p->pos.x - ((p->pos.x - player_pos->x) * ptr->delta / 2);
		new_pos.y = p->pos.y - ((p->pos.y - player_pos->y) * ptr->delta / 2);
		if (ptr->key.m)
			ft_check_new_pos_sprite(ptr, new_pos, p);
		p->a = p->pos.x - player_pos->x;
		p->b = p->pos.y - player_pos->y;
		p->c = 0;
		p->d = -p->a * p->pos.x - p->b * p->pos.y;
		p->rs = -(p->a * player_pos->x + p->b * player_pos->y + p->c * \
			player_pos->z + p->d);
		i++;
	}
	if (ptr->pars->nbr_sprite)
		ft_sort(ptr);
	// i = -1;
	// while (++i < ptr->pars->nbr_sprite)
	// 	printf("t = %f\n", ptr->pars->plans_sprite[i].t);
}

void	ft_check_new_pos_sprite(t_ptr *ptr, t_c new_pos, t_sprite *sprite)
{
	t_i		new_pos_i;
	t_i		pos;

	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (!(new_pos_i.x < ptr->pars->nbr_map.x && new_pos_i.y < \
			ptr->pars->nbr_map.y && new_pos_i.x >= 0 && new_pos_i.y >= 0))
		return ;
	ft_check_wall(ptr, new_pos_i, new_pos, &sprite->pos);
	pos.x = ptr->player.pos.x;
	pos.y = ptr->player.pos.y;
	if (new_pos_i.x == pos.x && new_pos_i.y == pos.y && !(int)ptr->player.pos.z)
		ptr->nbr_life -= (int)(100 * ptr->delta);
}
