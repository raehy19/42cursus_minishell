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

t_link_str	*new_link_str(t_token_type type, char *str)
{
	t_link_str	*new;

	new = (t_link_str *) malloc(sizeof(t_link_str));
	if (!new)
		return (NULL);
	new->str = str;
	new->str_type = type;
	new->next = NULL;
	return (new);
}

t_link_str	*link_str_last(t_link_str *lst)
{
	t_link_str	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	link_str_add_back(t_link_str **lst, t_link_str *new)
{
	t_link_str	*temp;

	if (!(*(lst)))
	{
		*lst = new;
		return ;
	}
	temp = link_str_last(*(lst));
	if (!temp)
		return ;
	temp->next = new;
}
