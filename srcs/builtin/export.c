/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:46:07 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 17:06:45 by yeepark          ###   ########.fr       */
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

	index = ft_stridx(src, '=');
	name = make_name(src, index);
	env = find_env(name);
	if (!env)
		return (0);
	if (index < 1)
		return (1);
	free(env->value);
	env->value = ft_substr(src, index + 1, ft_strlen(src));
	if (!env->value)
		g_global.err_num = FAIL_MALLOC;
	return (1);
}

static void	handle_multi_arg(t_node *node)
{
	int				idx;
	t_env			*new;

	idx = 0;
	while (node->command_arg[++idx])
	{
		if (g_global.err_num == FAIL_MALLOC)
			return ;
		g_global.err_num = NaE;
		if (handle_duplicated_name(node->command_arg[idx]))
			continue ;
		new = make_env(node->command_arg[idx]);
		if (g_global.err_num == NaE)
			add_env_back(new);
		if (g_global.err_num == INVALID_IDENTIFIER)
			print_invalid_identifier_error(node, idx);
	}
	g_global.err_num = NaE;
}

void	ft_export(t_node *node)
{
	g_global.exit_status = 0;
	g_global.err_num = NaE;
	if (node->arg_cnt == 1)
		handle_single_arg();
	if (node->arg_cnt > 1)
		handle_multi_arg(node);
	handle_error();
	exit_by_global();
}
