/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:26:24 by rjeong            #+#    #+#             */
/*   Updated: 2023/04/02 13:51:20 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

int	is_string_char(char c)
{
	if (!c || ft_isspace(c) || c == '(' || c == ')' || c == '&' || c == '|'
		|| c == '<' || c == '>' || c == '\'' || c == '\"')
		return (0);
	return (1);
}

int	is_and_or_pipe(t_token *temp)
{
	if (!temp)
		return (0);
	if (temp->type == T_AND || temp->type == T_OR
		||temp->type == T_PIPE)
		return (1);
	return (0);
}

int	is_parenthesis(t_token *temp)
{
	if (!temp)
		return (0);
	if (temp->type == T_LEFT_PARENTHESIS
		|| temp->type == T_RIGHT_PARENTHESIS)
		return (1);
	return (0);
}

int	is_logical(t_token *temp)
{
	return (is_and_or_pipe(temp) || is_parenthesis(temp));
}

int	is_arrow(t_token *temp)
{
	if (!temp)
		return (0);
	if (temp->type == T_REDIRECTING_INPUT
		|| temp->type == T_HERE_DOCUMENT
		||temp->type == T_REDIRECTING_OUTPUT
		||temp->type == T_APPENDING_REDIRECTED_OUTPUT)
		return (1);
	return (0);
}
