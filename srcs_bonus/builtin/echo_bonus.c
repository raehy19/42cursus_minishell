/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:32:44 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/17 10:57:04 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

int	is_option(char *str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	if (str[idx] != '-' || !str[++idx])
		return (0);
	while (str[idx] == 'n')
		idx++;
	return (!str[idx]);
}

int	check_option(t_node *node)
{
	int	idx;

	idx = 1;
	if (node->arg_cnt == 1)
		return (idx);
	while (is_option(node->command_arg[idx]))
		idx++;
	return (idx);
}

void	ft_echo(t_node *node)
{
	int	idx;
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
}
