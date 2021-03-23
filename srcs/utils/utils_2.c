/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:46:13 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 18:56:25 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_init_struct(t_cub *cub)
{
	cub->epars = 0;
	cub->player.speed = 0.5;
	cub->pars->nbr_sprite = 0;
	cub->time.tv_sec = 0;
	cub->time.tv_usec = 0;
	cub->last_second = ft_time_now();
	cub->nbr_life = 100;
	cub->fov = 80;
	return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		ft_skip_spaces(char *line, unsigned int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}
