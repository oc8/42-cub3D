/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:06:41 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/30 15:35:43 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*rs;
	size_t	i;

	if (!s1 || !s2 ||
	!(rs = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	i = 0;
	i = ft_strlcpy(&rs[i], s1, 10000);
	i = ft_strlcpy(&rs[i], s2, 10000);
	return (rs);
}
