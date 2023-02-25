/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:26:27 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 18:53:50 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_builtin(t_node *node)
{
//	printf("%s\n", node->command_arg[0]);
	if (!ft_strcmp(node->command_arg[0], "echo"))
	{
		ft_echo(node);
	}
}

void	execve_command(t_node *node)
{
	char	**envp;

//	envp = make_envp_str();
	envp = 0;
	execve(node->command_path, node->command_arg, envp);
}

void	handle_command(t_node *node)
{
	handle_builtin(node);
	execve_command(node);
}
