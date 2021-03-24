/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/24 19:54:02 by odroz-ba         ###   ########lyon.fr   */
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

static void	ft_sort(t_cub *cub)
{
	t_vector		dir;
	t_sprite		*p;
	unsigned int	i;
	float			t_max;
	unsigned int	j;

	dir = cub->player.dir[cub->screen.h / 2 * (cub->screen.s_l / 4) \
			+ cub->screen.w / 2];
	dir = ft_rotation(dir, &cub->agl, cub);
	p = cub->pars->plans_sprite;
	t_max = 0;
	i = -1;
	while (++i < cub->pars->nbr_sprite)
		p[i].t = p[i].a * dir.x + p[i].b * dir.y + p[i].c * dir.z / p[i].rs;
	j = -1;
	while (++j < cub->pars->nbr_sprite - 1)
	{
		i = -1;
		while (++i < cub->pars->nbr_sprite - 1)
		{
			if (p[i].t > p[i + 1].t)
				ft_switch(&p[i], &p[i + 1]);
		}
	}
}

void		ft_check_new_pos_sprite(t_cub *cub, t_sprite *p)
{
	t_i	new_pos_i;
	t_i	pos;
	t_c	*player_pos;
	t_c	new_pos;

	player_pos = &cub->player.pos;
	new_pos.x = p->pos.x - ((p->pos.x - player_pos->x) * cub->delta / 2);
	new_pos.y = p->pos.y - ((p->pos.y - player_pos->y) * cub->delta / 2);
	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (!(new_pos_i.x < cub->pars->nbr_map.x && new_pos_i.y < \
			cub->pars->nbr_map.y && new_pos_i.x >= 0 && new_pos_i.y >= 0))
		return ;
	ft_check_wall(cub, new_pos_i, new_pos, &p->pos);
	pos.x = cub->player.pos.x;
	pos.y = cub->player.pos.y;
	if (new_pos_i.x == pos.x && new_pos_i.y == pos.y && !(int)cub->player.pos.z)
		cub->nbr_life -= (int)(100 * cub->delta);
}

void		ft_create_plan_sprite(t_cub *cub)
{
	unsigned int	i;
	t_sprite		*p;
	t_c				*player_pos;

	player_pos = &cub->player.pos;
	i = 0;
	while (i < cub->pars->nbr_sprite)
	{
		p = &cub->pars->plans_sprite[i];
		if (cub->key.m)
			ft_check_new_pos_sprite(cub, p);
		p->a = p->pos.x - player_pos->x;
		p->b = p->pos.y - player_pos->y;
		p->c = 0;
		p->d = -p->a * p->pos.x - p->b * p->pos.y;
		p->rs = -(p->a * player_pos->x + p->b * player_pos->y + p->c * \
			player_pos->z + p->d);
		i++;
	}
	if (cub->pars->nbr_sprite)
		ft_sort(cub);
}
