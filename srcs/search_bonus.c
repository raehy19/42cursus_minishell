/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/19 19:07:14 by yeepark          ###   ########.fr       */
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

void	search_tree(t_node *node)
{
	int		pipe[2][2];
	int		cnt;
	pid_t	pid;

	cnt = 0;
	if (handle_singlebuiltin(node))
		return ;
	open_pipe(pipe[OLD]);
	while (node)
	{
		g_global.err_num = NaE;
		if (node->left->logical_type == ROOT)
		{
			pid = fork();
			if (pid == 0)
				node = node->left;
			if (pid > 0)
			{
				node = node->right;
				cnt++;
			}
			continue ;
		}
		if (node->logical_type == AND || node->logical_type == OR)
		{		
			wait_process(pid, cnt);
			if (check_exit_status(node))
				return ;
			init_standard_fildes();
		}
		node->left->is_child = set_(node);
		pid = handle_process(node, pipe, &cnt);
		node = node->right;
	}
	close_pipe(pipe[OLD]);
	wait_process(pid, cnt);
}
