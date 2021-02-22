/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:53:44 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/27 19:03:14 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	n_long;

	n_long = (long)n;
	if (n_long < 0)
	{
		n_long *= -1;
		write(fd, "-", 1);
	}
	if (n_long < 10)
	{
		ft_putchar_fd(n_long + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n_long / 10, fd);
		ft_putchar_fd(n_long % 10 + '0', fd);
	}
}
