/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:26:27 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 14:39:13 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	handle_builtin(t_node *node)
{
	if (!ft_strcmp(node->command_arg[0], "echo"))
		ft_echo(node);
	if (!ft_strcmp(node->command_arg[0], "cd"))
		ft_cd(node);
	if (!ft_strcmp(node->command_arg[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(node->command_arg[0], "export"))
		ft_export(node);
	if (!ft_strcmp(node->command_arg[0], "unset"))
		ft_unset(node);
	if (!ft_strcmp(node->command_arg[0], "env"))
		ft_env();
	if (!ft_strcmp(node->command_arg[0], "exit"))
		ft_exit(node);
}

void	execve_command(t_node *node)
{
	char	**envp;

	envp = make_envp();
	handle_error();
	node->command_path = find_command_path(node);
	if (!node->command_path)
	{
		g_global.exit_status = 127;
		print_command_error(node, 0, "command not found");
	}
	if (execve(node->command_path, node->command_arg, envp) == -1)
	{
		g_global.err_num = FAIL_EXECUTE;
		handle_error();
	}
}

void	handle_command(t_node *node)
{
	handle_builtin(node);
	execve_command(node);
}
