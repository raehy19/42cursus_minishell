/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:58:05 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/26 18:02:28 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

int	is_env_allowed_char(const char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	make_env_linked_str(char *str, t_link_str **lst, int *idx)
{
	int		i;
	char	*env_name;
	t_env	*env;

	i = 0;
	while (is_env_allowed_char(*(str + i)))
		++i;
	env_name = ft_strndup((str), i);
	if (!env_name)
		g_global.err_num = FAIL_MALLOC;
	env = find_env(env_name);
	if (env)
		link_str_add_back(lst,
			new_link_str(T_SINGLE_QUOTE, strdup(env->value)));
	free(env_name);
	*idx += i + 1;
}

void	check_env(char **str)
{
	t_link_str	*temp;
	int			idx;
	int			i;

	temp = NULL;
	idx = 0;
	i = -1;
	while (*((*str) + idx + ++i))
	{
		if (*((*str) + idx + i) == '$')
		{
			if (!((*str) + idx + i + 1) || (*((*str) + idx + i + 1) != '?'
					&& !is_env_allowed_char(*((*str) + idx + i + 1))))
			{
				link_str_add_back(&temp,
					new_link_str(T_SINGLE_QUOTE, strndup((*str) + idx + i, 1)));
				++idx;
			}
			else if (*((*str) + idx + i + 1) == '?')
			{
				link_str_add_back(&temp, new_link_str(T_SINGLE_QUOTE,
						ft_itoa(g_global.exit_status)));
				idx += 2;
			}
			else
			{
				link_str_add_back(&temp,
					new_link_str(T_SINGLE_QUOTE, strndup(((*str) + idx), i)));
				make_env_linked_str((*str + idx + i + 1), &temp, &idx);
			}
			i = -1;
		}
	}
	link_str_add_back(&temp,
		new_link_str(T_SINGLE_QUOTE, strndup((*str + idx), i)));
	free(*str);
	*str = ft_combine_lump(temp);
}
