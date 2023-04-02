/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:41:36 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 12:52:10 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

char	*join_name_and_value(t_env *env)
{
	int		size;
	char	*new;

	size = ft_strlen(env->name) + ft_strlen(env->value) + 1;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
	{
		g_global.err_num = FAIL_MALLOC;
		return (0);
	}
	ft_strlcpy(new, env->name, ft_strlen(env->name) + 1);
	if (env->value)
	{
		ft_strlcat(new, "=", ft_strlen(env->name) + 2);
		ft_strlcat(new, env->value, size + 1);
	}
	return (new);
}

char	**make_envp(void)
{
	int		idx;
	t_env	*env;
	char	**envp;

	envp = malloc(sizeof(char *) * (get_env_size() + 1));
	if (!envp)
	{
		g_global.err_num = FAIL_MALLOC;
		return (0);
	}
	idx = 0;
	env = g_global.envp;
	while (g_global.err_num == NaE && env)
	{
		envp[idx] = join_name_and_value(env);
		idx++;
		env = env->next;
	}
	envp[idx] = 0;
	handle_error();
	return (envp);
}
