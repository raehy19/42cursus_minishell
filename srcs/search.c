/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 17:24:48 by yeepark          ###   ########.fr       */
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

// pipe == 0 && builtin 일 때 예외처리
void	search_tree(t_node *node)
{
	int	pipe[2][2];
	int	cnt;

	if (handle_singlebuiltin(node))
		return ;
	cnt = 0;
	open_pipe(pipe[OLD]);
	while (node)
	{
		g_global.err_num = NaE;
		open_pipe(pipe[NEW]);
		node->pid = fork();
		if (node->pid == -1)
		{
			g_global.err_num = FAIL_FORK;
			handle_error();
		}
		handle_child_process(node, pipe, cnt);
		handle_parent_process(node, pipe);
		node = node->right;
		cnt++;
	}
	close_pipe(pipe[OLD]);
	while (cnt--)
		wait(0);
}
