/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:32:29 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/27 19:40:38 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*s1copy;
	int		i;

	s1copy = malloc(sizeof(*s1copy) * ft_strlen(s1) + 1);
	if (!s1copy)
		return (0);
	i = -1;
	while (s1[++i])
		s1copy[i] = s1[i];
	s1copy[i] = '\0';
	return (s1copy);
}
