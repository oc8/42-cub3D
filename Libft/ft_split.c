/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:30:59 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/03 20:23:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_all(char **rs, int i)
{
	while (--i >= 0)
		free(rs[i]);
	free(rs);
	return (0);
}

int		ft_count_str(const char *src, char sep)
{
	int		count;

	count = 0;
	while (*src)
	{
		while (*src == sep && *src)
			src++;
		if (*src != '\0')
			count++;
		while (*src != sep && *src)
			src++;
	}
	return (count);
}

int		ft_count_c(const char *str, char c)
{
	int		count;

	count = 0;
	while (*str != c && *str)
	{
		str++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**rs;
	int		i;
	int		j;

	if (!s)
		return (0);
	if (!(rs = malloc(sizeof(char*) * (ft_count_str(s, c) + 1))))
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		if (!(rs[i] = malloc(sizeof(char) * (ft_count_c(s, c) + 1))))
			return (ft_free_all(rs, i));
		j = -1;
		while (*s != c && *s)
			rs[i][++j] = *s++;
		rs[i][++j] = '\0';
		i++;
	}
	rs[i] = 0;
	return (rs);
}
