/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:03:19 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 17:05:57 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_exit(t_node *node)
{
	if (node->arg_cnt == 1)
		exit_by_global();
	if (node->arg_cnt > 2)
	{
		print_command_error(node, 0, "too many arguments");
		return ;
	}
	if (!ft_isnumber(node->command_arg[1]))
	{
		g_global.exit_status = 1;
		print_command_error(node, 1, "numberic argument required");
	}
	g_global.exit_status = ft_atoi(node->command_arg[1]);
	exit_by_global();
}
