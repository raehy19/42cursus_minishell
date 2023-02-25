/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:46:07 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 09:55:06 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

static void	handle_single_arg(void)
{
	int		idx;
	int		size;
	t_env	*tmp;

	idx = 0;
	size = get_env_size();
	tmp = g_global.envp;
	rank_envp();
	while (idx < size)
	{
		if (tmp->order == idx)
		{
			if (!tmp->value)
				printf("declare -x %s\n", tmp->name);
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = g_global.envp;
			idx++;
			continue ;
		}
		tmp = tmp->next;
	}
}

static int	handle_duplicated_name(char *src)
{
	int		index;
	char	*name;
	t_env	*tmp;
	t_env	*duplicated;

	index = ft_index(src, '=');
	name = make_name(src, index);
	tmp = g_global.envp;
	duplicated = find_env(&tmp, name);
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
