/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:37:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/23 16:16:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_calc_rs(t_cub *ptr, t_plan *p)
{
	float	rs;
	t_c		*pos;

	pos = &ptr->player.pos;
	rs = -(p->a * pos->x + p->b * pos->y + p->c * pos->z + p->d);
	return (rs);
}

int		ft_in_map(t_cub *ptr, t_i coordinate)
{
	t_i	nbr_map;

	nbr_map = ptr->pars->nbr_map;
	if (coordinate.x < 0 || coordinate.y < 0)
		return (0);
	if (coordinate.x >= nbr_map.x || coordinate.y >= nbr_map.y)
		return (0);
	return (1);
}

void	ft_lstclear_mlx(t_list **lst, int (*del)(void*, void*), t_cub *ptr)
{
	t_list	*start;
	t_list	*tmp;

	(void)del;
	(void)ptr;
	start = *lst;
	while (start)
	{
		del(ptr->mlx.ptr, start->content);
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

void	ft_add_to_lst(t_cub *ptr, void *add_ptr)
{
	t_list	*content;

	if (!add_ptr)
		ft_close(ptr, 1, "mlx_get_data_addr() error");
	if (!ptr->mlx_lst)
		ptr->mlx_lst = ft_lstnew(add_ptr);
	else
	{
		content = ft_lstnew(add_ptr);
		ft_lstadd_front(&ptr->mlx_lst, content);
	}
}

void	*ft_calloc_lst(t_cub *ptr, size_t nbr, size_t size)
{
	void	*rs;
	t_list	*content;

	rs = ft_calloc(nbr, size);
	if (!rs)
		ft_close(ptr, 1, "calloc_lst error");
	if (!ptr->malloc_lst)
		ptr->malloc_lst = ft_lstnew(rs);
	else
	{
		content = ft_lstnew(rs);
		ft_lstadd_front(&ptr->malloc_lst, content);
	}
	return (rs);
}
