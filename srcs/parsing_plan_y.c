/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plan_y.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:22:48 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/01 13:40:39 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	ft_add_sprite_y(t_ptr *ptr, t_p *plan, int y)
{
	int		x;
	int		j;

	j = 0;
	x = -1;
	while (++x < ptr->pars->nbr_map.x)
		if (ptr->pars->map[y][x] == 2)
			j++;
	plan->sprite = ft_check_calloc(ptr, j, sizeof(t_p*));
	j = -1;
	x = -1;
	while (++x < ptr->pars->nbr_map.x)
		if (ptr->pars->map[y][x] == 2)
			plan->sprite[++j] = ft_search_sprite(ptr, y, x);
	plan->nbr = ++j;
}

static int	ft_is_no_wall(t_ptr *ptr, int y)
{
	int		x;

	x = -1;
	while (++x < ptr->pars->nbr_map.x)
		if (ptr->pars->map[y - 1][x] == '1' && ptr->pars->map[y][x] != '1')
			return (1);
	return (0);
}

static int	ft_is_so_wall(t_ptr *ptr, int y)
{
	int		x;

	x = -1;
	while (++x < ptr->pars->nbr_map.x)
		if (ptr->pars->map[y - 1][x] != '1' && ptr->pars->map[y][x] == '1')
			return (1);
	return (0);
}

void		ft_create_plans_y(t_ptr *ptr)
{
	int	y;
	int	i;

	ptr->pars->plans_no = ft_check_calloc(ptr, ptr->pars->nbr_map.y, sizeof(t_p));
	ptr->pars->plans_so = ft_check_calloc(ptr, ptr->pars->nbr_map.y, sizeof(t_p));
	i = 0;
	y = 0;
	ptr->pars->plans_no[i].d = 0;
	ptr->pars->plans_so[i].d = 0;
	while (++y < ptr->pars->nbr_map.y)
	{
		i++;
		if (ft_is_no_wall(ptr, y))
			ptr->pars->plans_no[i] = ft_new_plan('y', y);
		else
			ptr->pars->plans_no[i].d = 0;
		ft_add_sprite_y(ptr, &ptr->pars->plans_no[i], y);
		if (ft_is_so_wall(ptr, y))
			ptr->pars->plans_so[i] = ft_new_plan('y', y);
		else
			ptr->pars->plans_so[i].d = 0;
		ft_add_sprite_y(ptr, &ptr->pars->plans_so[i], y);
	}
}
