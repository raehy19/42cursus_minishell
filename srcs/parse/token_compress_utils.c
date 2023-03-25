/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_compress_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 04:16:35 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/12 04:35:06 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_string(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_SINGLE_QUOTE || token->type == T_DOUBLE_QUOTE
		|| token->type == T_STRING)
		return (1);
	return (0);
}

t_linked_str	*new_linked_str(t_token_type type, char *str)
{
	t_linked_str	*new;

	new = (t_linked_str *) malloc(sizeof(t_linked_str));
	if (!new)
		return (NULL);
	new->str = str;
	new->str_type = type;
	new->next = NULL;
	return (new);
}

t_linked_str	*lst_last_linked_str(t_linked_str *lst)
{
	t_linked_str	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	linked_str_add_back(t_linked_str **lst, t_linked_str *new)
{
	t_linked_str	*temp;

	if (!(*(lst)))
	{
		*lst = new;
		return ;
	}
	temp = lst_last_linked_str(*(lst));
	if (!temp)
		return ;
	temp->next = new;
}
