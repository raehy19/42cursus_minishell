/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:56:51 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 15:48:06 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(t_token_type type, char *str)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->str = str;
	new->next = NULL;
	new->link_str = NULL;
	return (new);
}

t_token	*lst_last_token(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	lst_push_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!(*(lst)))
	{
		*lst = new;
		return ;
	}
	temp = lst_last_token(*(lst));
	if (!temp)
		return ;
	temp->next = new;
}

t_token	*token_shift(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	if (temp)
		*token_list = (*token_list)->next;
	return (temp);
}

void	token_unshift(t_token **lst, t_token *new)
{
	if ((*lst))
		new->next = *lst;
	*lst = new;
}
