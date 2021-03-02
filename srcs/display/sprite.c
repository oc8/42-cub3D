/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:47:06 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/02 18:05:59 by odroz-ba         ###   ########lyon.fr   */
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

// int		ft_texture_sprite(t_ptr *ptr, t_c pixel)
// {
// 	(void)ptr;
// 	(void)pixel;
// 	return (0);
// }

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
				p[i].a = (x + 0.5) - ptr->pos.x;
				p[i].b = (y + 0.5) - ptr->pos.y;
				p[i].c = 0;
				p[i].d = - p[i].a * (x + 0.5) - p[i].b * (y + 0.5) - p[i].c * 0.5;
				i++;
				// printf("\t\t\t\t\t%d\n", ptr->pars->plans_sprite[i].index.y);
			}
	}
}

static unsigned int	ft_check_sprite(t_ptr *ptr, t_img *sprite, t_c *pixel, t_i index)
{
	t_i		i_img;
	unsigned int		rs;
	float	ab;
	float	bc;
	float	ac;
	// center & z -> ok
	// trouver x / y
	(void)index;
	// (void)sprite;
	// (void)pixel;
	// printf("x = %f, y = %f, z = %f\n", pixel->x, pixel->y, pixel->z);
	i_img.y = (int)((2 - pixel->z) * (sprite->height * 0.5));
	ab = pixel->x - (index.x + 0.5);
	bc = pixel->y - (index.y + 0.5);
	// printf("ab = %f, bc = %f\n", ab, bc);
	if (ab > 0.5 || ab < -0.5 || bc > 0.5 || bc < -0.5)
		return (0);
	ac = bc * bc + ab * ab;
	ac = sqrt(ac);
	if (ptr->pos.y > (index.y + 0.5))
	{
		if (ab >= 0)
			ac += 0.5;
		else
			ac = 0.5 - ac;
	}
	else if (!ab)
	{
		if (bc < 0)
			ac = 0.5 - ac;
		else
			ac += 0.5;
	}
	else
	{
		if (ab >= 0)
			ac = 0.5 - ac;
		else
			ac += 0.5;
	}
	i_img.x = (int)(ac * sprite->width);
	rs = sprite->pixels[i_img.y * (int)(sprite->s_l * 0.25) + i_img.x];
	// printf("AC = %f, rs = %d\n", (sqrt(ac) + test), rs);
	// printf("rs = %d\n", rs);
	if (rs != sprite->pixels[0])
		return (rs);
	return (0);
}

static int	ft_is_sprite(t_ptr *ptr, t_c *pixel, t_c dir, float t, t_p_sprite *sprite)
{
	t_i			i_map;
	int			color;

	pixel->z = ptr->pos.z + dir.z * t;
	if (pixel->z > 0 && pixel->z < 2)
	{
		pixel->x = ptr->pos.x + dir.x * t;
		pixel->y = ptr->pos.y + dir.y * t;
		i_map.x = (int)pixel->x;
		i_map.y = (int)pixel->y;
		// printf("x = %d\ny = %d\n\n", i_map.x, i_map.y);
		if (i_map.x == sprite->index.x && i_map.y == sprite->index.y && (color = ft_check_sprite(ptr, &ptr->sprite, pixel, sprite->index)))
		{
				return (color);
		}
	}
	return (0);
}

int		ft_ray_sprite(t_ptr *ptr, t_c dir, t_c *pixel, t_p *plan, t_dist *dist)
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
			if (t > 0 && (dist->color_sprite = ft_is_sprite(ptr, pixel, dir, t, p[i])))
			{
				return (t);
			}
		}
	}
	return (0);
}
