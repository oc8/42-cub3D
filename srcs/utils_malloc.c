/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:43:29 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/02 12:44:18 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	*ft_check_calloc(t_ptr *ptr, size_t nbr, size_t size)
{
	void	*rs;
	t_list			*content;

	rs = ft_calloc(nbr, size);
	if (!rs)
		ft_close(ptr, 1);
	if (!ptr->malloc_lst)
		ptr->malloc_lst = ft_lstnew(rs);
	else
	{
		content = ft_lstnew(rs);
		ft_lstadd_front(&ptr->malloc_lst, content);
	}
	return (rs);
}
