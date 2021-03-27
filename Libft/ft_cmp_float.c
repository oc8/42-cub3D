/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:36:47 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/27 17:41:38 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_cmp_equal_flt(float c, float *lst, unsigned int nbr)
{
	unsigned int	i;

	i = -1;
	while (++i < nbr)
		if (c == lst[i])
			return (1);
	return (0);
}

char	ft_cmp_dif_flt(float c, float *lst, unsigned int nbr)
{
	unsigned int	i;

	i = -1;
	while (++i < nbr)
		if (c == lst[i])
			return (0);
	return (1);
}
