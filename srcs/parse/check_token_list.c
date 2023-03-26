/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:39:59 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/26 12:45:14 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

t_link_str	*link_str_shift(t_link_str **link_str_list)
{
	t_link_str	*temp;

	temp = *link_str_list;
	if (temp)
		*link_str_list = (*link_str_list)->next;
	return (temp);
}

void	free_link_str(t_link_str **link_str_list)
{
	t_link_str	*temp;

	temp = link_str_shift(link_str_list);
	while (temp)
	{
		free(temp->str);
		free(temp);
		temp = link_str_shift(link_str_list);
	}
}

void	free_token_list(t_token **token_list)
{
	t_token	*temp;

	temp = token_shift(token_list);
	while (temp)
	{
		free(temp->str);
		free_link_str(&temp->link_str);
		free(temp);
		temp = token_shift(token_list);
	}
}

int	free_n_ret(t_token **token_list, int ret)
{
	free_token_list(token_list);
	return (ret);
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
		else if (is_and_or_pipe(temp))
		{
			if (!temp->next || (!is_arrow(temp)
					&& temp->next->type != T_LUMP_STR
					&& temp->next->type != T_LEFT_PARENTHESIS))
				return (free_n_ret(token_list, 1));
		}
		else if (is_arrow(temp))
		{
			if (!temp->next || temp->next->type != T_LUMP_STR)
				return (free_n_ret(token_list, 1));
		}
		if (parenthesis_stack < 0)
			return (free_n_ret(token_list, 1));
		temp = temp->next;
	}
	if (parenthesis_stack != 0)
		return (free_n_ret(token_list, 1));
	return (0);
}
