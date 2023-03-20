/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:58:37 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/20 17:49:28 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

//builtlin x or pipe와 연결 => fork
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

int	handle_and_or(t_node *node, pid_t pid, int *cnt)
{
	if (node->logical_type == AND || node->logical_type == OR)
	{		
		wait_process(pid, *cnt);
		if (check_exit_status(node))
			return (1);
		init_standard_fildes();
	}
	return (0);
}

int	handle_parenthesis(t_node **node, pid_t pid, int *cnt, int *is_main)
{
	if ((*node)->left->logical_type == ROOT)
	{
		printf("asdf\n");
		pid = fork();
		if (pid == 0)
		{
			*node = (*node)->left;
			*is_main = 0;
		}
		if (pid > 0)
		{
			*node = (*node)->right;
			(*cnt)++;
		}
		return (0);
	}
	return (1);

}
