/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:24:41 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 15:46:34 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	parse_arrow(t_node **arrow, t_token *temp, t_token **token_list)
{
	t_node	*new;

	if (!temp->next || temp->next->type != T_LUMP_STR)
	{
		g_global.err_num = SYNTAX_ERR;
		return ;
	}
	new = new_node(REDIRECT, NaL);
	if (!new)
		return ;
	new->redirect_type = (t_redirect_type)(temp->type - 4);
	free(temp);
	temp = token_shift(token_list);
	if (temp->type != T_LUMP_STR)
		g_global.err_num = SYNTAX_ERR;
	new->redirect_linked_str = temp->link_str;
	free(temp);
	node_unshift(arrow, new);
}

void	parse_cmd(t_linked_arg **cmd_args, t_token *temp)
{
	lst_push_cmd(cmd_args, temp->link_str);
	free(temp);
}

void	add_new_logical(t_node **head, t_token *temp, t_token **token_list)
{
	(*head)->right = new_node(LOGICAL, (t_logical_type) temp->type);
	free(temp);
	parse_token_list(&((*head)->right), token_list);
}

void	ft_check_cmd(t_node **head, t_linked_arg *cmd_args, t_node *arrow)
{
	if ((*head)->left)
		return ;
	(*head)->left = new_node(COMMAND, NaL);
	if ((*head)->left)
	{
		if (cmd_args)
			(*head)->left->cmd_arg_linked_str = cmd_args;
		(*head)->left->left = arrow;
	}
	else
		g_global.err_num = FAIL_MALLOC;
}
