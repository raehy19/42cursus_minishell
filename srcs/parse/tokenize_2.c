/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:26:49 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/11 14:31:05 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern t_global	g_global;

void	tokenize_string_single(char *str, int *idx, t_token_node **lst)
{
	int	i;

	i = 1;
	while (*(str + *idx + i) && (*(str + *idx + i)) != '\'')
		++i;
	if (!*(str + *idx + i))
	{
		g_global.err_num = SYNTAX_ERR;
		return ;
	}
	lst_add_back_token(lst,
		lst_new_token(T_STRING, ft_strndup((str + *idx + 1), i - 1)));
	*idx += i;
}

void	tokenize_env(char *str, int *idx, t_token_node **lst)
{
	int		i;
	char	*env_name;
	t_env	*env;

	i = 0;
	while (is_env_allowed_char(*(str + *idx + i + 1)))
		++i;
	env_name = ft_strndup((str + *idx + 1), i);
	if (!env_name)
		g_global.err_num = FAIL_MALLOC;
	env = find_env(env_name);
	if (env)
		lst_add_back_token(lst,
			lst_new_token(T_STRING, ft_strdup(env->value)));
	free(env_name);
	*idx += i + 1;
}

void	tokenize_string_double(char *str, int *idx, t_token_node **lst)
{
	int		i;

	i = 1;
	while (*(str + *idx + i) && (*(str + *idx + i)) != '\"')
	{
		if (*(str + *idx + i) == '$')
		{
			lst_add_back_token(lst,
				lst_new_token(T_STRING, ft_strndup((str + *idx + 1), i - 1)));
			*idx += i;
			i = 0;
			tokenize_env(str, idx, lst);
		}
		++i;
	}
	if (!*(str + *idx + i))
	{
		g_global.err_num = SYNTAX_ERR;
		return ;
	}
	lst_add_back_token(lst,
		lst_new_token(T_STRING, ft_strndup((str + *idx + 1), i - 1)));
	*idx += i;
}

void	tokenize_string(char *str, int *idx, t_token_node **lst)
{
	int		i;

	i = 0;
	while (is_string_char(*(str + *idx + i)))
	{
		if (*(str + *idx + i) == '$')
		{
			lst_add_back_token(lst,
				lst_new_token(T_STRING, ft_strndup((str + *idx), i)));
			*idx += i;
			i = 0;
			tokenize_env(str, idx, lst);
		}
		++i;
	}
	lst_add_back_token(lst,
		lst_new_token(T_STRING, ft_strndup((str + *idx), i)));
	*idx += i - 1;
}
