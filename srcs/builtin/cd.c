/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:36 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 10:56:45 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	set_pwd(void)
{
	t_env	*env;
	t_env	*pwd;

	env = g_global.envp;
	pwd = find_env(&env, "PWD");
	free(pwd->value);
	pwd->value = getcwd(0, 4096);
}

void	ft_cd(t_node *node)
{
	int		is_error;
	t_env	*env;

	env = g_global.envp;
	is_error = chdir(node->command_arg[1]);
	if (node->arg_cnt == 1)
		is_error = chdir(find_env(&env, "HOME")->value);
	if (is_error)
	{
		perror(node->command_arg[1]);
		g_global.exit_status = 1;
		exit(g_global.exit_status); //exit code 1
	}
	set_pwd();
}
