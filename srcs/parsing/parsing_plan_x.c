/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plan_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:22:29 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/07 17:00:08 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_add_sprite_x(t_ptr *ptr, t_plan *plan, int x)
{
	int		y;
	int		j;

	j = 0;
	y = -1;
	while (++y < ptr->pars->nbr_map.y)
		if (ptr->pars->map[y][x] == 2)
			j++;
	plan->sprite = ft_calloc_lst(ptr, j, sizeof(t_plan*));
	j = -1;
	y = -1;
	while (++y < ptr->pars->nbr_map.y)
		if (ptr->pars->map[y][x] == 2)
			plan->sprite[++j] = ft_search_sprite(ptr, y, x);
	plan->nbr = ++j;
}

static int	ft_is_we_wall(t_ptr *ptr, int x)
{
	int		y;

	y = -1;
	while (++y < ptr->pars->nbr_map.y)
		if (ptr->pars->map[y][x - 1] == '1' && ptr->pars->map[y][x] != '1')
			return (1);
	return (0);
}

static int	ft_is_ea_wall(t_ptr *ptr, int x)
{
	int		y;

	y = -1;
	while (++y < ptr->pars->nbr_map.y)
		if (ptr->pars->map[y][x - 1] != '1' && ptr->pars->map[y][x] == '1')
			return (1);
	return (0);
}

void		ft_create_plans_x(t_ptr *ptr)
{
	int		x;
	int		i;

	ptr->pars->plans_we = ft_calloc_lst(ptr, ptr->pars->nbr_map.x, sizeof(t_plan));
	ptr->pars->plans_ea = ft_calloc_lst(ptr, ptr->pars->nbr_map.x, sizeof(t_plan));

	i = 0;
	x = 0;
	ptr->pars->plans_we[i].d = 0;
	ptr->pars->plans_ea[i].d = 0;
	while (++x < ptr->pars->nbr_map.x)
	{
		i++;
		if (ft_is_we_wall(ptr, x))
			ptr->pars->plans_we[i] = ft_new_plan('x', x);
		else
			ptr->pars->plans_we[i].d = 0;
		ft_add_sprite_x(ptr, &ptr->pars->plans_we[i], x);
		if (ft_is_ea_wall(ptr, x))
			ptr->pars->plans_ea[i] = ft_new_plan('x', x);
		else
			ptr->pars->plans_ea[i].d = 0;
		ft_add_sprite_x(ptr, &ptr->pars->plans_ea[i], x);
	}
}