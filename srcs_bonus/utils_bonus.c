/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:31 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

extern t_global	g_global;

int	check_fork(t_node *node)
{
	int		is_pipe;

	is_pipe = 0;
	set_builtin_type(node->left);
	if (!node->left->builtin_type)
		return (1);
	if (node->right)
		is_pipe = (node->right->logical_type == PIPE);
	is_pipe = (is_pipe || (node->logical_type == PIPE));
	return (is_pipe);
}

int	check_exit_status(t_node *node)
{
	return ((node->logical_type == AND && g_global.exit_status)
		|| (node->logical_type == OR && !g_global.exit_status));
}

int	handle_and_or(t_node *node, t_execute *execute)
{
	if (node->logical_type == AND || node->logical_type == OR)
	{		
		wait_process(execute);
		if (check_exit_status(node))
			return (1);
		if (!execute->pre_redirect)
			init_standard_fildes();
	}
	return (0);
}

int	handle_parenthesis(t_node **node, t_execute *execute)
{
	if ((*node)->left->logical_type != ROOT)
		return (1);
	execute->pid = fork();
	if (execute->pid == -1)
	{
		g_global.err_num = FAIL_FORK;
		handle_error();
	}
	if (execute->pid > 0)
	{
		*node = (*node)->right;
		execute->cnt += 1;
		return (0);
	}
	*node = (*node)->left;
	if ((*node)->pre_redirect)
	{
		search_node((*node)->pre_redirect);
		execute->pre_redirect = 1;
	}
	execute->in_subshell = 1;
	return (0);
}
