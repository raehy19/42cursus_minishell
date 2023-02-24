/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:56:51 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/24 20:56:53 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token_node	*new_token(t_token_type type, char *str)
{
	t_token_node	*new;

	new = (t_token_node *) malloc(sizeof(t_token_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->string = str;
	new->next = NULL;
	return (new);
}

