/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:38:21 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:18:51 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

struct timeval	ft_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time);
}

static float	ft_time_diff_ms(struct timeval t1, struct timeval t0)
{
	return ((t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) \
		/ 1000.0f);
}

struct timeval	ft_time(t_cub *cub, char *str, int *count)
{
	struct timeval	time_now;
	float			delta;
	static int		time_fps = 0;

	time_now = ft_time_now();
	if (!cub->time.tv_sec && !cub->time.tv_usec)
		return (time_now);
	delta = ft_time_diff_ms(time_now, cub->time) / 1000.0f;
	if (ft_time_diff_ms(time_now, cub->last_second) > 1000)
	{
		time_fps = *count;
		*count = 0;
		cub->last_second = ft_time_now();
	}
	sprintf(str, "FPS : %i", time_fps);
	if (cub->key.maj)
		cub->player.speed = 6 * delta;
	else
		cub->player.speed = 3 * delta;
	if (cub->key.ctrl)
		cub->player.speed /= 2;
	cub->delta = delta;
	return (time_now);
}
