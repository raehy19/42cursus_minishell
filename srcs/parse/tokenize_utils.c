/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:56:51 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/24 20:56:53 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token_node	*lst_new_token(t_token_type type, char *str)
{
	t_token_node	*new;

	new = (t_token_node *) malloc(sizeof(t_token_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->string = str;
	new->next = NULL;
	return (new);
}

void	lst_add_front_token(t_token_node **lst, t_token_node *new)
{
	new->next = (*(lst));
	*(lst) = new;
	return ;
}

t_token_node	*lst_last_token(t_token_node *lst)
{
	t_token_node	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


void	lst_add_back_token(t_token_node **lst, t_token_node *new)
{
	t_token_node	*temp;

	if (!(*(lst)))
	{
		*lst = new;
		return ;
	}
	temp = lst_last_token(*(lst));
	if (!temp)
		return ;
	temp->next = new;
	return ;
}
