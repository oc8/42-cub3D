/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_y_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:22:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_no_wall(t_cub *ptr, unsigned int y)
{
	unsigned int	x;

	if (y < 1)
		return (1);
	x = -1;
	while (++x < ptr->pars->nbr_map.x)
		if (ptr->pars->map[y - 1][x] == '1' && ptr->pars->map[y][x] != '1')
			return (1);
	return (0);
}

static int	ft_is_so_wall(t_cub *ptr, unsigned int y)
{
	unsigned int	x;

	if (y < 1)
		return (1);
	x = -1;
	while (++x < ptr->pars->nbr_map.x)
		if (ptr->pars->map[y - 1][x] != '1' && ptr->pars->map[y][x] == '1')
			return (1);
	return (0);
}

void		ft_create_plans_y(t_cub *ptr)
{
	unsigned int	y;
	unsigned int	i;
	unsigned int	nbr_plan;

	nbr_plan = ptr->pars->nbr_map.y;
	ptr->pars->plans_no = ft_calloc_lst(ptr, nbr_plan + 1, sizeof(t_plan));
	ptr->pars->plans_so = ft_calloc_lst(ptr, nbr_plan + 1, sizeof(t_plan));
	i = -1;
	y = -1;
	// ptr->pars->plans_no[i].d = 0;
	// ptr->pars->plans_so[i].d = 0;
	while (++y < nbr_plan)
	{
		i++;
		if (ft_is_no_wall(ptr, y))
			ptr->pars->plans_no[i] = ft_new_plan('y', y);
		else
			ptr->pars->plans_no[i].d = 0;
		if (ft_is_so_wall(ptr, y))
			ptr->pars->plans_so[i] = ft_new_plan('y', y);
		else
			ptr->pars->plans_so[i].d = 0;
	}
	ptr->pars->plans_so[++i] = ft_new_plan('y', y);
	ptr->pars->plans_no[i] = ft_new_plan('y', y);
}
