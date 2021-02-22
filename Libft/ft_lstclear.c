/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:14:19 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/02 18:51:40 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*start;

	start = *lst;
	while (start)
	{
		del(start->content);
		start = start->next;
	}
	start = *lst;
	while (start)
	{
		free(start);
		start = start->next;
	}
	*lst = 0;
}
