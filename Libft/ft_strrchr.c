/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:01:10 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/27 19:21:28 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*str;
	int		i;

	cc = (char)c;
	str = (char*)s;
	i = ft_strlen(s);
	while (str[i] != cc && &str[i] >= str && i > 0)
		i--;
	if (cc == '\0')
		return (&str[i]);
	if (str + i == str && str[i] != cc)
		return (0);
	return (str + i);
}
