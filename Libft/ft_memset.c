/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:46:47 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/03 15:32:28 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = (char*)s;
	while (n--)
		str[n] = (char)c;
	return (str);
}
