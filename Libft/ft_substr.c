/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:08 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/30 15:36:06 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*rs;
	size_t		i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start || len == 0)
	{
		if (!(rs = malloc(sizeof(char))))
			return (0);
		*rs = 0;
		return (rs);
	}
	if ((size_t)ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	if (!(rs = malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len && s[start])
	{
		rs[i] = s[start];
		start++;
		i++;
	}
	rs[i] = '\0';
	return (rs);
}
