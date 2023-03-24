/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:24:33 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 15:46:35 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

t_token	*parse_l_parenthesis(t_node **head, t_token *temp, t_token **token_list)
{
	(*head)->left = new_node(LOGICAL, ROOT);
	free(temp);
	parse_token_list(&((*head)->left), token_list);
	return (token_shift(token_list));
}

t_token	*parse_r_parenthesis(t_node **head, t_token *temp, t_token **token_list)
{
	t_node			*arrow;

	free(temp);
	arrow = NULL;
	temp = token_shift(token_list);
	while (is_arrow(temp))
	{
		parse_arrow(&arrow, temp, token_list);
		temp = token_shift(token_list);
	}
	(*head)->left->pre_redirect = arrow;
	return (temp);
}

void	parse_parenthesis(t_node **head, t_token **temp, t_token **token_list)
{
	if (*temp && (*temp)->type == T_LEFT_PARENTHESIS)
		*temp = parse_l_parenthesis(head, *temp, token_list);
	else
	{
		g_global.err_num = SYNTAX_ERR;
		return ;
	}
	if (*temp && (*temp)->type == T_RIGHT_PARENTHESIS)
		*temp = parse_r_parenthesis(head, *temp, token_list);
	else
		g_global.err_num = SYNTAX_ERR;
}

void	parse_token_list(t_node **head, t_token **token_list)
{
	t_token			*temp;
	t_node			*arrow;
	t_linked_arg	*cmd_args;

	temp = token_shift(token_list);
	if (is_parenthesis(temp))
		parse_parenthesis(head, &temp, token_list);
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
	if (temp && temp->type == T_RIGHT_PARENTHESIS)
		token_unshift(token_list, temp);
}
