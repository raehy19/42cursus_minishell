/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:45 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/26 17:54:13 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

extern t_global	g_global;

int	init_envp(char *envp[])
{
	int				idx;
	int				is_oldpwd;
	t_env			*new;

	idx = 0;
	is_oldpwd = 0;
	while (envp[idx])
	{
		new = make_env(envp[idx]);
		if (g_global.err_num != NaE)
			return (1);
		add_env_back(new);
		if (!ft_strcmp(new->name, "OLDPWD"))
			is_oldpwd = 1;
		idx++;
	}
	if (is_oldpwd)
		return (0);
	new = make_env("OLDPWD");
	if (g_global.err_num != NaE)
		return (1);
	add_env_back(new);
	return (0);
}

void	init_builtin_functions(void)
{
	g_global.builtin_function[BUILTIN_ECHO] = ft_echo;
	g_global.builtin_function[BUILTIN_CD] = ft_cd;
	g_global.builtin_function[BUILTIN_PWD] = ft_pwd;
	g_global.builtin_function[BUILTIN_EXPORT] = ft_export;
	g_global.builtin_function[BUILTIN_UNSET] = ft_unset;
	g_global.builtin_function[BUILTIN_ENV] = ft_env;
	g_global.builtin_function[BUILTIN_EXIT] = ft_exit;
}

void	init_global(char **envp)
{
	init_builtin_functions();
	if (init_envp(envp))
		exit(clear_env());
	g_global.exit_status = 0;
	g_global.is_child = 0;
	g_global.standard_fildes[0] = STDIN_FILENO;
	g_global.standard_fildes[1] = STDOUT_FILENO;
}
