/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:36 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 17:06:12 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	set_pwd(void)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env("PWD");
	oldpwd = find_env("OLDPWD");
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(0, 4096);
}

void	ft_cd(t_node *node)
{
	int		is_error;
	char	*changed_dir;
	char	*error_msg;
	t_env	*home;

	changed_dir = node->command_arg[1];
	home = find_env("HOME");
	if (node->arg_cnt == 1 && home)
		changed_dir = home->value;
	is_error = chdir(changed_dir);
	if (is_error)
	{
		if (node->arg_cnt == 1)
			error_msg = "HOME not set";
		if (node->arg_cnt > 1)
			error_msg = "No such file or directory";
		g_global.exit_status = 1;
		print_command_error(node, (node->arg_cnt > 1), error_msg);
	}
	set_pwd();
	g_global.exit_status = 0;
	exit_by_global();
}
