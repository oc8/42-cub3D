/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:43:33 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/02 19:50:47 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_neg(long *n_long, int *count)
{
	if (*n_long < 0)
	{
		*n_long *= -1;
		*count = 1;
		return (0);
	}
	return (1);
}

char		*ft_itoa(int n)
{
	long	cpy;
	int		count;
	char	*rs;
	int		flag;
	long	n_long;

	n_long = (long)n;
	count = 0;
	flag = ft_check_neg(&n_long, &count);
	cpy = n_long;
	while (cpy /= 10)
		count++;
	if (!(rs = malloc(sizeof(char) * count + 2)))
		return (0);
	if (flag == 0)
		rs[0] = '-';
	rs[count + 1] = '\0';
	while (rs + count + flag > rs)
	{
		rs[count--] = n_long % 10 + '0';
		n_long /= 10;
	}
	return (rs);
}
