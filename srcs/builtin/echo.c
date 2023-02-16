/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:32:44 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 21:06:57 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_echo(t_node *node)
{
	int	idx;
	int	newline;

	idx = 1;
	newline = 1;
	if (!ft_strcmp(node->command_arg[1], "-n"))
	{
		newline = 0;
		idx++;
	}
	while (node->command_arg[idx])
	{
		printf("%s", node->command_arg[idx]);
		idx++;
		if (node->command_arg[idx])
			printf(" ");
	}
	if (newline)
		printf("\n");
	g_global.exit_status = 0;
	exit(g_global.exit_status);
}
