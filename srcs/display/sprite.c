/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:47:06 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/16 17:18:32 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_malloc_sprite(t_ptr *ptr)
{
	unsigned int	y;
	unsigned int	x;
	int		nbr;

	nbr = ptr->pars->nbr_sprite;
	y = -1;
	while (++y < ptr->pars->nbr_map.y)
	{
		x = -1;
		while (++x < ptr->pars->nbr_map.x)
			if (ptr->pars->map[y][x] == 2)
				nbr += 1;
	}
	ptr->pars->plans_sprite = ft_calloc_lst(ptr, nbr, sizeof(t_sprite));
	ptr->pars->nbr_sprite = nbr;
}

void	ft_pos_sprite(t_ptr *ptr)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	t_sprite	*p;

	i = 0;
	y = -1;
	while (++y < ptr->pars->nbr_map.y)
	{
		x = -1;
		while (++x < ptr->pars->nbr_map.x)
			if (ptr->pars->map[y][x] == 2)
			{
				p = &ptr->pars->plans_sprite[i];
				p->pos.x = (x + 0.5);
				p->pos.y = (y + 0.5);
				i++;
			}
	}
}

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
		new_pos.x = p->pos.x - ((p->pos.x + 0.05 - pos->x) * ptr->delta / 2);
		new_pos.y = p->pos.y - ((p->pos.y + 0.05 - pos->y) * ptr->delta / 2);
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

int		ft_is_sprite(t_ptr *ptr, t_c *pixel, t_vector dir, float t, t_sprite *sprite)
{
	t_i			i_map;
	int			color;

	pixel->z = ptr->player.pos.z + dir.z * t;
	if (pixel->z > 0 && pixel->z < 2)
	{
		pixel->x = ptr->player.pos.x + dir.x * t;
		pixel->y = ptr->player.pos.y + dir.y * t;
		i_map.x = (int)pixel->x;
		i_map.y = (int)pixel->y;
		// if (i_map.x == (int)sprite->pos.x && i_map.y == (int)sprite->pos.y)
		// {
			color = ft_sprite_texture(ptr, &ptr->sprite, pixel, sprite);
			if (color)
				return (color);
		// }
	}
	return (0);
}
