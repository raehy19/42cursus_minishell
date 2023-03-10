/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:43:09 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 17:27:17 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	handle_child_process(t_node *node, int pipe[2][2], int *cnt)
{
	if (node->pid == 0)
	{
		close_fildes(pipe[NEW][READ]);
		close_fildes(pipe[OLD][WRITE]);
		if (*cnt)
			duplicate_fildes(pipe[OLD][READ], STDIN_FILENO);
		if (node->right)
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
		node = node->right;
		(*cnt)++;
	}
}
