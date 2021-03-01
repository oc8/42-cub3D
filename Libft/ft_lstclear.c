/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:14:19 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/03/01 14:00:25 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*start;
	t_list	*tmp;

	start = *lst;
	while (start)
	{
		del(start->content);
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
