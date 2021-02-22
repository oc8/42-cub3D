/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:02:25 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/27 19:41:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_in_str(const char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (str[i] == 0)
		return (0);
	return (1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*rs;
	int		i;
	int		j;
	int		mem;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_in_str(set, s1[i]) && s1[i])
		i++;
	mem = i;
	i = ft_strlen(s1);
	if (mem == i)
		return (ft_strdup(""));
	while (ft_in_str(set, s1[--i]))
		;
	if (!(rs = malloc(sizeof(char) * (i - mem + 2))))
		return (NULL);
	j = -1;
	while (mem <= i)
		rs[++j] = s1[mem++];
	rs[++j] = '\0';
	return (rs);
}
