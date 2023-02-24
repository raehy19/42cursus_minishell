/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:32:44 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/24 22:48:11 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

int	is_option(char *str)
{
	int	idx;

	idx = 0;
	if (str[idx] != '-')
		return (0);
	idx++;
	while (str[idx] && str[idx] == 'n')
		idx++;
	return (!str[idx]);
}

int	check_option(t_node *node)
{
	int	idx;

	idx = 1;
	if (!node->command_arg[idx])
		return (idx);
	while (is_option(node->command_arg[idx]))
		idx++;
	return (idx);
}

void	ft_echo(t_node *node)
{
	int	idx;
	int	option;
	int	newline;

	newline = 1;
	idx = check_option(node);
	if (idx > 1)
		newline = 0;
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
