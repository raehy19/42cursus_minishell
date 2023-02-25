/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:03:19 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 11:34:24 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

static int	ft_isnumber(char *str)
{
	int	idx;

	idx = 0;
	if (*str == '+' || *str == '-')
		idx++;
	if (!str[idx])
		return (0);
	while (ft_isdigit(str[idx]))
		idx++;
	return (!str[idx]);
}

void	ft_exit(t_node *node)
{
	if (node->arg_cnt == 1)
		exit(g_global.exit_status);
	if (node->arg_cnt > 2)
	{
		printf("bash: exit: too many arguments\n");
		g_global.exit_status = 1;
		exit(g_global.exit_status);
	}
	if (!ft_isnumber(node->command_arg[1]))
	{
		printf("bash :exit: %s: numberic argument required\n", node->command_arg[1]);
		g_global.exit_status = 1;
		exit(g_global.exit_status);
	}
	g_global.exit_status = ft_atoi(node->command_arg[1]);
	exit(g_global.exit_status);
}
