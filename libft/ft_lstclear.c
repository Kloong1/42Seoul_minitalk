/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kloong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 23:48:54 by kloong            #+#    #+#             */
/*   Updated: 2021/07/08 14:59:49 by yohkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
}
