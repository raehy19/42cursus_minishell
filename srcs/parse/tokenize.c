/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:24:33 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/14 16:24:42 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern t_global	g_global;

void	tokenize_whitespace(char *str, int *idx, t_token_node **lst)
{
	while (*(str + *idx + 1) && ft_isspace(*(str + *idx + 1)))
		++(*idx);
	lst_add_back_token(lst, lst_new_token(T_WHITESPACE, NULL));
}

void	tokenize_parenthesis(char *str, int *idx, t_token_node **lst)
{
	if (*(str + *idx) == '(')
		lst_add_back_token(lst, lst_new_token(T_LEFT_PARENTHESIS, NULL));
	else if (*(str + *idx) == ')')
		lst_add_back_token(lst, lst_new_token(T_RIGHT_PARENTHESIS, NULL));
}

void	tokenize_and_or_pipe(char *str, int *idx, t_token_node **lst)
{
	char	*tmp;

	if (*(str + *idx + 1)
		&& (*(str + *idx + 1) == '|' || *(str + *idx + 1) == '&'))
	{
		if (*(str + *idx) == '&' && *(str + *idx + 1) == '&')
			lst_add_back_token(lst, lst_new_token(T_AND, NULL));
		else if (*(str + *idx) == '|' && *(str + *idx + 1) == '|')
			lst_add_back_token(lst, lst_new_token(T_OR, NULL));
		++*idx;
	}
	else if (*(str + *idx) == '|')
		lst_add_back_token(lst, lst_new_token(T_PIPE, NULL));
	else
	{
		tmp = ft_strndup((str + *idx), 1);
		if (!tmp)
			g_global.errno = FAIL_MALLOC;
		else
			lst_add_back_token(lst, lst_new_token(T_STRING, tmp));
	}
}

void	tokenize_arrows(char *str, int *idx, t_token_node **lst)
{
	if (*(str + *idx + 1)
		&& (*(str + *idx + 1) == '<' || *(str + *idx + 1) == '>' ))
	{
		if (*(str + *idx) == '<' && *(str + *idx + 1) == '<')
			lst_add_back_token(lst, lst_new_token(T_HERE_DOCUMENT, NULL));
		else if (*(str + *idx) == '>' && *(str + *idx + 1) == '>')
			lst_add_back_token(lst,
				lst_new_token(T_APPENDING_REDIRECTED_OUTPUT, NULL));
		++*idx;
	}
	else if (*(str + *idx) == '<')
		lst_add_back_token(lst, lst_new_token(T_REDIRECTING_INPUT, NULL));
	else if (*(str + *idx) == '>')
		lst_add_back_token(lst, lst_new_token(T_REDIRECTING_OUTPUT, NULL));
}

void	tokenize_string_single(char *str, int *idx, t_token_node **lst)
{
	int	i;

	i = 1;
	while (*(str + *idx + i) && (*(str + *idx + i)) != '\'')
		++i;
	if (!*(str + *idx + i))
	{
		g_global.errno = SYNTAX_ERR;
		return;
	}
	lst_add_back_token(lst,
		lst_new_token(T_STRING, ft_strndup((str + *idx + 1), i - 1)));
	*idx += i;
}

t_token_node	*ft_tokenize(char *input)
{
	int				idx;
	t_token_node	*token_list;

	idx = -1;
	token_list = NULL;
	while (*(input + ++idx))
	{
		if (g_global.errno)
			break ;
		if (ft_isspace(*(input + idx)))
			tokenize_whitespace(input, &idx, &token_list);
		else if (*(input + idx) == '(' || *(input + idx) == ')')
			tokenize_parenthesis(input, &idx, &token_list);
		else if (*(input + idx) == '&' || *(input + idx) == '|')
			tokenize_and_or_pipe(input, &idx, &token_list);
		else if (*(input + idx) == '<' || *(input + idx) == '>')
			tokenize_arrows(input, &idx, &token_list);
		else if (*(input + idx) == '\'')
			tokenize_string_single(input, &idx, &token_list);
		else if (*(input + idx) == '\"')
			;
		else
			;
	}
	return (token_list);
}
