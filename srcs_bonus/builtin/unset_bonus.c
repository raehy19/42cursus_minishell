/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:52:52 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:50:57 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

void	ft_unset(t_node *node)
{
	int	idx;

	g_global.exit_status = 0;
	if (node->arg_cnt == 1)
		return ;
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
}
