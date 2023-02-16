/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:46:07 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 19:39:30 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

static void	handle_single_arg(void)
{
	int		idx;
	t_env	*tmp;

	idx = 0;
	tmp = g_global.envp;
	rank_envp();
	while (idx < get_envp_size())
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

static void	handle_multi_arg(t_node *node)
{
	int				idx;
	t_env			*new;

	idx = 1;
	while (node->command_arg[idx])
	{
		new = make_env(node->command_arg[idx]);
		if (g_global.errno == FAIL_MALLOC)
			return ;
		if (g_global.errno == INVALID_IDENTIFIER)
		{
			g_global.exit_status = 1;
			printf("bash: export: `%s': not a valid identifier\n", node->command_arg[idx]);
			idx++;
			continue ;
		}
		add_env_back(new);
		idx++;
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
