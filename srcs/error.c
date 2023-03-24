/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:36:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/24 18:46:50 by yeepark          ###   ########.fr       */
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

void	print_invalid_identifier_error(t_node *node, int idx)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(node->command_arg[0], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(node->command_arg[idx], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_global.exit_status = 1;
}

void	print_redirect_error(char *filename, char *error_message)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	g_global.exit_status = 1;
	exit(g_global.exit_status);
}

void	handle_error(void)
{
	if (g_global.err_num == NaE)
		return ;
	g_global.exit_status = 1;
	if (g_global.err_num == FAIL_MALLOC)
	{
		ft_putstr_fd(strerror(ENOMEM), 2);
		g_global.exit_status = ENOMEM;
	}
	if (g_global.err_num == FAIL_OPEN_PIPE)
		ft_putstr_fd("fail open pipe\n", 2);
	if (g_global.err_num == FAIL_OPEN_FILDES)
		ft_putstr_fd("fail open fildes\n", 2);
	if (g_global.err_num == FAIL_CLOSE_FILDES)
		ft_putstr_fd("fail close fildes\n", 2);
	if (g_global.err_num == FAIL_EXECUTE)
		ft_putstr_fd("fail execve\n", 2);
	if (g_global.err_num == FAIL_FORK)
		ft_putstr_fd("fail fork\n", 2);
	if (g_global.err_num == FAIL_DUPLICATE_FILDES)
		ft_putstr_fd("fail duplicate fildes\n", 2);
	if (g_global.err_num == FAIL_OPEN_DIR)
		ft_putstr_fd("fail open directory\n", 2);
	if (g_global.err_num == FAIL_STAT)
		ft_putstr_fd("fail get file status\n", 2);
	exit(g_global.exit_status);
}
