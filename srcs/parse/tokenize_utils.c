/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:56:51 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/12 04:35:38 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_node	*lst_new_token(t_token_type type, char *str)
{
	t_token_node	*new;

	new = (t_token_node *) malloc(sizeof(t_token_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->str = str;
	new->next = NULL;
	new->linked_str = NULL;
	return (new);
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

int	is_string_char(char c)
{
	if (!c || ft_isspace(c) || c == '(' || c == ')' || c == '&' || c == '|'
		|| c == '<' || c == '>' || c == '\'' || c == '\"')
		return (0);
	return (1);
}
