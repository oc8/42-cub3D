/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:47:06 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/24 13:34:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	ft_malloc_sprite(t_ptr *ptr) /////
{
	int		y;
	int		x;
	int		i;

	y = -1;
	while (++y < ptr->pars->nbr_map.y)
	{
		x = -1;
		while (++x < ptr->pars->nbr_map.x)
			if (ptr->pars->map[y][x] == 2)
				ptr->pars->nbr_sprite += 1;
	}
	ptr->pars->plans_sprite = ft_check_calloc(ptr, ptr->pars->nbr_sprite, sizeof(t_p_sprite));
	ptr->emalloc |= e_sprite;
	
	t_p_sprite	*p;

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

t_p_sprite	*ft_search_sprite(t_ptr *ptr, int y, int x)
{
	int		i;

	i = 0;
	while (/*i < ptr->pars->nbr_sprite && */!(ptr->pars->plans_sprite[i].index.x == x && ptr->pars->plans_sprite[i].index.y == y))
		i++;
	return (&ptr->pars->plans_sprite[i]);
}

void	ft_create_plan_sprite(t_ptr *ptr)
{
	int		y;
	int		x;
	int		i;
	t_p_sprite	*p;

	i = 0;
	y = -1;
	while (++y < ptr->pars->nbr_map.y)
	{
		x = -1;
		while (++x < ptr->pars->nbr_map.x)
			if (ptr->pars->map[y][x] == 2)
			{
				p = ptr->pars->plans_sprite;
				p[i].a = ptr->dir->x;
				p[i].b = ptr->dir->y;
				p[i].c = ptr->dir->z;
				p[i].d = - p[i].a * ptr->pos.x - p[i].b * ptr->pos.y - p[i].c * ptr->pos.z;
				i++;
				// printf("\t\t\t\t\t%d\n", ptr->pars->plans_sprite[i].index.y);
			}
	}
}

static int	ft_check_sprite(t_ptr *ptr)
{
	(void)ptr;
	// center & z -> ok
	// trouver x / y
	return (1);
}

static int	ft_is_sprite(t_ptr *ptr, t_c *pixel, t_c dir, float t, t_i index)
{
	t_i			i_map;

	pixel->z = ptr->pos.z + dir.z * t;
	if (pixel->z > 0 && pixel->z < 1)
	{
		pixel->x = ptr->pos.x + dir.x * t;
		pixel->y = ptr->pos.y + dir.y * t;
		i_map.x = (int)pixel->x;
		i_map.y = (int)pixel->y;
		// printf("x = %d\ny = %d\n\n", i_map.x, i_map.y);
		if (i_map.x == index.x && i_map.y == index.y && ft_check_sprite(ptr))
		{
				return (1);
		}
	}
	return (0);
}

int		ft_ray_sprite(t_ptr *ptr, t_c dir, t_c *pixel, t_p *plan)
{
	t_p_sprite		**p;
	float			rs_dir;
	float			t;
	unsigned int	i;

	p = plan->sprite;
	i = -1;
	while (++i < plan->nbr)
	{
		rs_dir = p[i]->a * dir.x + p[i]->b * dir.y + p[i]->c * dir.z;
		if (rs_dir)
		{
			t = - (p[i]->a * ptr->pos.x + p[i]->b * ptr->pos.y + p[i]->c * ptr->pos.z + p[i]->d) / rs_dir;
			// printf("t = %f\n", t);
			if (t > 0 && ft_is_sprite(ptr, pixel, dir, t, p[i]->index))
			{
				return (t);
			}
		}
	}
	return (0);
}
