/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_on_excute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:52:29 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/26 12:44:10 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

char	*ft_combine_lump(t_link_str *head)
{
	t_link_str		*temp;
	t_link_str		*next;
	char			*res;
	char			*temp_str;

	res = head->str;
	temp = head;
	if (temp->str_type != T_SINGLE_QUOTE)
		check_env(&res);
	while (temp->next)
	{
		if (temp->next->str_type != T_SINGLE_QUOTE)
			check_env(&(temp->next->str));
		temp_str = ft_strjoin(res, temp->next->str);
		free(res);
		free(temp->next->str);
		temp->next->str = NULL;
		res = temp_str;
		next = temp->next;
		free(temp);
		temp = next;
	}
	free(temp);
	return (res);
}

int	ft_count_arg(t_linked_arg *head)
{
	int	i;

	if (!head)
		return (0);
	i = 1;
	while (head && head->next)
	{
		head = head->next;
		++i;
	}
	return (i);
}

char	**ft_combine_arg(t_linked_arg **head, int *arg_cnt)
{
	t_linked_arg	*temp;
	char			**res;
	int				i;

	*arg_cnt = ft_count_arg(*head);
	if (*arg_cnt == 0)
		return (NULL);
	res = (char **) malloc(sizeof(char *) * (*arg_cnt + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < *arg_cnt)
	{
		*(res + i) = ft_combine_lump((*head)->arg_str);
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	*(res + i) = NULL;
	return (res);
}
