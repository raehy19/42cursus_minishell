/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:51:29 by rjeong            #+#    #+#             */
/*   Updated: 2023/04/02 13:51:26 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_cmd_arg_linked(t_linked_arg *linked_arg_list)
{
	t_linked_arg	*temp;
	t_linked_arg	*next;

	temp = linked_arg_list;
	while (temp)
	{
		next = temp->next;
		free_link_str(&temp->arg_str);
		free(temp);
		temp = next;
	}
}

void	free_link_str(t_link_str **link_str_list)
{
	t_link_str	*temp;
	t_link_str	*next;

	temp = *link_str_list;
	while (temp)
	{
		next = temp->next;
		free(temp->str);
		free(temp);
		temp = next;
	}
	*link_str_list = NULL;
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
