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

void	tokenize_and_or_pipe(char *str, int *idx, t_token_node *lst)
{
	if (*(str + *idx) == '&' && *(str + *idx + 1) == '&')
	{
		lst_add_back_token(&lst, lst_new_token(T_AND, NULL));
		++*idx;
	}
	else if (*(str + *idx) == '|' && *(str + *idx + 1) == '|')
	{
		lst_add_back_token(&lst, lst_new_token(T_OR, NULL));
		++*idx;
	}
	else if (*(str + *idx) == '|')
		lst_add_back_token(&lst, lst_new_token(T_PIPE, NULL));
	else
		;
}

t_token_node	*ft_tokenize(char *input)
{
	int				idx;
	t_token_node	*token_list;

	idx = 0;
	token_list = NULL;
	while (*(input + ++idx))
	{
		if (ft_isspace(*(input + idx)))
			;
		else if (*(input + idx) == '(' || *(input + idx) == ')')
			;
		else if (*(input + idx) == '&' || *(input + idx) == '|')
			;
		else if (*(input + idx) == '<' || *(input + idx) == '>')
			;
		else if (*(input + idx) == '\'')
			;
		else if (*(input + idx) == '\"')
			;
		else
			;
	}
	return (token_list);
}