/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:37:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/07 18:07:53 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		ft_in_map(t_ptr *ptr, t_i coordinate)
{
	t_i	nbr_map;

	nbr_map = ptr->pars->nbr_map;
	if (coordinate.x < 0 || coordinate.y < 0)
		return (0);
	if (coordinate.x >= nbr_map.x || coordinate.y >= nbr_map.y)
		return (0);
	return (1);
}

void	ft_lstclear_mlx(t_list **lst, int (*del)(void*, void*), t_ptr *ptr)
{
	t_list	*start;
	t_list	*tmp;
(void)del;
(void)ptr;
	start = *lst;
	while (start)
	{
		// del(ptr->mlx.ptr, start->content);
		start = start->next;
	}
	start = *lst;
	while (start)
	{
		tmp = start->next;
		free(start);
		start = tmp;
	}
	*lst = 0;
}

void	ft_add_to_lst(t_ptr *ptr, void *add_ptr)
{
	t_list	*content;

	if (!add_ptr)
		ft_close(ptr, 5);
	if (!ptr->mlx_lst)
		ptr->mlx_lst = ft_lstnew(add_ptr);
	else
	{
		content = ft_lstnew(add_ptr);
		ft_lstadd_front(&ptr->mlx_lst, content);
	}
}

void	*ft_calloc_lst(t_ptr *ptr, size_t nbr, size_t size)
{
	void	*rs;
	t_list	*content;

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