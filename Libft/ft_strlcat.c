/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:13:33 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/02 18:49:47 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strnlen(char *str, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && str[i] != '\0')
		i++;
	return (i);
}

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l;

	l = ft_strnlen(dest, size);
	if (l == size)
		return (l + ft_strlen(src));
	return (l + ft_strlcpy(dest + l, src, size - l));
}
