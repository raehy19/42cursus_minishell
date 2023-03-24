/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:20:09 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/24 20:07:59 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	set_builtin_type(t_node *node)
{
	if (!node->command_arg)
		node->command_arg
			= ft_combine_arg(node->cmd_arg_linked_str, &node->arg_cnt);
	if (!node->command_arg)
		return ;
	handle_command_wildcard(node);
	node->builtin_type = NaB;
	if (!ft_strcmp(node->command_arg[0], "echo"))
		node->builtin_type = ECHO;
	if (!ft_strcmp(node->command_arg[0], "cd"))
		node->builtin_type = CD;
	if (!ft_strcmp(node->command_arg[0], "pwd"))
		node->builtin_type = PWD;
	if (!ft_strcmp(node->command_arg[0], "export"))
		node->builtin_type = EXPORT;
	if (!ft_strcmp(node->command_arg[0], "unset"))
		node->builtin_type = UNSET;
	if (!ft_strcmp(node->command_arg[0], "env"))
		node->builtin_type = ENV;
	if (!ft_strcmp(node->command_arg[0], "exit"))
		node->builtin_type = EXIT;
}

int	handle_singlebuiltin(t_node *node)
{
	if (node->right || node->left->type != COMMAND)
		return (0);
	set_builtin_type(node->left);
	if (!node->left->builtin_type)
		return (0);
	g_global.is_child = 0;
	search_node(node->left);
	return (1);
}
