/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:58:22 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/18 17:27:26 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_plan		ft_new_plan(char x_y, int c)
{
	t_plan		plan;

	if (x_y == 'x')
	{
		plan.a = 1;
		plan.b = 0;
		plan.c = 0;
	}
	else
	{
		plan.a = 0;
		plan.b = 1;
		plan.c = 0;
	}
	plan.d = -c;
	return (plan);
}

int			ft_create_plan(t_ptr *ptr)
{
	ft_create_plans_x(ptr);
	ft_create_plans_y(ptr);
	return (0);
}
