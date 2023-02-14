/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:23:34 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/12 11:49:45 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*(lst)))
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*(lst));
	if (!temp)
		return ;
	temp->next = new;
	return ;
}
