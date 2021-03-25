/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:32 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/25 19:18:44 by odroz-ba         ###   ########lyon.fr   */
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
	unsigned int	j;

	dir = cub->player.dir_center;
	dir = ft_rotation(dir, &cub->agl);
	p = cub->pars->plans_sprite;
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
	t_c	*p_pos;
	t_c	new_pos;

	p_pos = &cub->player.pos;
	new_pos.x = p->pos.x - ((p->pos.x - p_pos->x) * SPEED_S * cub->delta / 2);
	new_pos.y = p->pos.y - ((p->pos.y - p_pos->y) * SPEED_S * cub->delta / 2);
	new_pos_i.x = (int)new_pos.x;
	new_pos_i.y = (int)new_pos.y;
	if (!(new_pos_i.x < cub->pars->nbr_map.x && new_pos_i.y < \
			cub->pars->nbr_map.y && new_pos_i.x >= 0 && new_pos_i.y >= 0))
		return ;
	ft_check_wall(cub, new_pos_i, new_pos, &p->pos);
	pos.x = cub->player.pos.x;
	pos.y = cub->player.pos.y;
	if (new_pos_i.x == pos.x && new_pos_i.y == pos.y && cub->player.pos.z < S_S)
		cub->nbr_life -= (int)(100 * cub->delta);
}

static void	ft_create_plan_win(t_cub *cub, t_c *p_pos)
{
	t_sprite	*p;
	t_vector	dir;

	dir = cub->player.dir[cub->scr.h / 2 * (cub->scr.s_l / 4) + cub->scr.w / 2];
	p = &cub->pars->plan_win;
	p->pos.x = cub->pars->finish.x + 0.5;
	p->pos.y = cub->pars->finish.y + 0.5;
	p_pos = &cub->player.pos;
	p->a = p->pos.x - p_pos->x;
	p->b = p->pos.y - p_pos->y;
	p->c = 0;
	p->d = -p->a * p->pos.x - p->b * p->pos.y;
	p->rs = -(p->a * p_pos->x + p->b * p_pos->y + p->c * p_pos->z + p->d);
	dir = cub->player.dir_center;
	p->t = 1;
}

void		ft_create_plan_sprite(t_cub *cub)
{
	unsigned int	i;
	t_sprite		*p;
	t_c				*p_pos;

	p_pos = &cub->player.pos;
	i = 0;
	while (i < cub->pars->nbr_sprite)
	{
		p = &cub->pars->plans_sprite[i];
		if (cub->key.m)
			ft_check_new_pos_sprite(cub, p);
		p->a = p->pos.x - p_pos->x;
		p->b = p->pos.y - p_pos->y;
		p->c = 0;
		p->d = -p->a * p->pos.x - p->b * p->pos.y;
		p->rs = -(p->a * p_pos->x + p->b * p_pos->y + p->c * p_pos->z + p->d);
		i++;
	}
	if (cub->pars->nbr_sprite)
		ft_sort(cub);
	if (cub->flag_finish)
		ft_create_plan_win(cub, p_pos);
}
