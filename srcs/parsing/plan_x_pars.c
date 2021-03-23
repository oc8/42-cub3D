/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_x_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:22:29 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:22:07 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_we_wall(t_cub *cub, unsigned int x)
{
	unsigned int	y;

	if (x < 1)
		return (1);
	y = -1;
	while (++y < cub->pars->nbr_map.y)
		if (cub->pars->map[y][x - 1] == '1' && cub->pars->map[y][x] != '1')
			return (1);
	return (0);
}

static int	ft_is_ea_wall(t_cub *cub, unsigned int x)
{
	unsigned int	y;

	if (x < 1)
		return (1);
	y = -1;
	while (++y < cub->pars->nbr_map.y)
		if (cub->pars->map[y][x - 1] != '1' && cub->pars->map[y][x] == '1')
			return (1);
	return (0);
}

void		ft_create_plans_x(t_cub *cub)
{
	unsigned int	x;
	unsigned int	i;
	unsigned int	nbr_plan;

	nbr_plan = cub->pars->nbr_map.x;
	cub->pars->plans_we = ft_calloc_lst(cub, nbr_plan + 1, sizeof(t_plan));
	cub->pars->plans_ea = ft_calloc_lst(cub, nbr_plan + 1, sizeof(t_plan));
	i = -1;
	x = -1;
	// cub->pars->plans_we[i].d = 0;
	// cub->pars->plans_ea[i].d = 0;
	while (++x < nbr_plan)
	{
		i++;
		if (ft_is_we_wall(cub, x))
			cub->pars->plans_we[i] = ft_new_plan('x', x);
		else
			cub->pars->plans_we[i].d = 0;
		if (ft_is_ea_wall(cub, x))
			cub->pars->plans_ea[i] = ft_new_plan('x', x);
		else
			cub->pars->plans_ea[i].d = 0;
	}
	cub->pars->plans_ea[++i] = ft_new_plan('x', x);
	cub->pars->plans_we[i] = ft_new_plan('x', x);
}
