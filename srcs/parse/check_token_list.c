/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:39:59 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/26 18:02:40 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

int	free_n_ret(t_token **token_list, int ret)
{
	free_token_list(token_list);
	return (ret);
}

int	and_or_pipe_condition(t_token *temp)
{
	if (!temp->next || (!is_arrow(temp)
			&& temp->next->type != T_LUMP_STR
			&& temp->next->type != T_LEFT_PARENTHESIS))
		return (1);
	return (0);
}

int	arrow_condition(t_token *temp)
{
	if (!temp->next || temp->next->type != T_LUMP_STR)
		return (1);
	return (0);
}

int	check_token_list(t_token **token_list)
{
	t_token	*temp;
	int		parenthesis_stack;

	temp = *token_list;
	parenthesis_stack = 0;
	while (temp)
	{
		if (temp->type == T_LEFT_PARENTHESIS)
			++parenthesis_stack;
		else if (temp->type == T_RIGHT_PARENTHESIS)
			--parenthesis_stack;
		else if ((is_and_or_pipe(temp) && and_or_pipe_condition(temp))
			|| (is_arrow(temp) && arrow_condition(temp)))
			return (free_n_ret(token_list, 1));
		if (parenthesis_stack < 0)
			return (free_n_ret(token_list, 1));
		temp = temp->next;
	}
	if (parenthesis_stack != 0)
		return (free_n_ret(token_list, 1));
	return (0);
}
