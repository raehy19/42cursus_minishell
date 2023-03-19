/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:45 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/19 15:46:40 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!strcmp(new->name, "OLDPWD"))
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
	g_global.builtin_function[ECHO] = ft_echo;
	g_global.builtin_function[CD] = ft_cd;
	g_global.builtin_function[PWD] = ft_pwd;
	g_global.builtin_function[EXPORT] = ft_export;
	g_global.builtin_function[UNSET] = ft_unset;
	g_global.builtin_function[ENV] = ft_env;
	g_global.builtin_function[EXIT] = ft_exit;
}

void	init_global(char **envp)
{
	init_builtin_functions();
	if (init_envp(envp))
		exit(clear_env());
	g_global.standard_fildes[0] = STDIN_FILENO;
	g_global.standard_fildes[1] = STDOUT_FILENO;
}

