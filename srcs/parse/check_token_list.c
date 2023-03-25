/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:39:59 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/25 21:40:00 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

t_node	*check_token_list(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	while(temp)
	{
		
		temp = temp->next;
	}
}
