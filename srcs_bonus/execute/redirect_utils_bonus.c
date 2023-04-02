/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:43:24 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:12 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

int	is_in(t_redirect_type type)
{
	return (type == REDIRECTING_INPUT || type == HERE_DOCUMENT);
}

int	is_out(t_redirect_type type)
{
	return (type == REDIRECTING_OUTPUT
		|| type == APPENDING_REDIRECTED_OUTPUT);
}

int	check_in_redirect_authority(char *filename)
{
	char	*error_message;

	error_message = 0;
	if (access(filename, F_OK) == -1)
	{
		error_message = "No such file or directory\n";
		g_global.err_num = NO_SUCH_FILE;
	}
	if (!error_message && access(filename, R_OK) == -1)
	{
		error_message = "Permission denied\n";
		g_global.err_num = PERMISSION_DENIED;
	}
	if (error_message)
		print_redirect_error(filename, error_message);
	return (g_global.err_num == NaE);
}

int	check_out_redirect_authority(char *filename)
{
	char	*error_message;

	error_message = 0;
	if (access(filename, F_OK) == -1)
		return (1);
	if (access(filename, W_OK) == -1)
	{
		error_message = "Permission denied\n";
		g_global.err_num = PERMISSION_DENIED;
	}
	if (error_message)
		print_redirect_error(filename, error_message);
	return (g_global.err_num == NaE);
}
