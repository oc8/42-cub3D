/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:05:17 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/30 15:32:02 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*src1;
	char	*src2;

	src1 = (char*)s1;
	src2 = (char*)s2;
	while (n--)
	{
		if (*src1 != *src2)
			return ((unsigned char)*src1 - (unsigned char)*src2);
		src1++;
		src2++;
	}
	return (0);
}
