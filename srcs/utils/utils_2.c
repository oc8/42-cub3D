/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:46:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/15 17:47:18 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_init_struct(t_ptr *ptr)
{
	ptr->epars = 0;
	ptr->player.speed = 0.5;
	ptr->pars->nbr_sprite = 0;
	ptr->time.tv_sec = 0;
	ptr->time.tv_usec = 0;
	ptr->last_second = ft_time_now();
	return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
