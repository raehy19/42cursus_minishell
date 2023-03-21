/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/21 15:00:56 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	handle_node(t_node *node)
{
	if (node->type == REDIRECT)
		handle_redirect(node);
	if (node->type == COMMAND)
		handle_command(node);
}

void	search_node(t_node *node)
{
	if (node->left)
		search_node(node->left);
	if (node->right)
		search_node(node->right);
	handle_node(node);
}

void	search_tree(t_node *node)
{
	t_execute	execute;
	
	execute.cnt = 0;
	execute.in_subshell = 0;
	execute.pre_redirect = 0;
	if (handle_singlebuiltin(node))
		return ;
	open_pipe(execute.pipe[OLD]);
	while (node)
	{
		g_global.err_num = NaE;
		if (handle_and_or(node, &execute))
			return ;
		if (!handle_parenthesis(&node, &execute))
			continue ;
		node->left->is_child = check_fork(node);
		handle_process(node, &execute);
		node = node->right;
	}
	close_pipe(execute.pipe[OLD]);
	wait_process(&execute);
	if (execute.in_subshell)
		exit(g_global.exit_status);
}
