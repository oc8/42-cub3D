/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:49:03 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/12/04 11:36:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_free_lst(t_list *rs, void (*del)(void *))
{
	ft_lstclear(&rs, *del);
	return (0);
}

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rs;
	t_list	*element;

	rs = 0;
	while (l)
	{
		element = ft_lstnew(f(l->content));
		if (!element)
			return (ft_free_lst(rs, *del));
		ft_lstadd_back(&rs, element);
		l = l->next;
	}
	return (rs);
}
