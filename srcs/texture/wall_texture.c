/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:54:11 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/26 20:50:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_wall_texture(t_c pixel, t_img img, char axe)
{
	t_i_signed	index;

	if (axe == 'y')
		index.x = (pixel.x - (int)pixel.x) * img.w;
	else
		index.x = (pixel.y - (int)pixel.y) * img.w;
	index.y = (S_W - pixel.z) * (img.h / S_W);
	if (index.x < img.w && index.y < img.h * S_W && index.x > 0 && index.y > 0)
		return (img.pixels[index.y * (img.s_l / 4) + index.x]);
	return (0);
}
