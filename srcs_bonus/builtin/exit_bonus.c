/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:03:19 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:50:59 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

void	ft_exit(t_node *node)
{
	if (!g_global.is_child)
		ft_putstr_fd("exit\n", 2);
	if (node->arg_cnt == 1)
		exit(g_global.exit_status);
	if (!ft_isnumber(node->command_arg[1]))
	{
		g_global.exit_status = 255;
		print_command_error(node, 1, "numberic argument required");
		exit(g_global.exit_status);
	}
	if (node->arg_cnt > 2)
	{
		g_global.exit_status = 1;
		print_command_error(node, 0, "too many arguments");
		return ;
	}
	g_global.exit_status = ft_atoi(node->command_arg[1]);
	exit(g_global.exit_status);
}
