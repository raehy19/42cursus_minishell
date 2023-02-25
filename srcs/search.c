/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 20:52:49 by yeepark          ###   ########.fr       */
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
	int	start;
	int	cnt;

	start = 1;
	cnt = 0;
	open_pipe(pipe[OLD]);
	while (node)
	{
		open_pipe(pipe[NEW]);
		node->pid = fork();
	//	if (node->pid == -1)
		if (node->pid == 0)
		{
			close(pipe[NEW][READ]);
			close(pipe[OLD][WRITE]);
			if (!start)
				dup2(pipe[OLD][READ], STDIN_FILENO);
			if (node->right)
				dup2(pipe[NEW][WRITE], STDOUT_FILENO);
			close(pipe[OLD][READ]);
			close(pipe[NEW][WRITE]);
			search_node(node->left);
		}
		if (node->pid > 0)
		{
			start = 0;
			close(pipe[OLD][READ]);
			close(pipe[OLD][WRITE]);
			pipe[OLD][READ] = pipe[NEW][READ];
			pipe[OLD][WRITE] = pipe[NEW][WRITE];
			node = node->right;
			cnt++;
		}
	}
	close(pipe[OLD][READ]);
	close(pipe[OLD][WRITE]);
	while (cnt--)
		wait(0);
}
