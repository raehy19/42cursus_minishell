/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:46:07 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 10:29:21 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

static void	handle_single_arg(void)
{
	int		idx;
	int		size;
	t_env	*env;

	idx = 0;
	size = get_env_size();
	env = g_global.envp;
	rank_envp();
	while (idx < size)
	{
		if (env->order == idx)
		{
			if (!env->value)
				printf("declare -x %s\n", env->name);
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
			env = g_global.envp;
			idx++;
			continue ;
		}
		env = env->next;
	}
}

static int	handle_duplicated_name(char *src)
{
	int		index;
	char	*name;
	t_env	*env;
	t_env	*duplicated;

	index = ft_stridx(src, '=');
	name = make_name(src, index);
	env = g_global.envp;
	duplicated = find_env(&env, name);
	if (!duplicated)
		return (0);
	if (index < 1)
		return (1);
	free(duplicated->value);
	duplicated->value = ft_substr(src, index + 1, ft_strlen(src));
	if (!duplicated->value)
		g_global.errno = FAIL_MALLOC;
	return (1);
}

static void	handle_multi_arg(t_node *node)
{
	int				idx;
	t_env			*new;

	idx = 0;
	while (node->command_arg[++idx])
	{
		if (handle_duplicated_name(node->command_arg[idx]))
			continue ;
		new = make_env(node->command_arg[idx]);
		if (g_global.errno == FAIL_MALLOC)
			return ;
		if (g_global.errno == INVALID_IDENTIFIER)
		{
			g_global.exit_status = 1;
			printf("bash: export: `%s': not a valid identifier\n", node->command_arg[idx]);
			continue ;
		}
		add_env_back(new);
	}
}

void	ft_export(t_node *node)
{
	g_global.exit_status = 0;
	if (node->arg_cnt == 1)
		handle_single_arg();
	if (node->arg_cnt > 1)
		handle_multi_arg(node);
//	exit(g_global.exit_status);
}
