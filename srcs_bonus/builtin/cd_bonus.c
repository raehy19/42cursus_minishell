/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:36 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 12:28:11 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

void	set_pwd(void)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env("PWD");
	oldpwd = find_env("OLDPWD");
	if (!pwd)
	{
		pwd = make_env("PWD=");
		if (g_global.err_num == NaE)
			add_env_back(pwd);
	}
	if (g_global.err_num == NaE && !oldpwd)
	{
		oldpwd = make_env("OLDPWD=");
		if (g_global.err_num == NaE)
			add_env_back(oldpwd);
	}
	if (g_global.err_num != NaE)
	{
		handle_error();
		return ;
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(0, 0);
}

static int	check_directory(char *changed_dir)
{
	struct stat	st_info;

	if (access(changed_dir, F_OK) == -1)
		return (1);
	stat(changed_dir, &st_info);
	return (is_directory(st_info.st_mode));
}

int	handle_cd_error(int is_error, t_node *node, char *changed_dir)
{
	char	*error_msg;

	if (!is_error)
		return (0);
	error_msg = 0;
	if (!error_msg && node->arg_cnt == 1)
		error_msg = "HOME not set";
	if (!error_msg && !check_directory(changed_dir))
		error_msg = "Not a directory";
	if (!error_msg && node->arg_cnt > 1)
		error_msg = "No such file or directory";
	g_global.exit_status = 1;
	print_command_error(node, (node->arg_cnt > 1), error_msg);
	return (1);
}

void	ft_cd(t_node *node)
{
	int		is_error;
	char	*changed_dir;
	t_env	*home;

	changed_dir = node->command_arg[1];
	home = find_env("HOME");
	if (node->arg_cnt == 1 && home)
		changed_dir = home->value;
	is_error = chdir(changed_dir);
	if (handle_cd_error(is_error, node, changed_dir))
		return ;
	g_global.exit_status = 0;
	set_pwd();
}
