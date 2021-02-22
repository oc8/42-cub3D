/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:37:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/02/12 12:02:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	*ft_check_calloc(t_ptr *ptr, size_t nmemb, size_t size)
{
	void	*rs;

	rs = ft_calloc(nmemb, size);
	if (!rs)
		ft_close(ptr, 1);
	return (rs);
}
