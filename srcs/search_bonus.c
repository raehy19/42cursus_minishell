/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/17 17:38:32 by yeepark          ###   ########.fr       */
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

//builtlin x or pipe와 연결 => fork
int	set_(t_node *node)
{
	t_node	*cmd_node;
	int		is_pipe;

	cmd_node = node->left;
	cmd_node->command_arg
		= ft_combine_arg(cmd_node->cmd_arg_linked_str, &cmd_node->arg_cnt);
	if (!is_builtin(cmd_node))
		return (1);
	is_pipe = 0;
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

void	search_tree(t_node *node)
{
	int		pipe[2][2];
	int		cnt;
	pid_t	pid;

	if (handle_singlebuiltin(node))
		return ;
	cnt = 0;
	open_pipe(pipe[OLD]);
	while (node)
	{
		g_global.err_num = NaE;
		if (node->logical_type == AND || node->logical_type == OR)
		{		
			wait_process(pid, cnt);
			if (check_exit_status(node))
				return ;
		}
		node->left->is_child = set_(node);
		pid = handle_process(node, pipe, &cnt);
		node = node->right;
	}
	close_pipe(pipe[OLD]);
	wait_process(pid, cnt);
}
