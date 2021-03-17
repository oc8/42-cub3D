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
