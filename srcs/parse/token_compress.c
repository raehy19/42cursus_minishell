/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_compress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:43:14 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/12 04:35:19 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_combine_str(t_token *temp, t_linked_str **linked_str,
					   t_token **token_list)
{
	t_token	*to_free;

	while (is_string(temp))
	{
		lst_add_back_linked_str(linked_str,
			new_linked_str(temp->type, temp->str));
		to_free = temp;
		temp = temp->next;
		free(to_free);
	}
	*token_list = temp;
}

void	compress_str_node(t_token *temp,
						  t_token **compressed_token_list, t_token **token_list)
{
	t_linked_str	*linked_str;
	t_token	*new;

	linked_str = NULL;
	lst_add_back_linked_str(&linked_str,
		new_linked_str(temp->type, temp->str));
	new = new_token(T_LUMP_STR, NULL);
	ft_combine_str(temp->next, &linked_str, token_list);
	new->linked_str = linked_str;
	lst_push_token(compressed_token_list, new);
	free(temp);
}

t_token	*compress_tokens(t_token **token_list)
{
	t_token	*compressed_token_list;
	t_token	*temp;

	compressed_token_list = NULL;
	temp = token_shift(token_list);
	while (temp)
	{
		if (is_string(temp))
			compress_str_node(temp, &compressed_token_list, token_list);
		else if (temp->type == T_WHITESPACE)
			free(temp);
		else
		{
			temp->next = NULL;
			lst_push_token(&compressed_token_list, temp);
		}
		temp = token_shift(token_list);
	}
	return (compressed_token_list);
}
