/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:56:04 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/30 15:32:02 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t n)
{
	char			*strdst;
	char			*strsrc;

	strdst = (char*)dst;
	strsrc = (char*)src;
	if (dst == src)
		return (dst);
	while (n--)
	{
		if (dst - src < 0)
			*strdst++ = *strsrc++;
		else
			strdst[n] = strsrc[n];
	}
	return (dst);
}
