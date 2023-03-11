/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:52:52 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 15:01:28 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_unset(t_node *node)
{
	int	idx;

	g_global.exit_status = 0;
	if (node->arg_cnt == 1)
		exit(g_global.exit_status);
	idx = 0;
	while (node->command_arg[++idx])
	{
		g_global.err_num = NaE;
		is_valid_name(node->command_arg[idx]);
		if (g_global.err_num == INVALID_IDENTIFIER)
		{
			print_invalid_identifier_error(node, idx);
			continue ;
		}
		remove_env(node->command_arg[idx]);
	}
	exit(g_global.exit_status);
}
