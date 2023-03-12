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

#include "../../minishell.h"

extern t_global	g_global;

void	tokenize_single_quote(char *str, int *idx, t_token_node **lst)
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
	lst_push_token(lst,
		new_token(T_SINGLE_QUOTE,
			ft_strndup((str + *idx + 1), i - 1)));
	*idx += i;
}

void	tokenize_double_quote(char *str, int *idx, t_token_node **lst)
{
	int		i;

	i = 1;
	while (*(str + *idx + i) && (*(str + *idx + i)) != '\"')
		++i;
	if (!*(str + *idx + i))
	{
		g_global.err_num = SYNTAX_ERR;
		return ;
	}
	lst_push_token(lst,
		new_token(T_DOUBLE_QUOTE,
			ft_strndup((str + *idx + 1), i - 1)));
	*idx += i;
}

void	tokenize_string(char *str, int *idx, t_token_node **lst)
{
	int		i;

	i = 0;
	while (is_string_char(*(str + *idx + i)))
		++i;
	lst_push_token(lst,
		new_token(T_STRING, ft_strndup((str + *idx), i)));
	*idx += i - 1;
}
