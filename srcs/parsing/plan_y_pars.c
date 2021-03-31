/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_y_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:22:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/31 17:25:08 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_no_wall(t_cub *cub, unsigned int y)
{
	unsigned int	x;

	if (y < 1)
		return (1);
	x = -1;
	while (++x < cub->pars->nbr_map.x)
		if (cub->pars->map[y - 1][x] == '1' && cub->pars->map[y][x] != '1')
			return (1);
	return (0);
}

static int	ft_is_so_wall(t_cub *cub, unsigned int y)
{
	unsigned int	x;

	if (y < 1)
		return (1);
	x = -1;
	while (++x < cub->pars->nbr_map.x)
		if (cub->pars->map[y - 1][x] != '1' && cub->pars->map[y][x] == '1')
			return (1);
	return (0);
}

void		ft_create_plans_y(t_cub *cub)
{
	unsigned int	y;
	unsigned int	i;
	unsigned int	nbr_plan;

	nbr_plan = cub->pars->nbr_map.y;
	cub->pars->plans_no = ft_calloc_lst(cub, nbr_plan + 1, sizeof(t_plan));
	cub->pars->plans_so = ft_calloc_lst(cub, nbr_plan + 1, sizeof(t_plan));
	i = 0;
	y = -1;
	while (++y < nbr_plan)
	{
		if (ft_is_no_wall(cub, y))
			cub->pars->plans_no[i] = ft_new_plan('y', y);
		else
			cub->pars->plans_no[i].d = 1;
		if (ft_is_so_wall(cub, y))
			cub->pars->plans_so[i] = ft_new_plan('y', y);
		else
			cub->pars->plans_so[i].d = 1;
		i++;
	}
	cub->pars->plans_so[i] = ft_new_plan('y', y);
	cub->pars->plans_no[i] = ft_new_plan('y', y);
}
