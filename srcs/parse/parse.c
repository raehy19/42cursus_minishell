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

int	is_and_or_pipe(t_token_node *temp)
{
	if (!temp)
		return (0);
	if (temp->type == T_AND ||temp->type == T_OR
		||temp->type == T_PIPE )
		return (1);
	return (0);
}

int	is_parenthesis(t_token_node *temp)
{
	if (!temp)
		return (0);
	if (temp->type == T_LEFT_PARENTHESIS
		|| temp->type == T_RIGHT_PARENTHESIS)
		return (1);
	return (0);
}

int	is_logical(t_token_node *temp)
{
	return (is_and_or_pipe(temp) || is_parenthesis(temp));
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
	new->redirect_type = (t_redirect_type) (temp->type - 4);
	free(temp);
	temp = token_shift(token_list);
	new->redirect_linked_str = temp->linked_str;
	free(temp);
	lst_unshift_token(arrow, new);
}

void	parse_cmd(t_linked_arg **cmd_args, t_token_node *temp)
{
	lst_push_cmd(cmd_args, temp->linked_str);
	free(temp);
}

void	add_new_logical(t_node **head, t_token_node *temp, t_token_node **token_list)
{
	(*head)->right = new_node(LOGICAL, (t_logical_type) temp->type);
	free(temp);
	ft_parse_token_list(&(*head)->right, token_list);
}

void	ft_check_cmd(t_node **head, t_linked_arg *cmd_args, t_node *arrow)
{
	if ((*head)->left)
		return;
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

t_token_node	*parse_l_parenthesis(t_node **head, t_token_node *temp, t_token_node **token_list)
{
	(*head)->left = new_node(LOGICAL, ROOT);
	free(temp);
	ft_parse_token_list(&(*head)->left, token_list);
	return (token_shift(token_list));
}

t_token_node	*parse_r_parenthesis(t_node **head, t_token_node *temp, t_token_node **token_list)
{
	t_node			*arrow;

	free(temp);
	arrow = NULL;
	temp = token_shift(token_list);
	if (is_arrow(temp))
		parse_arrow(&arrow, temp, token_list);
	(*head)->pre_redirect = arrow;
	return (token_shift(token_list));
}

void	parse_parenthesis(t_node **head, t_token_node **temp, t_token_node **token_list)
{
	if (*temp && (*temp)->type == T_LEFT_PARENTHESIS)
		*temp = parse_l_parenthesis(head, *temp, token_list);
	if (*temp && (*temp)->type == T_RIGHT_PARENTHESIS)
		*temp = parse_r_parenthesis(head, *temp, token_list);
	else
		g_global.err_num = SYNTAX_ERR;

}

void	ft_parse_token_list(t_node **head, t_token_node **token_list)
{
	t_token_node	*temp;
	t_node			*arrow;
	t_linked_arg	*cmd_args;

	temp = token_shift(token_list);
	if (!temp)
		return;
	if (is_parenthesis(temp))
		parse_parenthesis(head, &temp, token_list);
	if (!temp)
		return;
	arrow = NULL;
	cmd_args = NULL;
	while (temp && !is_logical(temp))
	{
		if (is_arrow(temp))
			parse_arrow(&arrow, temp, token_list);
		else if (temp->type == T_LUMP_STR)
			parse_cmd(&cmd_args, temp);
		temp = token_shift(token_list);
	}
	ft_check_cmd(head, cmd_args, arrow);
	if (is_and_or_pipe(temp))
		add_new_logical(head, temp, token_list);
}

t_node	*ft_parse(t_token_node **token_list)
{
	t_node	*tree;

	tree = new_node(LOGICAL, ROOT);
	ft_parse_token_list(&tree, token_list);
	if( !tree->left && !tree->right)
	{
		free(tree);
		tree = NULL;
	}
	return (tree);
}
