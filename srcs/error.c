/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:36:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 15:55:24 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	print_command_error(t_node *node, int idx, char *error_message)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(node->command_arg[0], 2);
	ft_putstr_fd(": ", 2);
	if (idx)
	{
		ft_putstr_fd(node->command_arg[idx], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	exit(g_global.exit_status);
}
