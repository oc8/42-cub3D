/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:56:44 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/10 16:01:50 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_witch_texture_x(t_ptr *ptr, t_c pixel, t_vector dir)
{
	if (dir.x < 0)
		return (ft_wall_texture(pixel, ptr->we, 'x'));
	else
		return (ft_wall_texture(pixel, ptr->ea, 'x'));
}

static int	ft_witch_texture_y(t_ptr *ptr, t_c pixel, t_vector dir)
{
	if (dir.y < 0)
		return (ft_wall_texture(pixel, ptr->no, 'y'));
	else
		return (ft_wall_texture(pixel, ptr->so, 'y'));
}

unsigned int	ft_nearest_wall(t_ptr *ptr, t_vector dir, t_dist x, t_dist y)
{
	if (x.t && y.t)
	{
		if (x.t < y.t)
			return (ft_witch_texture_x(ptr, x.pixel, dir));
		else
			return (ft_witch_texture_y(ptr, y.pixel, dir));
	}
	else if (y.t)
		return (ft_witch_texture_y(ptr, y.pixel, dir));
	else if (x.t)
		return (ft_witch_texture_x(ptr, x.pixel, dir));
	return (0);
}
