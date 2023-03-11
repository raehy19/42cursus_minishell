/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:35 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 17:26:16 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	set_singlebuiltin(t_node *node)
{
	char	*command;
	int		is_butilin;

	if (node->right != NULL || node->left->type != COMMAND)
		g_global.is_singlebuiltin = 0;
	command = node->left->command_arg[0];
	g_global.is_singlebuiltin = 1 
		&& (!ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"));
}

int	handle_singlebuiltin(t_node *node)
{
	set_singlebuiltin(node);
	if (g_global.is_singlebuiltin)
		search_node(node->left);
	return (g_global.is_singlebuiltin);
}
