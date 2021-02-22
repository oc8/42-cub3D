/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:43:50 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/27 19:40:51 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rs;

	if (!s)
		return (0);
	if (!(rs = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	i = -1;
	while (s[++i])
		rs[i] = (*f)(i, s[i]);
	rs[i] = '\0';
	return (rs);
}
