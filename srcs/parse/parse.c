/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:10:53 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/12 04:36:08 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

t_token_node	*token_shift(t_token_node **token_list)
{
	t_token_node	*temp;

	temp = *token_list;
	if (temp)
		*token_list = (*token_list)->next;
	return (temp);
}

int	is_logical(t_token_node *temp)
{
	if (temp->type == T_LEFT_PARENTHESIS
		|| temp->type == T_RIGHT_PARENTHESIS
		||temp->type == T_AND ||temp->type == T_OR
		||temp->type == T_PIPE )
		return (1);
	return (0);
}

int	is_arrow(t_token_node *temp)
{
	if (temp->type == T_REDIRECTING_INPUT
		|| temp->type == T_HERE_DOCUMENT
		||temp->type == T_REDIRECTING_OUTPUT
		||temp->type == T_APPENDING_REDIRECTED_OUTPUT)
		return (1);
	return (0);
}

void	parse_arrow(t_node **arrow, t_token_node *temp, t_token_node **token_list)
{
	t_node	*new;

	if (!temp->next || temp->next->type != T_LUMP_STR)
	{
		g_global.err_num = SYNTAX_ERR;
		return ;
	}
	new = new_node(REDIRECT, NaL);
	new->redirect_type = temp->type - 4;
	free(temp);
	temp = token_shift(token_list);
	new->redirect_linked_str = temp->linked_str;
	free(temp);
	lst_unshift_token(arrow, new);
}

void	ft_parse_token_list(t_node **head, t_token_node **token_list)
{
	t_token_node	*temp;
	t_node			*arrow;

	temp = token_shift(token_list);
	arrow = NULL;
	while (temp && !is_logical(temp))
	{
		if (is_arrow(temp))
			parse_arrow(&arrow, temp, token_list);
		temp = token_shift(token_list);
	}
	(void )head;
}

t_node	*ft_parse(t_token_node **token_list)
{
	t_node	*tree;

	tree = new_node(LOGICAL, ROOT);
	ft_parse_token_list(&tree, token_list);
	return (tree);
}
