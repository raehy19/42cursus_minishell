/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:52:52 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 20:52:07 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		g_global.errno = NaE;
		is_valid_name(node->command_arg[idx]);
		if (g_global.errno == INVALID_IDENTIFIER)
		{
			g_global.exit_status = 1;
			printf("bash: unset: `%s': not a valid identifier\n", node->command_arg[idx]);
			continue ;
		}
		remove_env(node->command_arg[idx]);
	}
	exit(g_global.exit_status);
}
