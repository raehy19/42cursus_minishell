/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:36:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 17:15:15 by yeepark          ###   ########.fr       */
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

void	print_redirect_error(char *filename)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_global.exit_status = 1;
	exit(g_global.exit_status);
}

void	print_error_fildes(t_error_number error_number)
{
	g_global.errno = error_number;
	perror("");
	g_global.exit_status = 1;
	exit(g_global.exit_status);
}
