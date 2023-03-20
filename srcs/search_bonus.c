/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/20 20:26:18 by yeepark          ###   ########.fr       */
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
	int		pipe[2][2];
	int		cnt;
	int		is_main;
	int		pre_redir;
	pid_t	pid;

	cnt = 0;
	is_main = 1;
	pre_redir = 0;
	if (handle_singlebuiltin(node))
		return ;
	open_pipe(pipe[OLD]);
	while (node)
	{
		g_global.err_num = NaE;
		if (handle_and_or(node, pid, &cnt, pre_redir))
			return ;
		if (!handle_parenthesis(&node, pid, &cnt, &is_main, &pre_redir))
			continue ;
		node->left->is_child = check_fork(node);
		pid = handle_process(node, pipe, &cnt);
		node = node->right;
	}
	close_pipe(pipe[OLD]);
	wait_process(pid, cnt);
	if (!is_main)
		exit(g_global.exit_status);
}
