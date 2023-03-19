/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:43:09 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/17 20:01:53 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	handle_child_process(t_node *node, int pipe[2][2], int cnt)
{
	if (node->pid == 0)
	{
		close_fildes(pipe[NEW][READ]);
		close_fildes(pipe[OLD][WRITE]);
		if (cnt)
			duplicate_fildes(pipe[OLD][READ], STDIN_FILENO);
		if (node->right && node->right->logical_type == PIPE)
			duplicate_fildes(pipe[NEW][WRITE], STDOUT_FILENO);
		close_fildes(pipe[OLD][READ]);
		close_fildes(pipe[NEW][WRITE]);
		search_node(node->left);
	}
}

void	handle_parent_process(t_node *node, int pipe[2][2], int *cnt)
{
	if (node->pid > 0)
	{
		close_pipe(pipe[OLD]);
		pipe[OLD][READ] = pipe[NEW][READ];
		pipe[OLD][WRITE] = pipe[NEW][WRITE];
		(*cnt)++;
	}
}

int	handle_process(t_node *node, int pipe[2][2], int *cnt)
{
	if (!node->left->is_child)
	{
		search_node(node->left);
		return (0);
	}
	open_pipe(pipe[NEW]);
	node->pid = fork();
	if (node->pid == -1)
	{
		g_global.err_num = FAIL_FORK;
		handle_error();
	}
	handle_child_process(node, pipe, *cnt);
	handle_parent_process(node, pipe, cnt);
	return (node->pid);
}

void	wait_process(pid_t pid, int cnt)
{
	int	res;
	int	status;

	while (cnt--)
	{
		res = wait(&status);
		if (res == pid)
			g_global.exit_status = status >> 8;
	}
}