/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:35 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/17 09:27:18 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

int	is_builtin(char **command_arg)
{
	char *command;

	if (!command_arg)
		return (0);
	command = command_arg[0];
	return (!ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"));
}

int	handle_singlebuiltin(t_node *node)
{
	if (node->right || !is_builtin(node->left->command_arg))
		return (0);
	node->left->is_child = 0;
	search_node(node->left);
	return (1);
}
