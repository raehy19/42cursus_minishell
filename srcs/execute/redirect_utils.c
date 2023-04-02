/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:58:07 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 14:06:34 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:43:24 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:57:54 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static char	*set_error_messeage(char *filename)
{
	char			*error_message;

	error_message = 0;
	if (ft_strchr(filename, '/')
		&& access(filename, F_OK) == -1)
	{
		error_message = "No such file or directory\n";
		g_global.err_num = NO_SUCH_FILE;
	}
	if (!error_message
		&& is_directory(st_info.st_mode))
	{
		error_message = "Is a directory\n";
		g_global.err_num = IS_DIRECTORY;
	}
	if (!error_message
		&& access(filename, F_OK) == 0
		&& access(filename, W_OK) == -1)
	{
		error_message = "Permission denied\n";
		g_global.err_num = PERMISSION_DENIED;
	}
	return (error_message);
}

int	check_out_redirect_authority(char *filename)
{
	char			*error_message;
	struct stat		st_info;

	stat(filename, &st_info);
	if (!ft_strchr(filename, '/') && access(filename, F_OK) == -1)
		return (1);
	error_message = set_error_messeage(filename);
	if (error_message)
		print_redirect_error(filename, error_message);
	return (g_global.err_num == NaE);
}
