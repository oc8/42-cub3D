/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:47:06 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/11 18:35:14 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_init_index_sprite(t_ptr *ptr)
{
	int			y;
	int			x;
	int			i;
	t_sprite	*p;

	i = 0;
	y = -1;
	while (++y < ptr->pars->nbr_map.y)
	{
		x = -1;
		while (++x < ptr->pars->nbr_map.x)
			if (ptr->pars->map[y][x] == 2)
			{
				p = ptr->pars->plans_sprite;
				p[i].index.y = y;
				p[i].index.x = x;
				i++;
			}
	}
}

void	ft_malloc_sprite(t_ptr *ptr)
{
	int		y;
	int		x;
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
	ft_init_index_sprite(ptr);
}

t_sprite	*ft_search_sprite(t_ptr *ptr, int y, int x)
{
	unsigned int	i;

	i = 0;
	while (i < ptr->pars->nbr_sprite && !(ptr->pars->plans_sprite[i].index.x \
		== x && ptr->pars->plans_sprite[i].index.y == y))
		i++;
	return (&ptr->pars->plans_sprite[i]);
}

void	ft_create_plan_sprite(t_ptr *ptr)
{
	int		y;
	int		x;
	int		i;
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
				p->a = (x + 0.5) - ptr->player.pos.x;//pos
				p->b = (y + 0.5) - ptr->player.pos.y;
				p->c = 0;
				p->d = -p->a * (x + 0.5) - p->b * (y + 0.5);
				i++;
			}
	}
}

static int	ft_is_sprite(t_ptr *ptr, t_c *pixel, t_vector dir, float t, t_sprite *sprite)
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
		if (i_map.x == sprite->index.x && i_map.y == sprite->index.y)
		{
			color = ft_sprite_texture(ptr, &ptr->sprite, pixel, sprite->index);
			if (color)
				return (color);
		}
	}
	return (0);
}

float	ft_ray_sprite(t_ptr *ptr, t_vector dir, t_dist *dist, float small_dist)
{
	t_sprite		*p;
	float			rs_dir;
	float			t;
	unsigned int	i;

	i = 0;
	while (i < ptr->pars->nbr_sprite)
	{
		p = &ptr->pars->plans_sprite[i];
		rs_dir = p->a * dir.x + p->b * dir.y + p->c * dir.z;
		if (rs_dir)
		{
			t = -(p->a * ptr->player.pos.x + p->b * ptr->player.pos.y + p->c * ptr->player.pos.z + p->d) / rs_dir;
			if (t > small_dist)
				return (0);
			if (t > 0)
			{
				dist->color_sprite = ft_is_sprite(ptr, &dist->pixel, dir, t, p);
				if (dist->color_sprite)
					return (t);
			}
		}
		i++;
	}
	return (0);
}
