/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:48:46 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/16 13:15:29 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*mem;

	mem = (char*)big;
	if (*little == 0)
		return (mem);
	if (len == 0)
		return (0);
	i = 0;
	while (i < len && big[i])
	{
		mem = (char*)(big + i);
		j = 0;
		while (big[i + j] == little[j] && len > i + j)
		{
			if (little[j + 1] == 0)
				return (mem);
			j++;
		}
		i++;
	}
	return (0);
}
