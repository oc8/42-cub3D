/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:37:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/04 18:27:42 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		ft_in_map(t_ptr *ptr, t_i coordinate)
{
	if (coordinate.x < 0 || coordinate.y < 0)
		return (0);
	if (coordinate.x >= ptr->pars->nbr_map.x || coordinate.y >= ptr->pars->nbr_map.y)
		return (0);
	return (1);
}
