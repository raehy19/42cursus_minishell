/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:43:09 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/26 19:03:30 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

extern t_global	g_global;

void	handle_child_process(t_node *node, t_execute *execute)
{
	if (node->pid == 0)
	{
		set_control_character();
		close_fildes(execute->pipe[NEW][READ]);
		close_fildes(execute->pipe[OLD][WRITE]);
		if (execute->cnt)
			duplicate_fildes(execute->pipe[OLD][READ], STDIN_FILENO);
		if (node->right && node->right->logical_type == PIPE)
			duplicate_fildes(execute->pipe[NEW][WRITE], STDOUT_FILENO);
		close_fildes(execute->pipe[OLD][READ]);
		close_fildes(execute->pipe[NEW][WRITE]);
		search_node(node->left);
	}
}

void	handle_parent_process(t_node *node, t_execute *execute)
{
	if (node->pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		close_pipe(execute->pipe[OLD]);
		execute->pipe[OLD][READ] = execute->pipe[NEW][READ];
		execute->pipe[OLD][WRITE] = execute->pipe[NEW][WRITE];
		execute->cnt += 1;
	}
}

void	handle_process(t_node *node, t_execute *execute)
{
	if (!g_global.is_child)
	{
		search_node(node->left);
		node->pid = 0;
		return ;
	}
	open_pipe(execute->pipe[NEW]);
	node->pid = fork();
	if (node->pid == -1)
	{
		g_global.err_num = FAIL_FORK;
		handle_error();
	}
	handle_child_process(node, execute);
	handle_parent_process(node, execute);
	execute->pid = node->pid;
}

unsigned char	get_status(int status)
{
	status = *(int *) & status;
	return (status >> 8 & 0x000000ff);
}

void	wait_process(t_execute *execute)
{
	int	res;
	int	status;

	while (execute->cnt)
	{
		execute->cnt -= 1;
		res = wait(&status);
		if (status == 2)
		{
			g_global.exit_status = 130;
			ft_putstr_fd("\n", 2);
			return ;
		}
		if (status == 3)
		{
			g_global.exit_status = 131;
			ft_putstr_fd("Quit: 3\n", 2);
			return ;
		}
		if (res == execute->pid)
			g_global.exit_status = get_status(status);
	}
}
