/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:47:06 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_malloc_sprite(t_cub *ptr)
{
	unsigned int	y;
	unsigned int	x;
	int				nbr;

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

void	ft_pos_sprite(t_cub *ptr)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	t_sprite		*p;

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
