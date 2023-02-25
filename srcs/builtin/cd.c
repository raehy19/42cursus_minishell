/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:36 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 13:07:56 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	set_pwd(void)
{
	t_env	*pwd;

	pwd = find_env("PWD");
	free(pwd->value);
	pwd->value = getcwd(0, 4096);
}

void	ft_cd(t_node *node)
{
	int		is_error;
	char	*path;
	t_env	*home;

	path = node->command_arg[1];
	home = find_env("HOME");
	if (node->arg_cnt == 1 && home)
		path = home->value;
	is_error = chdir(path);
	if (is_error)
	{
		if (node->arg_cnt == 1)
			printf("bash: cd: HOME not set\n");
		if (node->arg_cnt > 1)
			printf("bash: cd: %s: No such file or directory\n", node->command_arg[1]);
		g_global.exit_status = 1;
		exit(g_global.exit_status); //exit code 1
	}
	set_pwd();
	g_global.exit_status = 0;
	exit(g_global.exit_status);
}
