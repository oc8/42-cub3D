/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:42:44 by odroz-ba          #+#    #+#             */
/*   Updated: 2020/11/30 12:02:16 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*start;

	if (!(*alst))
	{
		*alst = new;
		new->next = 0;
		return ;
	}
	start = *alst;
	while (start->next)
		start = start->next;
	start->next = new;
	new->next = 0;
}
