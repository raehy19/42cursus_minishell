/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:26:27 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/05 19:58:02 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	handle_builtin(t_node *node)
{
//	printf("%s\n", node->command_arg[0]);
//	if (!ft_strcmp(node->command_arg[0], "echo"))
//		ft_echo(node);
}

void	execve_command(t_node *node)
{
	char	**envp;

	envp = make_envp();
	if (g_global.errno == FAIL_MALLOC)
	{
//		strerror(ENOMEM);
//		exit();
	}
	node->command_path = find_command_path(node);
	if (!node->command_path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(node->command_arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
//		printf("bash: %s: command not found\n", node->command_arg[0]);
		g_global.exit_status = 127;
		exit(g_global.exit_status);
	}
	execve(node->command_path, node->command_arg, envp);
}

void	handle_command(t_node *node)
{
//	handle_builtin(node);
	execve_command(node);
}

