/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:26:27 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/30 22:01:42 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

void	handle_builtin(t_node *node)
{
	g_global.builtin_function[node->builtin_type](node);
	if (g_global.is_child)
		exit(g_global.exit_status);
}

int	handle_exception(char *command)
{
	if (!ft_strcmp(command, ""))
		g_global.err_num = COMMAND_NOT_FOUND;
	if (!find_env("PATH"))
		g_global.err_num = NO_SUCH_FILE;
	return (g_global.err_num != NaE);
}

void	execve_command(t_node *node)
{
	char	**envp;

	if (!handle_exception(node->command_arg[0]))
		node->command_path = find_command_path(node);
	if (!node->command_path)
	{
		g_global.exit_status = 127;
		print_command_path_error(node, 0);
	}
	envp = make_envp();
	handle_error();
	if (execve(node->command_path, node->command_arg, envp) == -1)
	{
		g_global.err_num = FAIL_EXECUTE;
		handle_error();
	}
}

void	handle_command(t_node *node)
{
	if (!handle_command_wildcard(node))
		return ;
	if (!node->command_arg)
		exit(g_global.exit_status);
	if (node->builtin_type)
		handle_builtin(node);
	else
		execve_command(node);
}
