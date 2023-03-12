/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:46:40 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/12 05:46:41 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*new_node(t_node_type type, t_logical_type logical_type)
{
	t_node	*new;

	new = (t_node *) malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->pre_redirect = NULL;
	new->left = NULL;
	new->right = NULL;
	new->logical_type = logical_type;
	new->command_path = NULL;
	new->cmd_arg_linked_str = NULL;
	new->command_arg = NULL;
	new->arg_cnt = 0;
	new->redirect_type = NaR;
	new->redirect_linked_str = NULL;
	new->redirect_filename = NULL;
	new->in_fd = STDIN_FILENO;
	new->out_fd = STDOUT_FILENO;
	new->pid = 0;
	return (new);
}

void	lst_unshift_token(t_node **lst, t_node *new)
{
	if ((*lst))
		new->left = *lst;
	*lst = new;
}

